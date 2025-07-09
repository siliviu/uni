<?php
    session_start();
    require_once('../utils.php');
    $token = $_GET['csrftoken'];
    $csrf = $_SESSION['token'];
    if (!$token || $token !== $csrf)
    {
        echo 'Invalid CSRF token';
        header('Location: main.php');
        return;
    }

    $id = $_GET['id'];
    $db = connect();
    $query = $db->prepare('DELETE FROM images WHERE id = :id');
    $query->bindParam(':id', $id);
    $query->execute();
    header('Location: main.php');
