package map.lab7;

import atlantafx.base.theme.PrimerDark;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import map.lab7.controller.LoginController;
import map.lab7.controller.MasterController;
import map.lab7.repository.database.CredentialDBRepository;
import map.lab7.service.LoginService;
import map.lab7.service.UserService;

public class UserGUI extends javafx.application.Application implements App{
	@Override
	public void start(Stage stage) throws Exception {
		FXMLLoader fxmlLoader = new FXMLLoader(MasterGUI.class.getResource("login-view.fxml"));
		setUserAgentStylesheet(new PrimerDark().getUserAgentStylesheet());
		stage.setScene(new Scene(fxmlLoader.load()));
		LoginController loginController = fxmlLoader.getController();
		loginController.setService(new LoginService(new UserService()));
		stage.setTitle("Users");
		stage.setResizable(false);
		stage.show();
	}
	@Override
	public void run() {
		launch();
	}

}
