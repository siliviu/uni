package controller;

import com.sun.tools.javac.Main;
import domain.Order;
import domain.OrderItem;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.stage.Stage;
import repository.UserHibernateDBRepository;
import repository.UserRepository;
import services.LoginService;
import services.MasterService;
import utils.Observer;
import utils.UpdateEvent;

import java.io.IOException;

public class PharmacistController extends Observer {
	public Button log_btn;
	public TableView<Order> order_table;
	public TableView<OrderItem> medicinet;
	public TableColumn<Order, String> wardc, oidc, datec;
	public TableColumn<OrderItem, String> medicinec;
	public TableColumn<OrderItem, Integer> quantityc;
	public Button btn;
	private MasterService service;

	public void logout(ActionEvent actionEvent) throws IOException {
		FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("../login-view.fxml"));
		Stage stage = new Stage();
		stage.setScene(new Scene(fxmlLoader.load()));
		stage.setTitle("Login");
		LoginController loginController = fxmlLoader.getController();

		UserRepository userRepository = new UserHibernateDBRepository();
		loginController.setService(new LoginService(userRepository), service);
		stage.show();
		((Stage) (log_btn.getScene().getWindow())).close();
	}

	public void initialise() {
		order_table.setItems(FXCollections.observableArrayList(service.getPharmacistOrders()));
		wardc.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getWard().getName()));
		oidc.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getId().toString()));
		datec.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getOrderDate().toString()));
		medicinec.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getMedicine().getName()));
		quantityc.setCellValueFactory(cell -> new SimpleIntegerProperty(cell.getValue().getQuantity()).asObject());
		order_table.setOnMouseClicked(e -> {
			medicinet.setItems(FXCollections.observableArrayList(service.getOrderItems(order_table.getSelectionModel().getSelectedItem())));
		});
		btn.setOnMouseClicked(e -> {
			if (order_table.getSelectionModel().getSelectedItem() != null) {
				service.completeOrder(order_table.getSelectionModel().getSelectedItem());
				order_table.setItems(FXCollections.observableArrayList(service.getPharmacistOrders()));
			}
		});
	}

	public void setService(MasterService service) {
		this.service = service;
		initialise();
	}

	public MasterService getService() {
		return service;
	}

	@Override
	public void update(UpdateEvent updateEvent) {
		order_table.setItems(FXCollections.observableArrayList(service.getPharmacistOrders()));
	}
}
