<?php
$db_path = "sqlite:/mnt/c/Users/Liviu/Documents/p/uni/sem4/web/web.db";
$page_size = 3;
try {
    $conn = new PDO($db_path);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $page = $_GET["page"];
    $start = $page * $page_size;
    $result = $conn->query("SELECT * FROM pb2 LIMIT $page_size OFFSET $start");
    $arr = array();
    while ($row = $result->fetch(PDO::FETCH_ASSOC))
        array_push($arr, json_encode($row));
    echo json_encode($arr);
    $conn = null;
} catch (PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}
