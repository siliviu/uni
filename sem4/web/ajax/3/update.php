<?php
$db_path = "sqlite:/mnt/c/Users/Liviu/Documents/p/uni/sem4/web/web.db";
$conn = new PDO($db_path);
$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$person = json_decode(file_get_contents("php://input"));
$conn->query("UPDATE pb3 SET name='$person->name', email='$person->email', phone='$person->phone' WHERE id=$person->id");
$conn = null;
echo 'ok';
