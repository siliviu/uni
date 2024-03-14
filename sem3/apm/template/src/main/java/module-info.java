module com.example.template {
    requires javafx.controls;
    requires javafx.fxml;
	requires java.sql;


	opens com.example.template to javafx.fxml;
	opens com.example.template.domain to javafx.base;
    exports com.example.template;
	exports com.example.template.controller;
	opens com.example.template.controller to javafx.fxml;
}