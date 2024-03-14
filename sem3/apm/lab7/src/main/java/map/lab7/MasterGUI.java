package map.lab7;

import atlantafx.base.theme.PrimerDark;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import map.lab7.controller.MasterController;
import map.lab7.domain.*;
import map.lab7.repository.Repository;
import map.lab7.repository.database.FriendRequestDBRepository;
import map.lab7.repository.database.FriendshipDBRepository;
import map.lab7.repository.database.MessageDBRepository;
import map.lab7.repository.database.UserDBRepository;
import map.lab7.service.FriendService;
import map.lab7.service.MasterService;
import map.lab7.service.MessageService;
import map.lab7.service.UserService;

import java.io.IOException;

public class MasterGUI extends javafx.application.Application implements App {

	@Override
	public void start(Stage stage) throws IOException {
		Repository<Long, Message> messageRepo = new MessageDBRepository();
		UserService userService = new UserService();
		FriendService friendService = new FriendService();
		MessageService messageService = new MessageService();
		MasterService service = new MasterService(userService, friendService);
		FXMLLoader fxmlLoader = new FXMLLoader(MasterGUI.class.getResource("master-view.fxml"));
		setUserAgentStylesheet(new PrimerDark().getUserAgentStylesheet());
		stage.setScene(new Scene(fxmlLoader.load()));
		MasterController userController = fxmlLoader.getController();
		userController.setServices(service, userService, friendService, messageService);
		stage.setTitle("Users");
		stage.show();
	}

	@Override
	public void run() {
		launch();
	}
}