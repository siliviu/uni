<?php
$db_path = "sqlite:/mnt/c/Users/Liviu/Documents/p/uni/sem4/web/web.db";
try{
    $conn = new PDO($db_path);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $page = $_GET["id"];
    $result = $conn->query("SELECT * FROM pb3 WHERE id = $page");
    if ($row = $result->fetch(PDO::FETCH_ASSOC)) 
        echo(json_encode($row));
    $conn = null;
} catch(PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}
?>

