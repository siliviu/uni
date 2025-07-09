<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
    <style>
        .accepted {
            background-color: green;
        }
        .rejected {
            background-color: red;
        }
        .container {
            display: flex;
            flex-direction: column;
            flex-wrap: nowrap;
            gap: 10px;
        }
        .comentariu{
            padding: 10px;
        }
        h4{
            padding: 0;
            margin: 0 0 0 30px;
        }
    </style>
</head>
<body>
<?php
    session_start();
    require_once '../utils.php';
    $token = $_SESSION['token'];
    $db = connect();
    $sql = $db->prepare('SELECT * FROM comentarii');
    $sql->execute();
    $comentarii = $sql->fetchAll();
?>
  <p> Welcome! </p>

    <h3>Comentarii</h3>
    <div class="container">
        <?php
            foreach ($comentarii as $comentariu) {
                $class = '';
                if($comentariu['accepted'] == 1)
                    $class = 'accepted';
                else if($comentariu['accepted'] == 2)
                    $class = 'rejected';
                echo '<div class="comentariu ' . $class . '">';
                echo '<h4 class="autor">' . $comentariu['autor'] . '</h4>';
                echo '<textarea class="text" cols="30" rows="5" readonly>' . $comentariu['text'] . '</textarea>';
                echo '<form action="approve_comentariu.php" method="post">';
                echo '<input type="hidden" name="csrftoken" value="' . $token . '">';
                echo '<input type="hidden" name="id" value="' . $comentariu['id'] . '">';
                echo '<input type="hidden" name="accepted" value="1">';
                echo '<input type="submit" value="Accept">';
                echo '</form>';
                echo '<form action="approve_comentariu.php" method="post">';
                echo '<input type="hidden" name="csrftoken" value="' . $token . '">';
                echo '<input type="hidden" name="id" value="' . $comentariu['id'] . '">';
                echo '<input type="hidden" name="accepted" value="2">';
                echo '<input type="submit" value="Reject">';
                echo '</form>';
                echo '</div>';
            }
        ?>
    </div>
    <br><hr>
  <form action="logout.php" method="post">
    <input type="hidden" name="csrftoken" value="<?php echo $token; ?>">
    <input type="submit" value="Logout">
  </form>
</body>
</html>