package controller;

import com.sun.tools.javac.Main;
import domain.User;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import services.LoginService;
import services.MasterService;

public class LoginController {

	public TextField username, password;
	private LoginService service;

	public void login(ActionEvent actionEvent) {
		try {
			User user = service.login(username.getText(), password.getText());
			try {
				Stage stage = new Stage();
				FXMLLoader fxmlLoader;
				if (user.getType().equals("ward")) {
					fxmlLoader = new FXMLLoader(getClass().getResource("../ward-view.fxml"));
					stage.setTitle("Ward menu");
					stage.setScene(new Scene(fxmlLoader.load()));
					WardController wardController = fxmlLoader.getController();
					wardController.setService(new MasterService());
				} else {
					fxmlLoader = new FXMLLoader(getClass().getResource("../pharmacist-view.fxml"));
					stage.setTitle("Pharmacy menu");
					stage.setScene(new Scene(fxmlLoader.load()));
					PharmacistController pharmacistController = fxmlLoader.getController();
					pharmacistController.setService(new MasterService());

				}
				((Stage) (username.getScene().getWindow())).close();
				stage.show();
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

	public void setService(LoginService service) {
		this.service = service;
	}

}