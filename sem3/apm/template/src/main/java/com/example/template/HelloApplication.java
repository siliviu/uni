package com.example.template;

import com.example.template.controller.LoginController;
import com.example.template.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {

	@Override
	public void start(Stage stage) throws IOException {
		FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("login-view.fxml"));
		Scene scene = new Scene(fxmlLoader.load(), 320, 240);
		LoginController controller = fxmlLoader.getController();
		Service s = new Service();
		controller.setService(s);
		stage.setTitle("Login");
		stage.setScene(scene);
		stage.show();
	}
	public static void main(String[] args) {
		launch(args);
	}
}