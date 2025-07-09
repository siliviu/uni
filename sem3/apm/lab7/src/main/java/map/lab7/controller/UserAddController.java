package map.lab7.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import map.lab7.service.MasterService;
import map.lab7.service.UserService;

public class UserAddController {
	@FXML
	public TextField fNameField;
	@FXML
	public TextField lNameField;
	@FXML
	UserService userService;

	public void add(ActionEvent mouseEvent) {
		try {
			userService.addUser(fNameField.getText(), lNameField.getText());
			fNameField.clear();
			lNameField.clear();
			fNameField.requestFocus();
		} catch (Exception e) {
			Alert alert = new Alert(Alert.AlertType.ERROR);
			alert.setContentText("Could not add user.\n"+e.getMessage());
			alert.show();
		}
	}

	public void setUserService(UserService _service) {
		userService = _service;
	}
}
