module com.example.restaurants {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.restaurants to javafx.fxml;
    exports com.example.restaurants;
}