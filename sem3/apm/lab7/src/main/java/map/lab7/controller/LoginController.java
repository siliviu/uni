package map.lab7.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import map.lab7.MasterGUI;
import map.lab7.domain.User;
import map.lab7.service.*;

public class LoginController {
	public TextField username;
	public TextField password;
	public TextField firstname;
	public TextField lastname;
	LoginService loginService;

	public void login(ActionEvent actionEvent) {
		try {
			loginService.login(username.getText(), password.getText());
			FXMLLoader fxmlLoader = new FXMLLoader(MasterGUI.class.getResource("user-view.fxml"));
			try {
				Scene scene = new Scene(fxmlLoader.load());
				Stage stage = new Stage();
				UserController controller = fxmlLoader.getController();
				MessageService messageService = new MessageService();
				UserService userService = new UserService();
				FriendService friendService = new FriendService();
				ClientService clientService = new ClientService(messageService, userService, friendService, loginService.getUser(username.getText()));
				controller.setServices(clientService, userService, friendService, messageService);
				stage.setTitle("User menu");
				stage.setScene(scene);
				stage.show();
				((Stage)(username.getScene().getWindow())).close();
			} catch (Exception exception) {
				throw new RuntimeException(exception);
			}
		} catch (Exception e) {
			Alert alert = new Alert(Alert.AlertType.ERROR);
			alert.setContentText("Could not login.\n" + e.getMessage());
			alert.show();
		}

	}

	public void register(ActionEvent actionEvent) {
		try {
			loginService.register(username.getText(), password.getText(), firstname.getText(),lastname.getText());
			username.clear();
			password.clear();
			firstname.clear();
			lastname.clear();
			Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
			alert.setContentText("Registered successfully! You can now log in");
			alert.show();
		} catch (Exception e) {
			Alert alert = new Alert(Alert.AlertType.ERROR);
			alert.setContentText("Could not register.\n" + e.getMessage());
			alert.show();
		}
	}

	public void setService(LoginService loginService) {
		this.loginService = loginService;
	}


}
