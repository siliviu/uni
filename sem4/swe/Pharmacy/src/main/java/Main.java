import controller.LoginController;
import repository.UserHibernateDBRepository;
import repository.UserRepository;
import services.LoginService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends javafx.application.Application {
	public static void main(String[] args) {
		Application.launch();
	}

	@Override
	public void start(Stage stage) throws Exception {
		FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("login-view.fxml"));
		stage.setScene(new Scene(fxmlLoader.load()));
		stage.setTitle("Login");
		LoginController loginController = fxmlLoader.getController();

		UserRepository userRepository = new UserHibernateDBRepository();
		LoginService service = new LoginService(userRepository);
		loginController.setService(service);
		stage.show();

	}
}