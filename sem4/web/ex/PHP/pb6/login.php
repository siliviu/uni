<?php
    session_start();
    require_once('../utils.php');
    $db = connect();
    $username = $_POST['username'];
    $password = $_POST['password'];
    $query = $db->prepare('SELECT id FROM admins WHERE username = :username AND password = :password');
    $query->bindParam(':username', $username);
    $query->bindParam(':password', $password);
    $query->execute();
    $result = $query->fetchAll();
    if (count($result) == 0)
    {
        echo 'Invalid username or password';
        header('Location: index.html');
        return;
    }

    if(!isset($_SESSION['token']))
        $_SESSION['token'] = md5(uniqid(mt_rand(), true));
    $_SESSION['uid'] = $result[0]['id'];
    header('Location: admin.php');



