package controller;

import domain.*;
import javafx.animation.PauseTransition;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.util.Duration;
import services.IMasterService;
import services.IUserObserver;

import java.util.ArrayList;
import java.util.List;

public class UserController implements IUserObserver {
	public Button log_btn;

	public TableView<Game> table;
	public TableColumn<Game, Integer> column1;
	public TableColumn<Game, String> column2;
	public TableColumn<Game, Integer> column3;
	public TableColumn<Game, Integer> column4;
	public GridPane grid;
	private ArrayList<ArrayList<Button>> buttons = new ArrayList<>();
	private ArrayList<String> words;
	private final int nr = 3;
	private Game game;
	private IMasterService service;

	private String user;

	private void updateTable() throws Exception {
		List<Game> games = service.getLeaderboard();
		table.setItems(FXCollections.observableArrayList(games));
	}

	private EventHandler<ActionEvent> moveHandler(int y, int x) {
		return event -> handleMove(y, x);
	}

	public void handleMove(int y, int x) {
		Button button = buttons.get(y - 1).get(x - 1);
		button.setText("X");
		button.setDisable(true);
		Move move = new Move();
		move.setY(y);
		move.setX(x);
		move.setPlayer(true);
		move.setGame(game);
		try {
			MoveReply moveReply = service.move(move);
			if (moveReply.getY() == 0) {

			} else {
				int yy = moveReply.getY(), xx = moveReply.getX();
				Button button2 = buttons.get(yy - 1).get(xx - 1);
				button2.setText("0");
				button2.setDisable(true);
			}
			if(moveReply.isEnded()){
				Alert a = new Alert(Alert.AlertType.INFORMATION);
				a.setContentText("Game over!");
				a.show();
			}
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}


	public void initialise(String user) throws Exception {
		this.user = user;
		game = service.startGame(user);
		for (int i = 1; i <= nr; ++i)
			for (int j = 1; j <= nr; ++j) {
				buttons.add(new ArrayList<Button>());
				Button button = new Button();
				buttons.get(i - 1).add(button);
				grid.add(button, j - 1, i - 1);
				button.setOnAction(moveHandler(i, j));
				button.setPrefSize(100, 100);
			}
		updateTable();
	}


	@Override
	public void notifyUpdate() {
		Platform.runLater(() ->
		{
			try {
				updateTable();
			} catch (Exception e) {
				System.out.println(e.getMessage());
			}
		});
	}

	public void setService(IMasterService service) {
		this.service = service;
//		ages.setConverter(new StringConverter<>() {
//			@Override
//			public String toString(AgeGroup object) {
//				return EnumHandler.getStringFromGroup(object);
//			}
//
//			@Override
//			public AgeGroup fromString(String string) {
//				return ages.getSelectionModel().getSelectedItem();
//			}
//		});
//		distances.setConverter(new StringConverter<>() {
//			@Override
//			public String toString(RaceDistance object) {
//				return EnumHandler.getStringFromDistance(object);
//			}
//
//			@Override
//			public RaceDistance fromString(String string) {
//				return distances.getSelectionModel().getSelectedItem();
//			}
//		});
		column1.setCellValueFactory(new PropertyValueFactory<>("id"));
		column2.setCellValueFactory(new PropertyValueFactory<>("user"));
		column3.setCellValueFactory(new PropertyValueFactory<>("points"));
		column4.setCellValueFactory(new PropertyValueFactory<>("duration"));
//		ages.setItems(FXCollections.observableArrayList(AgeGroup.values()));
//
//		ages.setOnAction(e -> {
//			distances.setItems(FXCollections.observableArrayList(EnumHandler.getRacesFromAge(ages.getValue())));
//			table.setItems(null);
//
//		});
//		distances.setOnAction(
//				e -> {
//					try {
//						updateTable();
//					} catch (Exception ex) {
//						throw new RuntimeException(ex);
//					}
//				}
//		);
	}

	public void logout() throws Exception {
		service.logOut(null);
		((Stage) (log_btn.getScene().getWindow())).close();

	}

	public void signup() {
//		try {
//			List<RaceDistance> raceDistanceList = new ArrayList<>();
//			int ageValue = Integer.parseInt(age.getText());
//			AgeGroup ageGroup = EnumHandler.getGroupFromAge(ageValue);
//			if (ageGroup == null)
//				throw new RuntimeException("Invalid age group");
//			int i = 1;
//			for (RaceDistance raceDistance : EnumHandler.getRacesFromAge(ageGroup)) {
//				CheckBox checkBox = (CheckBox) vbox.getChildren().get(i++);
//				if (checkBox.isSelected())
//					raceDistanceList.add(raceDistance);
//			}
//			if (raceDistanceList.size() > 2)
//				throw new RuntimeException("Cannot sign up to more than two races.");
//			for (RaceDistance raceDistance : raceDistanceList)
//				service.signUpChild(name.getText(), ageValue, raceDistance, ageGroup);
//		} catch (Exception e) {
//			Alert alert = new Alert(Alert.AlertType.ERROR);
//			alert.setContentText("Could not sign up child.\n" + e.getMessage());
//			alert.show();
//		}
	}

	public void updateList() {
//		try {
////			vbox.getChildren().remove(1, vbox.getChildren().size());
////			int ageValue = Integer.parseInt(age.getText());
////			AgeGroup ageGroup = EnumHandler.getGroupFromAge(ageValue);
////			if (ageGroup == null)
////				return;
////			for (RaceDistance raceDistance : EnumHandler.getRacesFromAge(ageGroup))
////				vbox.getChildren().add(new CheckBox(EnumHandler.getStringFromDistance(raceDistance)));
//		} catch (Exception ignored) {
//		}
	}
}
