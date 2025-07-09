<?php
$db_path = "sqlite:/mnt/c/Users/Liviu/Documents/p/uni/sem4/web/web.db";
try {
    $conn = new PDO($db_path);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $id = $_GET['id'];
    $queryString = "SELECT * FROM pb5 WHERE parent=$id";
    $result = $conn->query($queryString);
    $arr = array();
    while ($row = $result->fetch(PDO::FETCH_ASSOC))
        array_push($arr, json_encode($row));
    echo json_encode($arr);
    $conn = null;
} catch (PDOException $e) {
    echo $e->getMessage();
}
