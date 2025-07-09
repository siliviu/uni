package controller;

import com.sun.tools.javac.Main;
import domain.Medicine;
import domain.Order;
import domain.OrderItem;
import domain.Ward;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.Stage;
import javafx.util.StringConverter;
import repository.UserHibernateDBRepository;
import repository.UserRepository;
import services.LoginService;
import services.MasterService;
import utils.Observer;
import utils.UpdateEvent;

import java.io.IOException;
import java.util.ArrayList;


public class WardController extends Observer {
	public Button log_btn;
	public ChoiceBox<Medicine> medicines;
	public Label stock;
	public Spinner<Integer> quantity;
	public TableView<OrderItem> table;
	public Button sendbtn, addbtn;
	public TableColumn<OrderItem, String> medicinec;
	public TableColumn<OrderItem, Integer> quantityc;
	public TableView<Order> ordert;
	public TableColumn<Order, String> oidc, datec, statusc;
	private MasterService service;
	private Ward ward;

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
		class Converter extends StringConverter<Medicine> {
			@Override
			public Medicine fromString(final String name) {
				return service.getMedicineByName(name);
			}

			@Override
			public String toString(final Medicine categoryObject) {
				if (categoryObject == null)
					return null;
				return categoryObject.getName();
			}
		}
		medicinec.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getMedicine().getName()));
		quantityc.setCellValueFactory(cell -> new SimpleIntegerProperty(cell.getValue().getQuantity()).asObject());
		oidc.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getId().toString()));
		datec.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getOrderDate().toString()));
		statusc.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().getStatus().toString()));
		medicines.setConverter(new Converter());
		ordert.setItems(FXCollections.observableArrayList(service.getWardOrders(ward)));
		medicines.setItems(FXCollections.observableArrayList(service.getMedicines()));
		medicines.setOnAction(e -> {
			if (medicines.getValue() == null) {
				stock.setText("Stock:	   ");
				quantity.getValueFactory().setValue(null);
				return;
			}
			var max = medicines.getValue().getStock();
			stock.setText("Stock:	   " + max);
			quantity.setValueFactory(new SpinnerValueFactory.IntegerSpinnerValueFactory(0, max));
		});
		addbtn.setOnAction(e -> {
			if (quantity.getValue() == 0) return;
			table.getItems().add(new OrderItem(null, medicines.getValue(), quantity.getValue()));
			medicines.getItems().remove(medicines.getValue());
			medicines.setValue(null);
		});
		sendbtn.setOnAction(e -> {
			service.placeOrder(table.getItems(), ward);
			medicines.setItems(FXCollections.observableArrayList(service.getMedicines()));
			table.setItems(FXCollections.observableArrayList());
			ordert.setItems(FXCollections.observableArrayList(service.getWardOrders(ward)));
			Alert a = new Alert(Alert.AlertType.INFORMATION);
			a.setContentText("Order placed!");
			a.show();
		});
	}

	public void setWard(Ward ward) {
		this.ward = ward;
		((Stage) (log_btn.getScene().getWindow())).setTitle("Ward menu - " + ward.getName());
	}

	public void setService(MasterService service) {
		this.service = service;
		this.ward = ward;
		initialise();
	}

	public MasterService getService() {
		return service;
	}

	@Override
	public void update(UpdateEvent updateEvent) {
		medicines.setItems(FXCollections.observableArrayList(service.getMedicines()));
		ordert.setItems(FXCollections.observableArrayList(service.getWardOrders(ward)));
	}
}
