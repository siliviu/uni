<?php
    function connect()
    {
        $db_path = "sqlite:C:/Users/aerap/Desktop/Web/Labs/PHP/db.sqllite3";
        if(func_num_args() > 0)
            $db_path = "sqlite:C:/Users/aerap/Desktop/Web/Labs/PHP/".func_get_arg(0).".sqllite3";
        $db = new PDO($db_path) or die("cannot open db");
        return $db;
    }