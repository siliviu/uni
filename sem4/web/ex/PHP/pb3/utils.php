<?php
    require_once "../utils.php";
    function getNote(): false|array
    {
        $db = connect("pb3");
        $sql = $db->prepare("SELECT S.cod, D.nume, nota FROM Note 
                INNER JOIN Discipline D on D.id = Note.disciplina_id 
                INNER JOIN Studenti S on Note.student_id = S.id");
        $sql->execute();
        return $sql->fetchAll(PDO::FETCH_ASSOC);
    }

    function showNote(): void
    {
        $note = getNote();
        if($note === false)
            die("Error");
        echo "<table border='1'>";
        echo "<tr><th>Cod</th><th>Nume</th><th>Nota</th></tr>";
        foreach($note as $n)
        {
            echo "<tr>";
            echo "<td>".$n["cod"]."</td>";
            echo "<td>".$n["nume"]."</td>";
            echo "<td>".$n["nota"]."</td>";
            echo "</tr>";
        }
        echo "</table>";
    }

    function getStudenti(): false|array
    {
        $db = connect("pb3");
        $sql = $db->prepare("SELECT * FROM Studenti");
        $sql->execute();
        return $sql->fetchAll(PDO::FETCH_ASSOC);
    }

    function getDiscipline(): false|array
    {
        $db = connect("pb3");
        $sql = $db->prepare("SELECT * FROM Discipline");
        $sql->execute();
        return $sql->fetchAll(PDO::FETCH_ASSOC);
    }

