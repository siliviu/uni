package com.example.template.controller;

import com.example.template.HelloApplication;
import com.example.template.domain.Client;
import com.example.template.service.Service;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.io.IOException;

public class LoginController {
	public Button btn;
	public TextField textbox;
	Service service;

	void openWindow(Client user) {
		FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("client-view.fxml"));
		Scene scene = null;
		try {
			scene = new Scene(fxmlLoader.load());
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		Stage stage = new Stage();
		ClientController controller = fxmlLoader.getController();
		controller.setService(service, user);
		stage.setTitle(String.format("%s", user.getName()));
		stage.setScene(scene);
		stage.show();
	}

	@FXML
	public void initialize() {
		btn.setOnAction(p -> openWindow(service.getByUsername(textbox.getText())));
	}

	public void setService(Service service) {
		this.service = service;
	}
}
