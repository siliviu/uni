<?php
$db_path = "sqlite:/mnt/c/Users/Liviu/Documents/p/uni/sem4/web/web.db";
$page_size = 3;
try {
    $conn = new PDO($db_path);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $result = $conn->query("SELECT COUNT(*) 'cnt' FROM pb2");
    if ($row = $result->fetch(PDO::FETCH_ASSOC))
        echo (intdiv($row['cnt'], $page_size));
    $conn = null;
} catch (PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}
