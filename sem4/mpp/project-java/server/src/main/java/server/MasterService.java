package server;

import domain.AgeGroup;
import domain.RaceDistance;
import domain.dto.ChildDTO;
import services.IMasterService;
import services.IUserObserver;

import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.ConcurrentHashMap;

import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.activemq.command.ActiveMQTopic;
import utils.HibernateUtils;

import javax.jms.*;

public class MasterService implements IMasterService {
	private final LoginService loginService;
	private final UserService userService;
	protected MessageProducer producer = null;
	protected Session session = null;

	private final Map<String, IUserObserver> loggedClients;

	public MasterService(LoginService loginService, UserService userService) {
		this.loginService = loginService;
		this.userService = userService;
		loggedClients = new ConcurrentHashMap<>();
	}

	@Override
	public synchronized void register(String username, String password) {
		loginService.register(username, password);
	}

	@Override
	public synchronized void logIn(String username, String password, IUserObserver user) throws Exception {
		if (loggedClients.get(username) != null)
			throw new Exception("User already logged in.");
		loginService.login(username, password);
		loggedClients.put(username, user);
	}

	@Override
	public void logOut(IUserObserver observer) throws Exception {
		String username = null;
		for (Map.Entry<String, IUserObserver> entry : loggedClients.entrySet())
			if (Objects.equals(observer, entry.getValue()))
				username = entry.getKey();
		if (username == null)
			throw new Exception("User not logged in");
		loggedClients.remove(username);
		HibernateUtils.closeSessionFactory();
	}

	@Override
	public synchronized List<ChildDTO> searchChildren(RaceDistance raceDistance, AgeGroup ageGroup) {
		return userService.searchChildren(raceDistance, ageGroup);
	}

	@Override
	public synchronized void signUpChild(String name, Integer age, RaceDistance raceDistance, AgeGroup ageGroup) {
		userService.signUpChild(name, age, raceDistance, ageGroup);
		notifySignup();
	}


	//	private final int defaultThreadsNo = 5;
//
//	private void notifySignup() {
//		System.out.println("Notifying");
//
//		ExecutorService executor = Executors.newFixedThreadPool(defaultThreadsNo);
//		for (IUserObserver user : loggedClients.values())
//			if (user != null)
//				executor.execute(() -> {
//					try {
//						System.out.println("Notifying " + user);
//						user.notifySignup();
//					} catch (Exception e) {
//						System.err.println("Error notifying friend " + e);
//					}
//				});
//		executor.shutdown();
//	}
	public void initialiseNotifications() {
		if (producer != null)
			return;
		ConnectionFactory cf = new ActiveMQConnectionFactory("tcp://localhost:61616");
		Connection conn = null;
		try {
			conn = cf.createConnection();
			conn.start();
			session = conn.createSession(false, Session.AUTO_ACKNOWLEDGE);
			Destination destination = new ActiveMQTopic("notification");
			producer = session.createProducer(destination);

		} catch (JMSException ignored) {
		}
	}

	private void notifySignup() {
		try {
			initialiseNotifications();
			TextMessage message = session.createTextMessage();
			message.setText("UPDATE_CHILDREN");
			System.out.println("SENT: " + message.getText());
			producer.send(message);
		} catch (JMSException ignored) {
		}
	}
}
