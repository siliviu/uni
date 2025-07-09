<?php
session_start();
require_once "../config.php";
$id = $_POST["id"];

if (!isset($_SESSION['uid'])) {
    header('HTTP/1.0 403 Forbidden');
    die('You are not logged in.');
}
$conn = new PDO($db_path);
$result = $conn->prepare("SELECT * FROM auth WHERE id=:id");
$result->bindParam(':id', $_SESSION['uid']);
$result->execute();
if (count($result) == 0) {
    header('HTTP/1.0 403 Forbidden');
    die('You are not logged in.');
}

    if (empty($_POST['token']) || $_POST['token'] != md5($_SESSION['uid'] . 'salty')) {
    header('HTTP/1.0 403 Forbidden');
    die('No CSRF.');
}

if (empty($id)) {
    echo 'Invalid input';
    header('Location: profile.php');
    return;
}

$result = $conn->prepare("DELETE FROM comments WHERE id=:id");
$result->bindParam(':id', $id);
$result->execute();
header("Location: admin.php");
