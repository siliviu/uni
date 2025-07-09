package map.lab7.controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;
import javafx.stage.Stage;
import map.lab7.MasterGUI;
import map.lab7.domain.User;
import map.lab7.util.pagination.PaginatedService;
import map.lab7.repository.database.PaginatedUserDBRepository;
import map.lab7.service.*;
import map.lab7.util.events.UpdateEvent;
import map.lab7.util.Observer;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class MasterController extends Observer {
	public Spinner<Integer> spinner;
	public Label pageInfo;
	MasterService masterService;
	PaginatedService<Long, User> paginatedService;
	UserService userService;
	MessageService messageService;
	FriendService friendService;

	@FXML
	public TableView<User> table;
	@FXML
	public TableColumn<User, String> fName;
	@FXML
	public TableColumn<User, String> lName;

	@Override
	public void update(UpdateEvent updateEvent) {
		if (updateEvent == UpdateEvent.USER) {
			ObservableList<User> users = FXCollections.observableArrayList();
			for (User user : paginatedService.getAll())
				users.add(user);
			table.setItems(users);
			pageInfo.setText((paginatedService.getCurrentPageNumber() + 1) + "/" + (paginatedService.getMaximumPageNumber() + 1));
		}
	}

	@FXML
	public void initialize() {
		table.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
		table.setRowFactory(tableView -> {
			final TableRow<User> row = new TableRow<>();
			row.setOnContextMenuRequested(e -> {
				final ContextMenu rowMenu = new ContextMenu();
				List<User> selectedUsers = new ArrayList<>(table.getSelectionModel().getSelectedItems());

				MenuItem removeItem = new MenuItem("Remove user" + (selectedUsers.size() > 1 ? "s" : ""));
				removeItem.setOnAction(ee -> selectedUsers.forEach(user -> userService.removeUser(user.getId())));
				rowMenu.getItems().add(removeItem);

				if (selectedUsers.size() == 1) {
					MenuItem userItem = new MenuItem("User Menu");
					userItem.setOnAction(ee -> {
						FXMLLoader fxmlLoader = new FXMLLoader(MasterGUI.class.getResource("user-view.fxml"));
						try {
							Scene scene = new Scene(fxmlLoader.load());
							Stage stage = new Stage();
							UserController controller = fxmlLoader.getController();
							ClientService clientService = new ClientService(messageService, userService, friendService, selectedUsers.get(0));
							controller.setServices(clientService, userService, friendService, messageService);
							stage.setTitle("User menu");
							stage.setScene(scene);
							stage.show();
						} catch (Exception exception) {
							throw new RuntimeException(exception);
						}
					});
					rowMenu.getItems().add(userItem);
				}

				if (selectedUsers.size() == 2) {
					Long id1 = selectedUsers.get(0).getId(), id2 = selectedUsers.get(1).getId();
					if (!friendService.areFriends(id1, id2)) {
						MenuItem friendItem = new MenuItem("Make users friends");
						friendItem.setOnAction(ee -> friendService.addFriendship(id1, id2));
						rowMenu.getItems().add(friendItem);
					} else {
						MenuItem friendItem = new MenuItem("Make users not friends");
						friendItem.setOnAction(ee -> friendService.removeFriendship(id1, id2));
						rowMenu.getItems().add(friendItem);
					}
				}
				table.setContextMenu(rowMenu);
			});
			return row;
		});
		fName.setCellFactory(TextFieldTableCell.forTableColumn());
		lName.setCellFactory(TextFieldTableCell.forTableColumn());
		fName.setCellValueFactory(new PropertyValueFactory<User, String>("firstName"));
		lName.setCellValueFactory(new PropertyValueFactory<User, String>("lastName"));
		spinner.setValueFactory(new SpinnerValueFactory.IntegerSpinnerValueFactory(1, 20, 10));
		spinner.valueProperty().addListener((obs, oldValue, newValue) -> {
			paginatedService.changePageSize(newValue);
			update(UpdateEvent.USER);
		});
	}

	@FXML
	public void edit(TableColumn.CellEditEvent<User, String> event) {
		User u = event.getRowValue();
		if (event.getTableColumn().getId().equals("fName")) u.setFirstName(event.getNewValue());
		else u.setLastName(event.getNewValue());
		try {
			userService.updateUser(u.getId(), u.getFirstName(), u.getLastName());
		} catch (Exception e) {
			Alert alert = new Alert(Alert.AlertType.ERROR);
			alert.setContentText("Could not edit user.\n" + e.getMessage());
			alert.show();
		}

	}

	public void setServices(MasterService masterService, UserService userService, FriendService friendService, MessageService messageService) {
		this.paginatedService = new PaginatedService<>(new PaginatedUserDBRepository());
		this.masterService = masterService;
		this.userService = userService;
		this.friendService = friendService;
		this.messageService = messageService;
		this.userService.addObserver(paginatedService);
		this.userService.addObserver(this);
		this.friendService.addObserver(this);
		this.messageService.addObserver(this);
		update(UpdateEvent.USER);
	}

	public void addMenu(ActionEvent mouseEvent) throws IOException {
		FXMLLoader fxmlLoader = new FXMLLoader(MasterGUI.class.getResource("user-add-view.fxml"));
		Scene scene = new Scene(fxmlLoader.load());
		Stage stage = new Stage();
		UserAddController controller = fxmlLoader.getController();
		controller.setUserService(userService);
		stage.setTitle("Add user");
		stage.setResizable(false);
		stage.setScene(scene);
		stage.show();
	}

	public void previousPage(ActionEvent actionEvent) {
		paginatedService.previousPage();
		update(UpdateEvent.USER);
	}

	public void nextPage(ActionEvent actionEvent) {
		paginatedService.nextPage();
		update(UpdateEvent.USER);
	}
}