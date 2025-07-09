package com.example.template.controller;

import com.example.template.domain.*;
import com.example.template.service.Service;
import com.example.template.util.Observer;
import com.example.template.util.events.UpdateEvent;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;

import java.time.Month;
import java.util.stream.Collectors;

public class ClientController extends Observer {
	public Client user;
	public TableColumn c1, c2, c3, c11, c12, c13, c21, c22, c23, c24, c25, c26;
	public ComboBox<String> combobox, combobox1;
	public Button btn;
	public TableView<Ticket> table1, table2;
	public TableView<Flight> table3;
	public DatePicker datepicker;
	Service service;

	public void update1() {
		ObservableList<Ticket> list = FXCollections.observableArrayList(service.getTickets().stream().filter(c -> c.getUsername().equals(user.getUsername())).collect(Collectors.toList()));
		table1.setItems(list);
	}

	public void update2() {
		ObservableList<Ticket> list = FXCollections.observableArrayList(service.getTickets().stream()
				.filter(c -> c.getPurchaseTime().getYear() == 2024 && c.getPurchaseTime().getMonth() == Month.JANUARY && c.getPurchaseTime().getDayOfMonth() == 24)
				.collect(Collectors.toList()));
		table2.setItems(list);
	}

	public void update3() {
		ObservableList<Flight> list = FXCollections.observableArrayList(service.getFlights().stream()
				.filter(f -> combobox.getValue() == null || combobox.getValue().equals(f.getFrom()))
				.filter(f -> combobox1.getValue() == null || combobox1.getValue().equals(f.getTo()))
				.filter(f -> datepicker.getValue() == null || datepicker.getValue().equals(f.getDepartureTime().toLocalDate()))
				.collect(Collectors.toList()));
		table3.setItems(list);
		table3.refresh();
	}

	@Override
	public void update(UpdateEvent updateEvent) {
		update1();
		update2();
		update3();
	}

	public void setService(Service service, Client user) {
		this.service = service;
		this.user = user;
		update1();
		update2();
		update3();
		service.addObserver(this);
		combobox.setItems(FXCollections.observableArrayList(service.getFrom()));
		combobox1.setItems(FXCollections.observableArrayList(service.getTo()));
		update(UpdateEvent.ALL);
	}

	@FXML
	public void initialize() {
		c1.setCellValueFactory(new PropertyValueFactory<Ticket, String>("username"));
		c2.setCellValueFactory(new PropertyValueFactory<Ticket, String>("flightId"));
		c3.setCellValueFactory(new PropertyValueFactory<Ticket, String>("purchaseTime"));
		c11.setCellValueFactory(new PropertyValueFactory<Ticket, String>("username"));
		c12.setCellValueFactory(new PropertyValueFactory<Ticket, String>("flightId"));
		c13.setCellValueFactory(new PropertyValueFactory<Ticket, String>("purchaseTime"));
		c21.setCellValueFactory(new PropertyValueFactory<Ticket, String>("from"));
		c22.setCellValueFactory(new PropertyValueFactory<Ticket, String>("to"));
		c23.setCellValueFactory(new PropertyValueFactory<Ticket, String>("departureTime"));
		c24.setCellValueFactory(new PropertyValueFactory<Ticket, String>("landingTime"));
		c25.setCellValueFactory(new PropertyValueFactory<Ticket, String>("seats"));
		c26.setCellValueFactory(new PropertyValueFactory<Ticket, Long>("id"));
		c26.setCellFactory(param -> new TableCell<>() {
			@Override
			protected void updateItem(Object item, boolean empty) {
				super.updateItem(item, empty);
				if (empty || item == null) {
					setText(null);
					setGraphic(null);
				} else {
					setText(String.valueOf(service.getAvailable((Long) item)));
				}
			}
		});
		combobox.setOnAction(e -> update3());
		combobox1.setOnAction(e -> update3());
		datepicker.setOnAction(e -> update3());
		btn.setOnAction(e -> {
					if (!table3.getSelectionModel().isEmpty())
						service.purchaseTicket(user, table3.getSelectionModel().getSelectedItem());
				}
		);
	}
}
