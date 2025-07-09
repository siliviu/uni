package controller;

import javafx.event.ActionEvent;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import services.IMasterService;
import services.IUserObserver;

public class LoginController {

	public IUserObserver user;
	public TextField username, password;
	private IMasterService service;

	Parent mainParent;

	public void login(ActionEvent actionEvent) {
		try {
			service.logIn(username.getText(), password.getText(), user);
			try {
				Stage stage = new Stage();
				Scene scene = new Scene(mainParent);

				stage.setTitle("User menu");
				stage.setScene(scene);
				stage.show();
				((Stage) (username.getScene().getWindow())).close();
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
			service.register(username.getText(), password.getText());
			username.clear();
			password.clear();
			Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
			alert.setContentText("Registered successfully! You can now log in");
			alert.show();
		} catch (Exception e) {
			Alert alert = new Alert(Alert.AlertType.ERROR);
			alert.setContentText("Could not register.\n" + e.getMessage());
			alert.show();
		}
	}

	public void setService(IMasterService service) {
		this.service = service;
	}

	public void setParent(Parent p){
		mainParent=p;
	}

	public void setUser(IUserObserver user) {
		this.user = user;
	}
}
