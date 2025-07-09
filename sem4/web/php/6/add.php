<?php
session_start();
require_once "../config.php";
$user = $_POST["user"];
$comment = $_POST["comment"];

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

if (empty($user) || empty($comment)) {
    echo 'Invalid input';
    header('Location: article.php');
    return;
}

$result = $conn->prepare("INSERT INTO comments (user, comment, state) VALUES (:user, :comment, 0)");
$result->bindParam(':user', $user);
$result->bindParam(':comment', htmlentities($comment));
$result->execute();
header("Location: article.php");
