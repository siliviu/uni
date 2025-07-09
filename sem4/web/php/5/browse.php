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

$result = $conn->prepare("SELECT uploads.path AS path, auth.user name FROM uploads INNER JOIN auth ON uploads.user=auth.id");
$result->execute();
while ($row = $result->fetch(PDO::FETCH_ASSOC)) {
    $path = $row['path'];
    $user = $row['name'];
    echo "User: $user<br>";
    echo "<img src=uploads/" . $path . "> </img> ";
    echo "<br><br>";
}

?>
<a href='home.php'>Back</a>

