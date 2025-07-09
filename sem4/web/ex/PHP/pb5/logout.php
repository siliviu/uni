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

    session_destroy();
    header('Location: index.html');
