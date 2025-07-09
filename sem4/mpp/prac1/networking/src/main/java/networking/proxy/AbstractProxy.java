package networking.proxy;

import networking.Response;
import networking.ResponseType;
import org.apache.activemq.ActiveMQConnectionFactory;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.activemq.command.ActiveMQTopic;

import javax.jms.*;

public abstract class AbstractProxy {
	protected final String host;
	protected final int port;

	protected BufferedReader input;
	protected PrintWriter output;
	protected Socket connection;

	protected final BlockingQueue<Response> responses;
	protected volatile boolean finished;

	public AbstractProxy(String host, int port) {
		this.host = host;
		this.port = port;
		responses = new LinkedBlockingQueue<>();
	}

	protected void closeConnection() {
		finished = true;
		try {
			input.close();
			output.close();
			connection.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	protected Response getResponse() {
		Response response = null;
		try {
			response = responses.take();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		return response;
	}

	protected void initializeConnection() {
		if (connection != null)
			return;
		try {
			connection = new Socket(host, port);
			output = new PrintWriter(connection.getOutputStream());
			output.flush();
			input = new BufferedReader(new InputStreamReader(connection.getInputStream()));
			finished = false;
			startReader();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void startReader() {
		Thread tw = new Thread(new ReaderThread());
		Thread not = new Thread(new NotificationThread());
		tw.start();
		not.start();
	}

	protected abstract boolean isUpdate(Response response);

	protected abstract void handleUpdate(Response response);

	protected abstract Response readResponse() throws Exception;

	private class NotificationThread implements Runnable {
		public void run() {
			try {
				ConnectionFactory cf = new ActiveMQConnectionFactory("tcp://localhost:61616");
				Connection conn = null;
				Session session = null;
				conn = cf.createConnection();
				conn.start();
				session = conn.createSession(false, Session.AUTO_ACKNOWLEDGE);
				Destination destination = new ActiveMQTopic("notification");
				MessageConsumer consumer = session.createConsumer(destination);
				while (!finished) {
					Message message = consumer.receive();
					TextMessage textMessage = (TextMessage) message;
					System.out.println("Received: " + textMessage.getText());
					Response response = new Response();
					if(textMessage.getText().equals("UPDATE_CHILDREN")) {
						response.setType(ResponseType.UPDATE);
						handleUpdate(response);
					}
				}
			} catch (JMSException e) {
// handle exception …
			}
		}
	}

	private class ReaderThread implements Runnable {
		public void run() {
			while (!finished) {
				Response response = null;
				try {
					response = readResponse();
					if (finished)
						break;
				} catch (Exception e) {
					System.out.println("Reading error " + e);
				}
				if (isUpdate(response)) {
					handleUpdate(response);
				} else {
					try {
						responses.put(response);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}

			}
		}
	}
}
