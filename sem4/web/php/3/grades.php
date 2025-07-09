<head>
    <meta charset="UTF-8" />
    <link rel="stylesheet" href="style.css" />
    <title>Title</title>
</head>
<body>
    <table>
        <thead>
            <td>Subject</td>
            <td>Student</td>
            <td>Grade</td>
        </thead>
        <?php
        require_once "../config.php";
        $conn = new PDO($db_path);
        $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $queryString = "SELECT Subject.name AS subject, Student.name AS student, Grade.mark AS grade FROM Student
                        INNER JOIN GRADE on Student.student_id=grade.student_id
                        INNER JOIN SUBJECT ON Subject.subject_id=grade.subject_id";
        $result = $conn->query($queryString);
        while ($row = $result->fetch(PDO::FETCH_ASSOC)) {
            $subject = $row['subject'];
            $student = $row['student'];
            $grade = $row['grade'];
            echo "<tr>
                <td>$subject</td>
                <td>$student</td>
                <td>$grade</td>
                </tr>";
        }
        ?>
    </table>
</body>