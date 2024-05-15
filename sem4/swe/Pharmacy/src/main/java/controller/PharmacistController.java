package controller;

import com.sun.tools.javac.Main;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;
import repository.UserHibernateDBRepository;
import repository.UserRepository;
import services.LoginService;
import services.MasterService;

import java.io.IOException;

public class PharmacistController {
	public Button log_btn;
	private MasterService service;

	public void logout(ActionEvent actionEvent) throws IOException {
		FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("../login-view.fxml"));
		Stage stage = new Stage();
		stage.setScene(new Scene(fxmlLoader.load()));
		stage.setTitle("Login");
		LoginController loginController = fxmlLoader.getController();

		UserRepository userRepository = new UserHibernateDBRepository();
		LoginService service = new LoginService(userRepository);
		loginController.setService(service);
		stage.show();
		((Stage) (log_btn.getScene().getWindow())).close();
	}

	public void setService(MasterService service) {
		this.service = service;
	}

	public MasterService getService() {
		return service;
	}
}
