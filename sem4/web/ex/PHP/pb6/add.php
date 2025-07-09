<?php
    session_start();
    require_once '../utils.php';
    $token = $_POST['csrftoken'];
    if (!$token || $token !== $_SESSION['token'])
    {
        echo 'Invalid CSRF token';
        header('Location: index.php');
        return;
    }

    $autor = $_POST['autor'];
    $text = $_POST['text'];

    if(empty($autor) || empty($text))
    {
        echo 'Invalid input';
        header('Location: index.php');
        return;
    }

    $db = connect();
    $query = $db->prepare('INSERT INTO comentarii (autor, text) VALUES (:autor, :text)');
    $query->bindParam(':autor', $autor);
    echo $text;
    $text= htmlentities($text);
    echo $text;
    // $query->bindParam(':text', htmlentities($text));
    // $query->execute();

    // header('Location: index.php');
