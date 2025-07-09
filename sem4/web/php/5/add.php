<?php
session_start();
require_once "../config.php";
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
    die('You can\'t upload photos for other people.');
}

if (empty($_POST['token']) || $_POST['token'] != md5($_SESSION['uid'] . 'salty')) {
    header('HTTP/1.0 403 Forbidden');
    die('No CSRF.');
}

if (empty($user)) {
    echo 'Invalid input';
    header('Location: profile.php');
    return;
}

$target_dir = "./uploads/";
$target_file = $target_dir . basename($_FILES["file"]["name"]);
$uploadOk = 1;
$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));

// Check if image file is a actual image or fake image
if(isset($_POST["submit"])) {
    $check = getimagesize($_FILES["file"]["tmp_name"]);
    if($check !== false) {
        echo "File is an image - " . $check["mime"] . ".";
        $uploadOk = 1;
    } else {
        echo "File is not an image.";
        $uploadOk = 0;
    }
}

// Check if file already exists
if (file_exists($target_file)) {
    $filename_without_ext = pathinfo($target_file, PATHINFO_FILENAME);
    // remove special characters
    $filename_without_ext = preg_replace('/[^A-Za-z0-9\-]/', '', $filename_without_ext);
    $target_file = $target_dir . $filename_without_ext . "1" . '.' . $imageFileType;
    echo "Sorry, file already exists. Renamed to $target_file";
}

// Check file size
if ($_FILES["file"]["size"] > 500000) {
    echo "Sorry, your file is too large.";
    $uploadOk = 0;
}

// Allow certain file formats
if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
    && $imageFileType != "gif" ) {
    echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
    $uploadOk = 0;
}

// rename target file with underscore instead of spaces
$target_file = str_replace(' ', '_', $target_file);

// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
    echo "Sorry, your file was not uploaded.";
// if everything is ok, try to upload file
} else {
    if (move_uploaded_file($_FILES["file"]["tmp_name"], $target_file)) {
        echo "The file ". htmlspecialchars( basename( $_FILES["file"]["name"])). " has been uploaded.";
    } else {
        echo "Sorry, there was an error uploading your file.";
        $uploadOk = 0;
    }
}

if($uploadOk==0)
    die();

$result = $conn->prepare("INSERT INTO uploads (path, user) VALUES (:path, :id)");
$target_file = str_replace($target_dir, "", $target_file);
$result->bindParam(':path', $target_file);
$result->bindParam(':id', $user);
$result->execute();
header("Location: profile.php");
