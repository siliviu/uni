import networking.server.AbstractServer;
import networking.server.JsonConcurrentServer;
import repository.*;
import server.LoginService;
import server.MasterService;
import server.UserService;
import services.IMasterService;

import java.io.FileReader;
import java.io.IOException;
import java.security.NoSuchAlgorithmException;
import java.util.Properties;

@SuppressWarnings("FieldCanBeLocal")
public class Main {
	private static final int defaultServerPort = 55555;

	public static void main(String[] args) {
		Properties props = new Properties();
		try {
			props.load(new FileReader("bd.config"));
			props.load(Main.class.getResourceAsStream("client.properties"));
		} catch (IOException e) {
			System.out.println("Cannot find bd.config or client.properties " + e);
		}
		int serverPort = defaultServerPort;
		try {
			serverPort = Integer.parseInt(props.getProperty("server.port"));
		} catch (NumberFormatException ex) {
			System.err.println("Wrong port number " + ex.getMessage());
			System.out.println("Using default port: " + defaultServerPort);
		}
		System.out.println("Using server port " + serverPort);
//		UserRepository userRepository = new UserDBRepository(props);
		UserRepository userRepository = new UserHibernateDBRepository();
//		ChildRepository childRepository = new ChildDBRepository(props);
		ChildRepository childRepository=new ChildHibernateDBRepository();
//		SignupRepository signupRepository = new SignupDBRepository(props);
		SignupRepository signupRepository = new SignupHibernateDBRepository();
		LoginService loginService = new LoginService(userRepository);
		UserService userService = new UserService(childRepository, signupRepository);
		IMasterService service = new MasterService(loginService, userService);
		AbstractServer server = new JsonConcurrentServer(serverPort, service);
		try {
			server.start();
		} catch (Exception e) {
			System.err.println("Error starting the server" + e.getMessage());
		}
	}
}
