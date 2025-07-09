<?php
session_start();
require_once "../config.php";
$student = $_POST["student"];
$subject = $_POST["subject"];
$grade = $_POST["grade"];

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

if (empty($student) || empty($subject) || empty($grade)) {
    echo 'Invalid input';
    header('Location: index.php');
    return;
}

$conn = new PDO($db_path);
$query = $conn->prepare("INSERT INTO GRADE (subject_id, student_id, mark) VALUES (:subject, :student, :grade)");
$query->bindParam(":subject", $subject);
$query->bindParam(":student", $student);
$query->bindParam(":grade", $grade);
$query->execute();

header('Location: admin.php');
