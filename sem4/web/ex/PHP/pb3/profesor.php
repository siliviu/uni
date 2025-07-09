<?php
    require_once "utils.php";
    $studenti = getStudenti();
    $discipline = getDiscipline();

    showNote();

    echo "<br><br><form action='add.php' method='POST' style='display: flex; gap: 10px'>";
    echo "<select name='student'>";
    foreach($studenti as $s)
        echo "<option value='".$s["id"]."'>".$s["nume"]."</option>";
    echo "</select>";
    echo "<br>";
    echo "<select name='disciplina'>";
    foreach($discipline as $d)
        echo "<option value='".$d["id"]."'>".$d["nume"]."</option>";
    echo "</select>";   
    echo "<input type='number' name='nota' min='1' max='10' value='5' step='0.1'>";
    echo "<input type='submit' value='Add'>";
    echo "</form>";


    echo "<a href='index.php'>Back</a>";