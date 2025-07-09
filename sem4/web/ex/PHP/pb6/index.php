<?php
session_start();
require_once '../utils.php';

if (!isset($_SESSION['token']))
    $_SESSION['token'] = md5(uniqid(mt_rand(), true));

function getComentarii() {
    $db = connect();
    $sql = $db->prepare('SELECT * FROM comentarii WHERE accepted = 1');
    $sql->execute();
    return $sql->fetchAll();
}

echo '<a href="login.html">Login as administrator</a><br>';

include 'articol.html';

echo '<h3>Comentarii</h3>';
$comentarii = getComentarii();
if (!$comentarii) {
    echo '<p>Nu exista comentarii</p>';
} else
    foreach ($comentarii as $comentariu) {
        echo '<div class="comentariu">';
        echo '<h4 class="autor">' . $comentariu['autor'] . '</h4>';
        echo '<p class="text">' . $comentariu['text'] . '</p>';
        echo '</div>';
    }
echo '<h3>Adauga comentariu</h3>';
echo '<form action="add.php" method="post">';
echo '<input type="hidden" name="csrftoken" value="' . $_SESSION['token'] . '">';
echo '<label for="autor">Autor</label>';
echo '<input type="text" name="autor" id="autor"><br>';
echo '<label for="text">Text</label>';
echo '<textarea name="text" id="text" cols="30" rows="5"></textarea><br>';
echo '<input type="submit" value="Adauga">';
echo '</form>';
