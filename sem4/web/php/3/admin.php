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

$result = $conn->prepare("SELECT * FROM Student");
$result->execute();

echo "<br><br><form action='add.php' method='POST'>";
echo "<select name='student'>";
echo "<option disabled selected>Student</option>";
while ($row = $result->fetch(PDO::FETCH_ASSOC))
    echo "<option value=" . $row['student_id'] . ">" .  $row['name'] . "</option>";
echo "</select>";
echo "<br>";
echo "<select name='subject'>";
echo "<option disabled selected>Subject</option>";
$result = $conn->prepare("SELECT * FROM Subject");
$result->execute();
while ($row = $result->fetch(PDO::FETCH_ASSOC))
    echo "<option value=" . $row['subject_id'] . ">" .  $row['name'] . "</option>";
echo "</select><br/>";
echo "<input type='number' name='grade' min='1' max='10' value='5' step='1'> <br>";
$token = md5($_SESSION['uid'] . 'salty');
echo '<input type="hidden" name="token" value="' . $token . '">';
echo "<input type='submit' value='Add'>";
echo "</form>";

?>
<a href='index.php'>Back</a>