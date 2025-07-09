<?php
require_once "../config.php";
session_start();
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
?>

<a href="browse.php">See all pictures</a> </br>
<a href="profile.php">Go to profile</a>