<?php
$db_path = "sqlite:/mnt/c/Users/Liviu/Documents/p/uni/sem4/web/web.db";
try {
    $conn = new PDO($db_path);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $attr = $_GET['attr'];
    $result = $conn->query("SELECT DISTINCT $attr FROM pb6 ORDER BY $attr");
    $arr = array();
    while ($row = $result->fetch(PDO::FETCH_ASSOC))
        array_push($arr, $row[$attr]);
    echo json_encode($arr);
    $conn = null;
} catch (PDOException $e) {
    echo $e->getMessage();
}
