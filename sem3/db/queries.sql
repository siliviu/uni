USE LanguageCentre

-- Print a list of each pupil and the classes/courses he takes
SELECT p.pupil_id, p.name "Name", c.name "Class", co.name "Course"
FROM Enrollments e
JOIN Pupils p
ON e.pupil_id=p.pupil_id
JOIN Classes c
ON c.class_id=e.class_id
JOIN Courses co
ON c.course_id=co.course_id

-- Print a list of all the courses with the number of classes available and language
-- Using count subquery
SELECT co.name "Course", l.name "Language Name", co.difficulty "Difficulty", co.length "Duration (weeks)", co.description "Description",
(SELECT COUNT(*) FROM Classes WHERE course_id=co.course_id) "Number of classes",
(SELECT STRING_AGG(name,', ') FROM Classes WHERE course_id=co.course_id) "Classes",
(SELECT COUNT(*) FROM Pupils s JOIN Enrollments e ON s.pupil_id=e.pupil_id WHERE e.class_id IN (SELECT class_id FROM Classes WHERE course_id=co.course_id)) "Number of studens"
FROM Courses co
INNER JOIN Languages l
ON co.language_id=l.language_id

-- Print a list of all classes with the course, teacher names
SELECT cl.name "Class", co.name "Course", co.difficulty "Difficulty", 
(SELECT STRING_AGG(t.name,', ') 
	FROM Teachers t 
	JOIN Contracts c
	ON t.teacher_id=c.teacher_id
	JOIN Classes cls
	ON c.class_id=cls.class_id
	WHERE cl.class_id=cls.class_id
) "Teachers",
(SELECT COUNT(*) FROM Pupils s JOIN Enrollments e ON s.pupil_id=e.pupil_id WHERE e.class_id = cl.class_id) "Number of students"
FROM Classes cl
JOIN Courses co
ON cl.course_id=co.course_id

-- Print results of all pupils
SELECT p.name Name, CONCAT(r.score,'/',e.max_score) Score, c.name Course
FROM Evaluations e
JOIN Results r
ON e.evaluation_id=r.evaluation_id
JOIN Courses c
ON c.course_id=e.course_id
JOIN Pupils p
ON p.pupil_id=r.pupil_id
ORDER BY c.name

-- Select all teachers who don't teach courses in a language they're qualified for
SELECT t.name, l.name language, k.level
FROM Teacher_Knowledge k
JOIN Languages l
ON k.language_id=l.language_id
JOIN Teachers t
ON k.teacher_id=t.teacher_id
WHERE NOT EXISTS (
	SELECT 1
	FROM Contracts ct
	JOIN Teachers tt
	ON ct.teacher_id=tt.teacher_id
	JOIN Classes cl
	ON ct.class_id=cl.class_id
	JOIN Courses co
	ON co.course_id=cl.course_id
	JOIN languages ll
	ON ll.language_id=co.language_id
	WHERE tt.name = t.name AND ll.name = l.name
)

-- Select the languages each person speaks
SELECT p.name, pl.name language, pk.level, 'Pupil' type
FROM Pupil_Knowledge pk
JOIN Languages pl
ON pl.language_id=pk.language_id
JOIN Pupils p
ON p.pupil_id=pk.pupil_id
UNION
SELECT t.name, tl.name language, tk.level, 'Teacher' type
FROM Teacher_Knowledge tk
JOIN Languages tl
ON tl.language_id=tk.language_id
JOIN Teachers t
ON t.teacher_id=tk.teacher_id

-- Select the people who speak 2 languages from (Spanish, French and German)
SELECT p.name
FROM Pupil_Knowledge pk
JOIN Languages pl
ON pl.language_id=pk.language_id
JOIN Pupils p
ON p.pupil_id=pk.pupil_id
WHERE pl.name = 'Spanish' OR pl.name = 'French' or pl.name = 'German'
GROUP BY p.name
HAVING COUNT(p.name) = 2
UNION
SELECT t.name
FROM Teacher_Knowledge tk
JOIN Languages tl
ON tl.language_id=tk.language_id
JOIN Teachers t
ON t.teacher_id=tk.teacher_id
WHERE tl.name IN ('Spanish', 'French', 'German')
GROUP BY t.name
HAVING COUNT(t.name) = 2

-- Select pupils who are Advanced in a language and a Beginner in another language
SELECT p.name
FROM Pupil_Knowledge pk
JOIN Languages pl
ON pl.language_id=pk.language_id
JOIN Pupils p
ON p.pupil_id=pk.pupil_id
WHERE pk.level = 'Advanced'
INTERSECT
SELECT p.name
FROM Pupil_Knowledge pk
JOIN Languages pl
ON pl.language_id=pk.language_id
JOIN Pupils p
ON p.pupil_id=pk.pupil_id
WHERE pk.level = 'Beginner'

-- Select pupils who are taking a course for a language they don't know
-- Except
SELECT pp.name,ll.name
FROM Enrollments e
JOIN Pupils pp
ON pp.pupil_id=e.pupil_id
JOIN Classes cl
ON cl.class_id=e.class_id
JOIN Courses co
ON co.course_id =cl.course_id
JOIN Languages ll
ON co.language_id = ll.language_id
EXCEPT
SELECT p.name,pl.name
FROM Pupil_Knowledge pk
JOIN Pupils p
ON p.pupil_id=pk.pupil_id
JOIN Languages pl
ON pl.language_id=pk.language_id

-- Select pupils who speak a language none of their teachers speaks
-- Distinct
SELECT Distinct p.name, pl.name
FROM Pupils p
JOIN Pupil_Knowledge pk
ON pk.pupil_id=p.pupil_id
JOIN Languages pl
ON pl.language_id=pk.language_id
WHERE pl.name NOT IN (
	SELECT tl.name
	From Enrollments e
	JOIN Classes cl
	ON cl.class_id=e.class_id
	JOIN Contracts co
	ON cl.class_id=co.class_id
	JOIN Teachers t
	ON t.teacher_id=co.teacher_id
	JOIN Teacher_Knowledge tk
	ON tk.teacher_id=t.teacher_id
	JOIN Languages tl
	ON tk.language_id=tl.language_id
	WHERE p.pupil_id=e.pupil_id
)

-- Select pupils who speak a language one of their teachers doesn't speak
-- Distinct
SELECT DISTINCT p.name, pl.name
FROM Pupils p
JOIN Pupil_Knowledge pk
ON pk.pupil_id=p.pupil_id
JOIN Languages pl
ON pl.language_id=pk.language_id
WHERE NOT EXISTS (
	SELECT 1
	From Enrollments e
	JOIN Classes cl
	ON cl.class_id=e.class_id
	JOIN Contracts co
	ON cl.class_id=co.class_id
	JOIN Teachers t
	ON t.teacher_id=co.teacher_id
	WHERE p.pupil_id=e.pupil_id AND
	NOT EXISTS(
		SELECT 1
		FROM Teacher_Knowledge tk
		JOIN Languages tl
		ON tk.language_id=tl.language_id
		WHERE tk.teacher_id=t.teacher_id AND tl.name=pl.name
	)
)

-- Select pupils in a class with more than 1 teacher
-- Distinct
SELECT DISTINCT p.name
FROM Pupils p
JOIN Enrollments e
ON p.pupil_id=e.pupil_id
JOIN Classes cl
ON cl.class_id=e.class_id
WHERE (  
	SELECT COUNT(*)
	FROM Contracts c
	WHERE c.class_id=cl.class_id
) > 1;

-- Select the pupil(s) who speaks the most languages in each class
-- All
WITH CntLang (pid, cnt) AS (
	SELECT p.pupil_id, (
		SELECT COUNT(*) 
		FROM Pupil_Knowledge pk
		JOIN Languages l
		ON l.language_id=pk.language_id
		WHERE p.pupil_id=pk.pupil_id
	)
	FROM Pupils p
)
SELECT cl.name, p.name, (SELECT cnt FROM Cntlang WHERE pid=p.pupil_id) languages
FROM Pupils p
JOIN Enrollments e
ON p.pupil_id=e.pupil_id
JOIN Classes cl
ON cl.class_id=e.class_id
WHERE (SELECT cnt FROM Cntlang WHERE pid=p.pupil_id) >= ALL (
	SELECT cnt
	FROM Cntlang
	JOIN Pupils pp
	ON pp.pupil_id=pid
	JOIN Enrollments ee
	ON ee.pupil_id=pp.pupil_id
	JOIN Classes ccl
	ON ee.class_id=ccl.class_id
	WHERE ccl.class_id=cl.class_id
)

-- Select classes with 3-5 pupils
-- Between
SELECT cl.name
FROM Classes cl
WHERE (
	SELECT COUNT(*) 
	FROM Enrollments e
	WHERE e.class_id=cl.class_id
) BETWEEN 3 AND 5

-- Find all the courses which have more than 1 class (the name and number of classes)
-- Using subquery
SELECT (
SELECT name 
FROM Courses
WHERE cl.course_id = course_Id
) "Course Name", COUNT(course_id) "Number of classes"
FROM Classes cl
GROUP BY course_id
HAVING COUNT(course_id) > 1

-- Order the languages by the number of courses they have
-- Using where instead of join
SELECT l.name "Language", COUNT(l.name) "Number of Courses"
FROM Courses co, Languages l
WHERE l.language_id = co.language_id
GROUP BY l.name
ORDER BY COUNT(l.name) DESC

-- Order the languages by the number of intermediate (including lower/upper int) classes they have and display their average length
-- Using group, subquery (and join), LIKE
SELECT (SELECT name
FROM Languages
WHERE language_id=co.language_id
) "Language", STRING_AGG(cl.name, ', ') "Course names", AVG(co.length) "Average length"
FROM Courses co
INNER JOIN Classes cl
ON co.course_id = cl.course_id
WHERE co.difficulty LIKE '%Intermediate'
GROUP BY co.language_id
ORDER BY COUNT(cl.name) ASC

-- List all the classes shorter than 52 weeks for each language
-- Using group, join
SELECT
l.name "Language", STRING_AGG(cl.name, ', ') "Course names"
FROM Courses co
JOIN Classes cl
ON co.course_id = cl.course_id
JOIN Languages l
ON l.language_id = co.language_id
WHERE co.length < 52
GROUP BY l.name