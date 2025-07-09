<?php

    function validate($nrpg, $n): bool
    {
        // check if these are numbers
        if (!is_numeric($nrpg) || !is_numeric($n))
        {
            echo "Non numeric input";
            return false;
        }

        // check if these are integers
        if ($nrpg != (int)$nrpg || $n != (int)$n)
        {
            echo "Non integer input";
            return false;
        }

        // check if these are positive
        if ($nrpg < 0 || $n < 0)
        {
            echo "Non positive input";
            return false;
        }
        return true;
    }

    function printdata($data): void
    {
        echo "<table>";
        echo "<tr>";
        echo "<th>nume</th>";
        echo "<th>producator</th>";
        echo "<th>procesor</th>";
        echo "<th>memorie</th>";
        echo "</tr>";
        foreach ($data as $row)
        {
            // echo safe values
            echo "<tr>";
            echo "<td>" . htmlspecialchars($row["nume"]) . "</td>";
            echo "<td>" . htmlspecialchars($row["producator"]) . "</td>";
            echo "<td>" . htmlspecialchars($row["procesor"]) . "</td>";
            echo "<td>" . htmlspecialchars($row["memorie"]) . "</td>";
            echo "</tr>";
        }
        echo "</table>";
    }

    function printform($nrpg, $n): void
    {
        echo "<form action=\"main.php\" method=\"get\">";
        echo "<input type=\"hidden\" name=\"nrpg\" value=\"0\">";
        echo "<input type=\"number\" name=\"n\" value=\"$n\" min='0'>";
        echo "<input type=\"submit\" value=\"submit\">";
        echo "</form>";
    }

    require_once "../utils.php";
    $db = connect();
    // table name: pb6
    // fields: nume, producator, procesor, memorie
    // put default values
    if (!isset($_GET["nrpg"]))
        $_GET["nrpg"] = 0;
    if (!isset($_GET["n"]))
        $_GET["n"] = 3;
    $nrpg = $_GET["nrpg"];
    $n = $_GET["n"];

    if (!validate($nrpg, $n))
        return;

    $sql = $db->prepare("SELECT * FROM pb6 LIMIT :nrpg, :n");
    $sql->bindParam(":nrpg", $nrpg, PDO::PARAM_INT);
    $sql->bindParam(":n", $n, PDO::PARAM_INT);
    $sql->execute();
    $result = $sql->fetchAll();

    printform($nrpg, $n);
    printdata($result);

    $next = $nrpg + $n;
    $prev = $nrpg - $n;

    if($nrpg > 0)
        echo "<a href=\"main.php?nrpg=$prev&n=$n\">Previous</a>";
    if(count($result) - $n == 0)
        echo "<a href=\"main.php?nrpg=$next&n=$n\">Next</a>";

    $db = null;