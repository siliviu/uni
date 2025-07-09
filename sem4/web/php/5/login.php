<?php
    require_once "../config.php";
    session_start();
    $conn = new PDO($db_path);
    $user = $_POST["user"];
    $password = $_POST["password"];
    $result = $conn->prepare("SELECT * FROM auth WHERE user = :user AND password = :password");
    $result->bindParam(":user", $user);
    $result->bindParam(":password", $password);
    $result->execute();
    $result = $result->fetchAll(PDO::FETCH_ASSOC);
    if(count($result) == 0) {
        echo "Invalid username or password</br>";
        echo "<a href='index.php'>Back</a>";
        return;
    }
    $_SESSION['uid'] = $result[0]['id'];
    header("Location: home.php")
?>