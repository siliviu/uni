<?php
    session_start();
    require_once('../utils.php');
    $csrf = $_SESSION['token'];

    if (!$csrf)
    {
        echo 'Invalid CSRF token';
        header('Location: index.html');
        return;
    }

    function getImages($uid): false|array
    {
        $db = connect();
        $query = $db->prepare('SELECT * FROM images WHERE user_id = :uid');
        $query->bindParam(':uid', $uid);
        $query->execute();
        return $query->fetchAll();
    }

    $images = getImages($_SESSION['uid']);
    echo "<h1>Your images</h1>";
    echo "<div style='display: flex; flex-direction: row; flex-wrap: wrap'>";
    foreach ($images as $image)
    {
        echo "<div style='display: flex; flex-direction: column; align-items: center'>";
        echo "<img src=\"{$image['path']}\" style='width: 100px; height: 100px;'>";
        echo "<a href=\"delete.php?id={$image['id']}&csrftoken=$csrf\">Delete</a>";
        echo "</div>";
    }
    echo "</div>";

    echo "<form action=\"add.php\" method=\"post\" enctype='multipart/form-data'>";
    echo "<input type=\"hidden\" name=\"csrftoken\" value=\"$csrf\">";
    echo "<label>Choose an image: <input type=\"file\" name=\"file\" accept='image/*'></label><br>";
    echo "<input type=\"submit\" value=\"submit\">";
    echo "</form>";

    echo "<hr><p>Cauta utilizator:</p>";
    echo "<form action=\"main.php\" method=\"get\">";
    echo "<input type=\"text\" name=\"username\">";
    echo "<input type=\"submit\" value=\"Cauta\">";
    echo "</form>";

    if(!empty($_GET['username']))
    {
        $db = connect();
        $username = $_GET['username'];
        $query = $db->prepare('SELECT * FROM users WHERE username = :username');
        $query->bindParam(':username', $username);
        $query->execute();
        $result = $query->fetchAll();
        if (count($result) == 0)
        {
            echo 'Invalid username';
            header('Location: main.html');
            return;
        }
        $uid = $result[0]['id'];
        $query = $db->prepare('SELECT * FROM images WHERE user_id = :uid');
        $query->bindParam(':uid', $uid);
        $query->execute();
        $images = $query->fetchAll();
        echo "<h1>Images of $username</h1>";
        echo "<div style='display: flex; flex-direction: row; flex-wrap: wrap'>";
        foreach ($images as $image)
        {
            echo "<div style='display: flex; flex-direction: column; align-items: center'>";
            echo "<img alt=\"{$image['path']}\" src=\"{$image['path']}\" style='width: 100px; height: 100px;'>";
            echo "</div>";
        }
        echo "</div>";
    }

    echo "<hr><p>Logout:</p>";
    echo "<form action=\"logout.php\" method=\"post\">";
    echo "<input type=\"hidden\" name=\"csrftoken\" value=\"$csrf\">";
    echo "<input type=\"submit\" value=\"Logout\">";
    echo "</form>";



