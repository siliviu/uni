<?php
session_start();
require_once "../config.php";
$path = $_POST["path"];
$user = $_POST["user"];

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

if ($user != $_SESSION['uid']) {
    header('HTTP/1.0 403 Forbidden');
    die('You can\'t delete other people\'s photos.');
}

if (empty($_POST['token']) || $_POST['token'] != md5($_SESSION['uid'] . 'salty')) {
    header('HTTP/1.0 403 Forbidden');
    die('No CSRF.');
}

if (empty($path) || empty($user)) {
    echo 'Invalid input';
    header('Location: profile.php');
    return;
}

$result = $conn->prepare("DELETE FROM uploads WHERE path=:path AND user=:id");
$result->bindParam(':path', $path);
$result->bindParam(':id', $user);
$result->execute();
header("Location: profile.php");
