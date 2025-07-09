<?php
$n = 3;
$db_path = "sqlite:/mnt/c/Users/Liviu/Documents/p/uni/sem4/web/web.db";


function check($conn, $y, $x) {
    $result = $conn->query("SELECT * FROM pb4 WHERE Y=$y AND X=$x");
    if ($row = $result->fetch(PDO::FETCH_ASSOC))
        return false;
    return true;
}

function getTurn($conn) {
    $cnt0 = 0;
    $cntX = 0;
    $result = $conn->query("SELECT * FROM pb4");
    while ($row = $result->fetch(PDO::FETCH_ASSOC))
        if ($row['turn'] == '1')
            ++$cntX;
        else
            ++$cnt0;
    if ($cnt0 < $cntX)
        return 0;
    return 1;
}

function checkEnd($conn) {
    $array = array(
        array(-1, -1, -1),
        array(-1, -1, -1),
        array(-1, -1, -1),
    );
    $result = $conn->query("SELECT * FROM pb4");
    while ($row = $result->fetch(PDO::FETCH_ASSOC))
        $array[$row['Y']][$row['X']] = $row['turn'];
    if ($array[0][0] != -1) {
        if (($array[0][0] == $array[0][1] && $array[0][1] == $array[0][2]) ||
            ($array[0][0] == $array[1][0] && $array[1][0] == $array[2][0])
        )
            return true;
    }
    if ($array[2][2] != -1) {
        if (($array[2][0] == $array[2][1] && $array[2][1] == $array[2][2]) ||
            ($array[0][2] == $array[1][2] && $array[1][2] == $array[2][2])
        )
            return true;
    }
    if ($array[1][1] != -1) {
        if (($array[1][0] == $array[1][1] && $array[1][1] == $array[1][2]) ||
            ($array[0][1] == $array[1][1] && $array[1][1] == $array[2][1]) ||
            ($array[0][0] == $array[1][1] && $array[1][1] == $array[2][2]) ||
            ($array[0][2] == $array[1][1] && $array[1][1] == $array[2][0])
        )
            return true;
    }
    return false;
}

try {
    $yy = $_GET["y"];
    $xx = $_GET["x"];
    $conn = new PDO($db_path);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    if (check($conn, $yy, $xx)) {
        $turn = getTurn($conn);
        $conn->query("INSERT INTO pb4 (turn, Y,X) VALUES ($turn, $yy, $xx)");
        $turn ^= 1;
        if (checkEnd($conn))
            $result->end = 1;
        else {
            do {
                $result->y = rand(0, $n - 1);
                $result->x = rand(0, $n - 1);
            } while (!check($conn, $result->y, $result->x));
            $conn->query("INSERT INTO pb4 (turn, Y, X) VALUES ($turn, $result->y,$result->x)");
            if (checkEnd($conn))
                $result->end = 2;
        }
        echo (json_encode($result));
        $conn = null;
    }
} catch (PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}
