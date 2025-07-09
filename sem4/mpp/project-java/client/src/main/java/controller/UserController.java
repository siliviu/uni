package controller;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.util.StringConverter;
import domain.AgeGroup;
import domain.dto.ChildDTO;
import domain.RaceDistance;
import services.IMasterService;
import services.IUserObserver;
import utils.EnumHandler;

import java.util.ArrayList;
import java.util.List;

public class UserController implements IUserObserver {
	public Button log_btn;
	public ChoiceBox<AgeGroup> ages;
	public ChoiceBox<RaceDistance> distances;
	public TableView<ChildDTO> table;
	public TableColumn<ChildDTO, String> nameColumn;
	public TableColumn<ChildDTO, Integer> ageColumn, signColumn;
	public TextField name;
	public TextField age;
	public VBox vbox;
	private IMasterService service;

	private void updateTable() throws Exception {
		if (ages.getValue() == null || distances.getValue() == null)
			return;
		List<ChildDTO> children = service.searchChildren(distances.getValue(), ages.getValue());
		table.setItems(FXCollections.observableArrayList(children));
	}

	@Override
	public void notifySignup() {
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
		ages.setConverter(new StringConverter<>() {
			@Override
			public String toString(AgeGroup object) {
				return EnumHandler.getStringFromGroup(object);
			}

			@Override
			public AgeGroup fromString(String string) {
				return ages.getSelectionModel().getSelectedItem();
			}
		});
		distances.setConverter(new StringConverter<>() {
			@Override
			public String toString(RaceDistance object) {
				return EnumHandler.getStringFromDistance(object);
			}

			@Override
			public RaceDistance fromString(String string) {
				return distances.getSelectionModel().getSelectedItem();
			}
		});
		nameColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
		ageColumn.setCellValueFactory(new PropertyValueFactory<>("age"));
		signColumn.setCellValueFactory(new PropertyValueFactory<>("signups"));
		ages.setItems(FXCollections.observableArrayList(AgeGroup.values()));

		ages.setOnAction(e -> {
			distances.setItems(FXCollections.observableArrayList(EnumHandler.getRacesFromAge(ages.getValue())));
			table.setItems(null);

		});
		distances.setOnAction(
				e -> {
					try {
						updateTable();
					} catch (Exception ex) {
						throw new RuntimeException(ex);
					}
				}
		);
	}

	public void logout() throws Exception {
		service.logOut(null);
		((Stage) (log_btn.getScene().getWindow())).close();

	}

	public void signup() {
		try {
			List<RaceDistance> raceDistanceList = new ArrayList<>();
			int ageValue = Integer.parseInt(age.getText());
			AgeGroup ageGroup = EnumHandler.getGroupFromAge(ageValue);
			if (ageGroup == null)
				throw new RuntimeException("Invalid age group");
			int i = 1;
			for (RaceDistance raceDistance : EnumHandler.getRacesFromAge(ageGroup)) {
				CheckBox checkBox = (CheckBox) vbox.getChildren().get(i++);
				if (checkBox.isSelected())
					raceDistanceList.add(raceDistance);
			}
			if (raceDistanceList.size() > 2)
				throw new RuntimeException("Cannot sign up to more than two races.");
			for (RaceDistance raceDistance : raceDistanceList)
				service.signUpChild(name.getText(), ageValue, raceDistance, ageGroup);
		} catch (Exception e) {
			Alert alert = new Alert(Alert.AlertType.ERROR);
			alert.setContentText("Could not sign up child.\n" + e.getMessage());
			alert.show();
		}
	}

	public void updateList() {
		try {
			vbox.getChildren().remove(1, vbox.getChildren().size());
			int ageValue = Integer.parseInt(age.getText());
			AgeGroup ageGroup = EnumHandler.getGroupFromAge(ageValue);
			if (ageGroup == null)
				return;
			for (RaceDistance raceDistance : EnumHandler.getRacesFromAge(ageGroup))
				vbox.getChildren().add(new CheckBox(EnumHandler.getStringFromDistance(raceDistance)));
		} catch (Exception ignored) {
		}
	}

}
