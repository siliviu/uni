package map.lab7.controller;

import javafx.beans.binding.Bindings;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.*;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import map.lab7.domain.FriendRequest;
import map.lab7.domain.Message;
import map.lab7.domain.ReplyMessage;
import map.lab7.domain.User;
import map.lab7.service.ClientService;
import map.lab7.service.FriendService;
import map.lab7.service.MessageService;
import map.lab7.service.UserService;
import map.lab7.util.events.UpdateEvent;
import map.lab7.util.Observer;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;

public class UserController extends Observer {
	@FXML
	public ListView<User> user_list, friend_list;
	@FXML
	public ListView<FriendRequest> request_list;
	@FXML
	public Label userName, chatName;
	@FXML
	public Tab requestTab;
	@FXML
	public ListView<Message> message_list;
	@FXML
	public TextField text;

	UserService userService;
	MessageService messageService;
	FriendService friendService;
	ClientService clientService;
	User recipient = null;

	@Override
	public void update(UpdateEvent updateEvent) {
		if (updateEvent == UpdateEvent.REQUESTS) {
			requestTab.setText(String.format("(%d)", clientService.getFriendRequests(clientService.getUser()).size()));
			ObservableList<FriendRequest> requests = FXCollections.observableArrayList();
			requests.addAll(clientService.getFriendRequests(clientService.getUser()));
			request_list.setItems(requests);
		} else if (updateEvent == UpdateEvent.USER) {
			ObservableList<User> users = FXCollections.observableArrayList();
			for (User user : clientService.getOtherUsers())
				users.add(user);
			user_list.setItems(users);
		} else if (updateEvent == UpdateEvent.FRIEND) {
			ObservableList<User> friends = FXCollections.observableArrayList();
			for (User user : clientService.getFriends())
				friends.add(user);
			friend_list.setItems(friends);
		} else if (updateEvent == UpdateEvent.MESSAGE) {
			if (recipient == null)
				return;
			chatName.setText(recipient.getFirstName() + " " + recipient.getLastName());
			ObservableList<Message> messages = FXCollections.observableArrayList();
			for (Message message : clientService.getUserMessages(recipient.getId()))
				messages.add(message);
			message_list.setItems(messages);
			message_list.scrollTo(message_list.getItems().size());
		}
	}

	@FXML
	public void initialize() {
		user_list.setCellFactory(param -> new ListCell<User>() {
			@Override
			protected void updateItem(User item, boolean empty) {
				super.updateItem(item, empty);
				if (empty || item == null) setText(null);
				else setText(item.getFirstName() + " " + item.getLastName());
				param.setOnContextMenuRequested(e -> {
							final ContextMenu rowMenu = new ContextMenu();
							MenuItem removeItem = new MenuItem("Send friend request");
							Long idFrom = clientService.getUser().getId(), idTo = user_list.getSelectionModel().getSelectedItem().getId();
							if (!friendService.areFriends(idFrom, idTo)) {
								removeItem.setOnAction(ee -> {
									try {
										friendService.sendFriendRequest(idFrom, idTo);
									} catch (Exception exception) {
										Alert alert = new Alert(Alert.AlertType.ERROR);
										alert.setContentText("A friend request has been sent to this user before");
										alert.show();
									}
								});
								rowMenu.getItems().add(removeItem);
							}
							user_list.setContextMenu(rowMenu);
						}
				);
			}
		});
		friend_list.setCellFactory(param -> new ListCell<User>() {
			@Override
			protected void updateItem(User item, boolean empty) {
				super.updateItem(item, empty);
				if (empty || item == null) setText(null);
				else setText(item.getFirstName() + " " + item.getLastName());
				param.setOnContextMenuRequested(e -> {
							final ContextMenu rowMenu = new ContextMenu();
							MenuItem removeItem = new MenuItem("Remove friend");
							removeItem.setOnAction(ee -> friendService.removeFriendship(clientService.getUser().getId(), friend_list.getSelectionModel().getSelectedItem().getId()));
							rowMenu.getItems().add(removeItem);
							friend_list.setContextMenu(rowMenu);
						}
				);
			}
		});
		request_list.setCellFactory(param -> new ListCell<FriendRequest>() {
			@Override
			protected void updateItem(FriendRequest item, boolean empty) {
				super.updateItem(item, empty);
				if (empty || item == null) setText(null);
				else {
					User user = userService.getUser(item.getId().getLeft());
					setText(user.getFirstName() + " " + user.getLastName());
				}
				param.setOnContextMenuRequested(e -> {
							final ContextMenu rowMenu = new ContextMenu();

							MenuItem acceptItem = new MenuItem("Accept friend request");
							acceptItem.setOnAction(ee -> friendService.acceptFriendRequest(request_list.getSelectionModel().getSelectedItem()));
							rowMenu.getItems().add(acceptItem);


							MenuItem rejectItem = new MenuItem("Reject friend request");
							rejectItem.setOnAction(ee -> friendService.rejectFriendRequest(request_list.getSelectionModel().getSelectedItem()));
							rowMenu.getItems().add(rejectItem);

							request_list.setContextMenu(rowMenu);
						}
				);
			}
		});
		message_list.setCellFactory(param -> new ListCell<Message>() {
			@Override
			protected void updateItem(Message item, boolean empty) {
				super.updateItem(item, empty);
				if (empty || item == null) {
					setText(null);
					setGraphic(null);
				} else {
					VBox vbox = new VBox();
					vbox.setPadding(new Insets(7));
					boolean right = clientService.getUser().getId() == item.getFrom();
					vbox.setStyle("-fx-background-color:" + (right ? "#0d419d" : "#051d4d") + ";-fx-background-radius: 10;");
					setAlignment(right ? Pos.CENTER_RIGHT : Pos.CENTER_LEFT);

					vbox.maxWidthProperty().bind(Bindings.divide(widthProperty(), 3));
					vbox.prefWidthProperty().bind(Bindings.divide(widthProperty(), 3));

					if (item instanceof ReplyMessage) {
						Label reply = new Label();
						Message source = messageService.getMessage(((ReplyMessage) item).getSourceid());
						reply.setText(userService.getUser(source.getFrom()).getFirstName() + ": " + source.getMessage());
						reply.setFont(new Font(12));
						reply.setPadding((new Insets(0, 0, 0, 5)));
						reply.setStyle("-fx-border-style: hidden hidden hidden solid; -fx-border-width:2; -fx-border-color: #2da44e;");
						vbox.getChildren().add(reply);
					}

					Label date = new Label();
					date.setText(DateTimeFormatter.ofPattern(ChronoUnit.HOURS.between(item.getDate(), LocalDateTime.now()) >= 24 ?
							"MM/dd" : "hh:mm a").format(item.getDate()));
					date.setFont(new Font(10));
					vbox.getChildren().add(date);

					Label message = new Label(item.getMessage());
					message.setWrapText(true);

					message.prefWidthProperty().bind(Bindings.subtract(Bindings.divide(widthProperty(), 3), 2 * 5));
					vbox.getChildren().add(message);

					setPadding(new Insets(10));
					setStyle("-fx-cell-size: -1;");
					setGraphic(vbox);

					addEventFilter(MouseEvent.MOUSE_PRESSED, e -> {
						if (message_list.getSelectionModel().getSelectedItem() == getItem()) {
							message_list.getSelectionModel().clearSelection();
							e.consume();
						}
					});
				}
			}
		});
		user_list.getSelectionModel().selectedItemProperty().addListener(e -> {
			recipient = user_list.getSelectionModel().getSelectedItem();
			update(UpdateEvent.MESSAGE);
		});
		friend_list.getSelectionModel().selectedItemProperty().addListener(e -> {
			recipient = friend_list.getSelectionModel().getSelectedItem();
			update(UpdateEvent.MESSAGE);
		});
	}

	public void setServices(ClientService service, UserService userService, FriendService friendService, MessageService messageService) {
		this.clientService = service;
		this.userService = userService;
		this.messageService = messageService;
		this.friendService = friendService;
		userName.setText(service.getUser().getFirstName());
		this.userService.addObserver(this);
		this.messageService.addObserver(this);
		this.friendService.addObserver(this);
		update(UpdateEvent.USER);
		update(UpdateEvent.FRIEND);
		update(UpdateEvent.REQUESTS);
	}

	public void sendMessage() {
		String content = text.getText();
		if (recipient != null && !content.isEmpty())
			clientService.sendMessage(recipient.getId(), content, message_list.getSelectionModel().isEmpty() ? null : message_list.getSelectionModel().getSelectedItem().getId());
		message_list.getSelectionModel().clearSelection();
		text.clear();
		text.requestFocus();
	}
}
