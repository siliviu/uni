<?php
    require_once "../utils.php";
    require_once "utils.php";
    $student = $_POST["student"];
    $disciplina = $_POST["disciplina"];
    $nota = $_POST["nota"];

    $db = connect("pb3");
    $sql = $db->prepare("INSERT INTO Note (disciplina_id, student_id, nota) VALUES (:disciplina, :student, :nota)");
    $sql->bindParam(":disciplina", $disciplina);
    $sql->bindParam(":student", $student);
    $sql->bindParam(":nota", $nota);
    $sql->execute();

    header("Location: profesor.php");
