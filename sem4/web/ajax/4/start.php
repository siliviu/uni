<?php
$n = 3;
$db_path = "sqlite:/mnt/c/Users/Liviu/Documents/p/uni/sem4/web/web.db";
try {
    $conn = new PDO($db_path);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $conn->query("DELETE FROM pb4");
    $result->turn = rand(0, 1);
    if ($result->turn == 1) {
        $result->y = rand(0, $n - 1);
        $result->x = rand(0, $n - 1);
        $conn->query("INSERT INTO pb4 (turn, Y,X) VALUES (1, '$result->y','$result->x')");
    }
    echo (json_encode($result));
    $conn = null;
} catch (PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}
