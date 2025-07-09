<?php
    require_once "utils.php";
    showNote();

    echo "<hr><br><p>Daca sunteti profesor:</p>";
    echo "<form action='login.php' method='POST'>";
    echo "<input type='text' name='username' placeholder='Username'>";
    echo "<input type='password' name='password' placeholder='Password'>";
    echo "<input type='submit' value='Login'>";
    echo "</form>";