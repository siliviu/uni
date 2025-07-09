<?php
    session_start();
    require_once('../utils.php');
    $token = $_POST['csrftoken'];
    $csrf = $_SESSION['token'];
    if (!$token || $token !== $csrf)
    {
        echo 'Invalid CSRF token';
        header('Location: main.php');
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
    echo "UPLOADED: $uploadOk";

    if($uploadOk == 1)
    {
        $db = connect();
        $uid = $_SESSION['uid'];
        $query = $db->prepare('INSERT INTO images (user_id, path) VALUES (:uid, :path)');
        $query->bindParam(':uid', $uid);
        $query->bindParam(':path', $target_file);
        $query->execute();
    }
    //header('Location: main.php');
