module map.lab7 {
	requires javafx.controls;
	requires javafx.fxml;
	requires java.sql;
	requires atlantafx.base;


	exports map.lab7;
	opens map.lab7 to javafx.fxml;
	exports map.lab7.controller;
	opens map.lab7.controller to javafx.fxml;
	exports map.lab7.domain;
	opens map.lab7.domain to javafx.fxml;
	exports map.lab7.service;
	opens map.lab7.service to javafx.fxml;
	exports map.lab7.util.pagination;
	opens map.lab7.util.pagination to javafx.fxml;
}