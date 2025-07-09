<head>
    <meta charset="UTF-8" />
    <link rel="stylesheet" href="style.css" />
    <title>Title</title>
</head>

<body>
    <?php
    require_once "../config.php";
    $page = 0;
    if (isset($_GET['page']))
        $page = $_GET['page'];
    $page_size = 3;
    if (isset($_GET['size']))
        $page_size = $_GET['size'];
    $conn = new PDO($db_path);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $result = $conn->query("SELECT COUNT(*) 'cnt' FROM pb6");
    if ($row = $result->fetch(PDO::FETCH_ASSOC))
        $max = intdiv(($row['cnt'] - 1), $page_size);
    $prev = max(0, $page - 1);
    $next = min($max, $page + 1);
    $page = $page + 1;
    $max = $max + 1;
    echo "
    <div class=container>
    <div class='nav'>
    <a class='prev' href='index.php?page=$prev&size=$page_size'>&lt;</a>
    <label>$page/$max</label>
    <a class='next' href='index.php?page=$next&size=$page_size'>&gt;</a>
    <form action='index.php' method='get' style='display:inline-block'>
    <input type='hidden' name='page' value=0>
    <select name='size'>";
    $page = $page - 1;
    $max = $max - 1;
    for ($i = 1; $i <= 4; $i++)
        echo "<option " . ($i == $page_size ? "selected" : "") . " value='$i'>$i</option>";
    echo "</select>
        <input type='submit' value='Change page size'>
        </form>
    </div>";
    echo "<table>
        <thead>
            <td>name</td>
            <td>producer</td>
            <td>cpu</td>
            <td>memory</td>
            <td>storage</td>
        </thead>";

    $start = $page * $page_size;
    $result = $conn->prepare("SELECT * FROM pb6 LIMIT :page_size OFFSET :start");
    $result->bindParam(":page_size", $page_size, PDO::PARAM_INT);
    $result->bindParam(":start", $start, PDO::PARAM_INT);
    $result->execute();
    while ($row = $result->fetch(PDO::FETCH_ASSOC)) {
        $name = $row['name'];
        $producer = $row['producer'];
        $cpu = $row['cpu'];
        $memory = $row['memory'];
        $storage = $row['storage'];
        echo "
            <tr>
            <td> $name </td>
            <td> $producer </td>
            <td> $cpu </td>
            <td> $memory </td>
            <td> $storage </td>
            </tr>
            ";
    }
    ?>
    </table>
    </div>
</body>