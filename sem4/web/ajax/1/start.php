<?php
$db_path = "sqlite:/mnt/c/Users/Liviu/Documents/p/uni/sem4/web/web.db";
try {
    $conn = new PDO($db_path);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $result = $conn->query("SELECT DISTINCT fromCity FROM pb1");
    $arr = array();
    while ($row = $result->fetch(PDO::FETCH_ASSOC))
        array_push($arr, $row['fromCity']);
    echo json_encode($arr);
    $conn = null;
} catch (PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}
