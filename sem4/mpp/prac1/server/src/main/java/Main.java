import networking.server.AbstractServer;
import networking.server.JsonConcurrentServer;
import repository.*;
import server.LoginService;
import server.MasterService;
import services.IMasterService;

@SuppressWarnings("FieldCanBeLocal")
public class Main {
	private static final int serverPort = 55555;

	public static void main(String[] args) {
		System.out.println("Using server port " + serverPort);
		UserRepository userRepository = new UserHibernateRepository();
//		ChildRepository childRepository=new ChildHibernateRepository();
//		SignupRepository signupRepository = new SignupHibernateRepository();
		GameRepository gameRepository = new GameHibernateRepository();
		WordsRepository wordsRepository = new WordsHibernateRepository();
		MoveRepository moveRepository = new MoveHibernateRepository();
		LoginService loginService = new LoginService(userRepository);
		IMasterService service = new MasterService(loginService, gameRepository, wordsRepository, moveRepository);
		AbstractServer server = new JsonConcurrentServer(serverPort, service);
		try {
			server.start();
		} catch (Exception e) {
			System.err.println("Error starting the server" + e.getMessage());
		}
	}
}
