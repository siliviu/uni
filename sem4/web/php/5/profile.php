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

echo "<span style='font-size:2em'>My profile</span> <br><br>";


echo "<form action='add.php' method='post' enctype='multipart/form-data'>";
$token = md5($_SESSION['uid'] . 'salty');
echo "<input type='hidden' name='token' value='$token'>";
echo "<label>Choose an image: <input type='file' name='file' accept='image/*'></label><br>";
$id = $_SESSION['uid'];
echo "<input type='hidden' name='user' value='$id'>";
echo "<input type='submit' value='Upload'>";
echo "</form>";
echo "<br/>";

$result = $conn->prepare("SELECT * FROM uploads WHERE user=:id");
$result->bindParam(':id', $_SESSION['uid']);
$result->execute();
while ($row = $result->fetch(PDO::FETCH_ASSOC)) {
    $path = $row['path'];
    echo "<img src=uploads/" . $path . "> </img> ";
    echo "<form action='delete.php' method='post'>";
    echo "<input type='hidden' name='user' value='$id'>";
    echo "<input type='hidden' name='path' value='$path'>";
    echo "<input type='hidden' name='token' value='$token'>";
    echo "<input type='submit' value='Delete'>
    </form>";
    echo "<br>";
}
?>
<a href='home.php'>Back</a>