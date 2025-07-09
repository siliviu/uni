USE LanguageCentre
SET NOCOUNT ON

GO


CREATE OR ALTER FUNCTION CheckIfNull(@string NVARCHAR(255))
RETURNS BIT AS 
BEGIN
	IF @string IS NULL
		RETURN 1
	IF @string = ''
		RETURN 1
	RETURN 0
END
GO

CREATE OR ALTER PROCEDURE GetLanguages(@language_id INT = NULL) AS BEGIN
	IF @language_id IS NOT NULL 
		SELECT * FROM Languages WHERE language_id=@language_id
	ELSE
		SELECT * FROM Languages
END
GO

CREATE OR ALTER PROCEDURE AddLanguage (@name NVARCHAR(255)) AS BEGIN
	IF dbo.CheckIfNull(@name) = 1
		THROW 50000, 'Name is null', 1;
		
	INSERT INTO Languages(name) VALUES (@name)
	PRINT 'Added new language'

END
GO

CREATE OR ALTER PROCEDURE UpdateLanguages (@name NVARCHAR(255), @language_id INT) AS BEGIN
	IF dbo.CheckIfNull(@name) = 1
		THROW 50000, 'Name is null', 1;

		
	UPDATE Languages
	SET name=@name
	WHERE language_id=@language_id
	PRINT 'Updated existing language'
END
GO

CREATE OR ALTER PROCEDURE DeleteLanguages(@language_id INT = NULL) AS BEGIN
	IF @language_id IS NOT NULL
		DELETE FROM Languages WHERE language_id=@language_id
END
GO

Exec GetLanguages
Exec GetLanguages 201
EXEC AddLanguage 'NEW LANGUAGE'
EXEC UpdateLanguages 'BB', 201
Exec GetLanguages
Exec DeleteLanguages 201
Exec GetLanguages
GO

CREATE OR ALTER PROCEDURE GetTeachers(@teacher_id INT = NULL) AS BEGIN
	IF @teacher_id IS NOT NULL 
		SELECT * FROM Teachers WHERE teacher_id=@teacher_id
	ELSE
		SELECT * FROM Teachers
END
GO

CREATE OR ALTER PROCEDURE AddTeacher (@studies NVARCHAR(255), @name NVARCHAR(255), @description NVARCHAR(255) = NULL) AS BEGIN
	IF dbo.CheckIfNull(@studies) = 1
		THROW 50000, 'Studies are null', 1;
	IF dbo.CheckIfNull(@name) = 1
		THROW 50000, 'Name is null', 1;
		
	INSERT INTO Teachers(studies, name, description) VALUES (@studies, @name, @description)
		PRINT 'Added new teacher'
END
GO

CREATE OR ALTER PROCEDURE UpdateTeachers (@studies NVARCHAR(255), @name NVARCHAR(255), @description NVARCHAR(255) = NULL, @teacher_id INT = NULL) AS BEGIN
	IF dbo.CheckIfNull(@studies) = 1
		THROW 50000, 'Studies are null', 1;
	IF dbo.CheckIfNull(@name) = 1
		THROW 50000, 'Name is null', 1;
		
	UPDATE Teachers
	SET studies=@studies, name=@name, description=@description
	WHERE teacher_id=@teacher_id
	PRINT 'Updated existing teacher'
END
GO

CREATE OR ALTER PROCEDURE DeleteTeachers(@teacher_id INT = NULL) AS BEGIN
	IF @teacher_id IS NOT NULL 
		DELETE FROM Teachers WHERE teacher_id=@teacher_id
END
GO

Exec GetTeachers
Exec GetTeachers 3
EXEC UpdateTeachers 'AAA', 'BBB', 'ee', 4
EXEC AddTeacher 'AANEW TEACHER', 'NEW', NULL
Exec DeleteTeachers 4
GO


CREATE OR ALTER PROCEDURE GetTeacherKnowledge(@language_id INT = NULL, @teacher_id INT = NULL) AS BEGIN
	IF @teacher_id IS NOT NULL AND @language_id IS NOT NULL
		SELECT * FROM Teacher_Knowledge WHERE language_id=@language_id AND teacher_id=@teacher_id
	ELSE
		SELECT * FROM Teacher_Knowledge
END
GO

CREATE OR ALTER PROCEDURE AddTeacherKnowledge (@level VARCHAR(255), @date_teaching DATE, @language_id INT, @teacher_id INT) AS BEGIN
	IF dbo.CheckIfNull(@level) = 1
		THROW 50000, 'Level is null', 1;

	IF NOT EXISTS (SELECT * FROM Teachers WHERE teacher_id=@teacher_id) OR NOT EXISTS (SELECT * FROM Languages WHERE language_id=@language_id)
		THROW 50000, 'Invalid teacher or language', 1;

	INSERT INTO Teacher_Knowledge(level, date_teaching, language_id, teacher_id) VALUES (@level, @date_teaching, @language_id, @teacher_id)
	PRINT 'Added new teacher knowledge'
END
GO

CREATE OR ALTER PROCEDURE UpdateTeacherKnowledge (@level VARCHAR(255), @date_teaching DATE, @language_id INT, @teacher_id INT) AS BEGIN
	IF dbo.CheckIfNull(@level) = 1
		THROW 50000, 'Level is null', 1;

	IF NOT EXISTS (SELECT * FROM Teachers WHERE teacher_id=@teacher_id) OR NOT EXISTS (SELECT * FROM Languages WHERE language_id=@language_id)
		THROW 50000, 'Invalid teacher or language', 1;

	UPDATE Teacher_Knowledge
	SET level=@level, date_teaching=@date_teaching
	WHERE language_id=@language_id and teacher_id=@teacher_id
	PRINT 'Updated teacher knowledge'
END
GO

CREATE OR ALTER PROCEDURE DeleteTeacherKnowledge(@language_id INT = NULL, @teacher_id INT = NULL) AS BEGIN
	IF @teacher_id IS NOT NULL AND @language_id IS NOT NULL
		DELETE FROM Teacher_Knowledge WHERE language_id=@language_id AND teacher_id=@teacher_id
END
GO

Exec GetTeacherKnowledge
Exec GetTeacherKnowledge 151, 2
Exec AddTeacherKnowledge 'BBBBBBBBB','2024/12/10', 152, 2
Exec UpdateTeacherKnowledge 'AAAAAAAAAA','2024/12/10', 151, 2
Exec GetTeacherKnowledge
EXEC DeleteTeacherKnowledge 152,2
Exec GetTeacherKnowledge
GO

CREATE OR ALTER VIEW GetAllTeacherKnowledge AS
	SELECT t.name "Teacher Name", l.name "Language Name"
	FROM Teacher_Knowledge tk
	JOIN Teachers t ON tk.teacher_id=t.teacher_id
	JOIN Languages l ON tk.language_id=l.language_id
	WHERE tk.level='A' AND l.name LIKE 'language4_'
GO

GO
CREATE OR ALTER VIEW GetBilingualTeachers AS
	SELECT t.name
	FROM Teacher_Knowledge tk
	JOIN Teachers t ON tk.teacher_id=t.teacher_id
	JOIN Languages l ON tk.language_id=l.language_id
	GROUP BY t.name
	HAVING COUNT(*)>1
GO


DROP INDEX IF EXISTS TK ON Teacher_Knowledge
DROP INDEX IF EXISTS L ON Languages
DROP INDEX IF EXISTS T ON Teachers

CREATE INDEX TK ON Teacher_Knowledge (teacher_id, language_id, level)
CREATE INDEX L ON Languages (language_id, name)
CREATE INDEX T ON Teachers (teacher_id, name)

SELECT * FROM GetAllTeacherKnowledge
SELECT * FROM GetBilingualTeachers