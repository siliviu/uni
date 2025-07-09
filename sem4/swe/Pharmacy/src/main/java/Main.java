import controller.LoginController;
import repository.*;
import services.LoginService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import services.MasterService;

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
		MedicineRepository medicineRepository = new MedicineHibernateDBRepository();
		OrderRepository orderRepository = new OrderHibernateDBRepository();
		OrderItemRepository orderItemRepository = new OrderItemHibernateDBRepository();
		MasterService master = new MasterService(medicineRepository, orderRepository, orderItemRepository);
		loginController.setService(service, master);
		stage.show();

	}
}