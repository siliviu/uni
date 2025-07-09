package networking.server;
import networking.worker.AbstractWorker;
import networking.worker.MasterJsonWorker;
import services.IMasterService;

import java.net.Socket;

public class JsonConcurrentServer extends AbstractConcurrentServer {
	private final IMasterService service;

	public JsonConcurrentServer(int port, IMasterService service) {
		super(port);
		this.service = service;
		System.out.println("JsonConcurrentServer");
	}

	@Override
	protected Thread createWorker(Socket client) {
		AbstractWorker worker = new MasterJsonWorker(service, client);
		return new Thread(worker);
	}
}
