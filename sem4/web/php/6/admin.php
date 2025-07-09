<head>
    <meta charset="UTF-8" />
    <link rel="stylesheet" href="style.css" />
    <title>Title</title>
</head>
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

$result = $conn->prepare("SELECT * FROM comments WHERE state=0");
$result->execute();
while ($row = $result->fetch(PDO::FETCH_ASSOC)) {
    $user = $row['user'];
    $comment = $row['comment'];
    $id = $row['id'];
    echo "User: $user<br>";
    echo "Comment: $comment";
    $token = md5($_SESSION['uid'] . 'salty');
    echo "<form action='delete.php' method='post'>";
    echo "<input type='hidden' name='id' value='$id'>";
    echo "<input type='hidden' name='token' value='$token'>";
    echo "<input type='submit' value='Delete'>
    </form>";
    echo "<form action='approve.php' method='post'>";
    echo "<input type='hidden' name='id' value='$id'>";
    echo "<input type='hidden' name='token' value='$token'>";
    echo "<input type='submit' value='Approve'>
    </form>";
    echo "<br><br>";
}
?>
<a href='index.php'>Back</a>