import controller.UserController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import controller.LoginController;
import networking.proxy.MasterJsonProxy;
import services.IMasterService;

import java.io.IOException;
import java.util.Properties;

public class Main extends javafx.application.Application {
	public static void main(String[] args) {
		Application.launch();
	}

	@SuppressWarnings("FieldCanBeLocal")
	private static final int defaultServerPort = 55555;
	@SuppressWarnings("FieldCanBeLocal")
	private static final String defaultServerIP = "localhost";

	@Override
	public void start(Stage stage) throws Exception {
		FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("login-view.fxml"));
		stage.setScene(new Scene(fxmlLoader.load()));
		stage.setTitle("Login");
			LoginController loginController = fxmlLoader.getController();

		FXMLLoader fxmlLoader2 = new FXMLLoader(Main.class.getResource("user-view.fxml"));


		Properties props = new Properties();
		try {
			props.load(Main.class.getResourceAsStream("client.properties"));
		} catch (IOException e) {
			System.out.println("Cannot find bd.config or client.properties " + e);
		}
		String serverIP = props.getProperty("server.host", defaultServerIP);
		int serverPort = defaultServerPort;

		try {
			serverPort = Integer.parseInt(props.getProperty("server.port"));
		} catch (NumberFormatException ex) {
			System.err.println("Wrong port number " + ex.getMessage());
			System.out.println("Using default port: " + defaultServerPort);
		}
		System.out.println("Using server IP " + serverIP);
		System.out.println("Using server port " + serverPort);

		IMasterService service = new MasterJsonProxy(serverIP, serverPort);

		loginController.setService(service);

		Parent parent = fxmlLoader2.load();

		UserController userController = fxmlLoader2.getController();
		userController.setService(service);
		loginController.setParent(parent);
		loginController.setUser(userController);
		stage.show();

	}
}