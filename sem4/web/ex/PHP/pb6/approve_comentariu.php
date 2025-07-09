<?php
    session_start();
    require_once('../utils.php');
    $token = $_POST['csrftoken'];
    $csrf = $_SESSION['token'];
    if (!$token || $token !== $csrf)
    {
        echo 'Invalid CSRF token';
        header('Location: admin.php');
        return;
    }

    $db = connect();
    $sql = $db->prepare('UPDATE comentarii SET accepted = :accepted WHERE id = :id');
    $sql->bindParam(':accepted', $_POST['accepted']);
    $sql->bindParam(':id', $_POST['id']);
    $sql->execute();
    header('Location: admin.php');

