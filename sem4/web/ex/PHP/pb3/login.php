<?php
    require_once "../utils.php";
    require_once "utils.php";
    $username = $_POST["username"];
    $password = $_POST["password"];
    $db = connect("pb3");
    $sql = $db->prepare("SELECT * FROM Profesori WHERE nume = :username AND parola = :password");
    $sql->bindParam(":username", $username);
    $sql->bindParam(":password", $password);
    $sql->execute();
    $result = $sql->fetchAll(PDO::FETCH_ASSOC);
    if(count($result) == 0) {
        echo "Invalid username or password";
        echo "<a href='index.php'>Back</a>";
        return;
    }

    header("Location: profesor.php");