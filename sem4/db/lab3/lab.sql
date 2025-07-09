USE LanguageCentre
GO

/*
CREATE TABLE LogTable(
Lid INT IDENTITY PRIMARY KEY,
TypeOperation VARCHAR(50),
TableOperation VARCHAR(50),
ExecutionDate DATETIME)
GO
DELETE FROM LogTable
*/

DELETE FROM Teachers WHERE studies = 'FSPAC'
DELETE FROM Teachers WHERE studies = 'Letters'
DELETE FROM Teachers WHERE studies = 'Business'
DELETE FROM Languages WHERE name = 'RoEnglish'
DELETE FROM Languages WHERE name = 'RoGerman'
DELETE FROM Languages WHERE name = 'RoItalian'

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

CREATE OR ALTER PROCEDURE AddTeacherLanguage (@teacher_name NVARCHAR(255), @studies NVARCHAR(255), @desc NVARCHAR(255), @language_name NVARCHAR(255), @level NVARCHAR(255), @date DATE) AS BEGIN
	BEGIN TRANSACTION
	BEGIN TRY
			IF dbo.CheckIfNull(@language_name) = 1
				RAISERROR('Language name must not be null', 14, 1)
			INSERT INTO Languages (name) VALUES(@language_name)
			IF dbo.CheckIfNull(@teacher_name) = 1
				RAISERROR('Teacher name must not be null', 14, 1)
			IF dbo.CheckIfNull(@studies) = 1
				RAISERROR('Teacher studies must not be null', 14, 1)
			INSERT INTO Teachers (name, studies, description) VALUES (@teacher_name, @studies, @desc)
			IF @level NOT IN ('Beginner', 'Intermediate', 'Advanced')
				RAISERROR('Invalid level', 14, 1)
			IF @date IS NULL
				RAISERROR('Date must not be null', 14, 1)
			INSERT INTO Teacher_Knowledge (level, date_teaching, language_id, teacher_id) VALUES (@level, @date,
				(SELECT MAX(language_id) FROM Languages), (SELECT MAX(teacher_id) FROM Teachers))
			INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate) VALUES('Add', 'Added Teacher + Language + Teacher Knowledge', GETDATE())
			COMMIT TRANSACTION
			SELECT 'Transaction committed'
	END TRY
	BEGIN  CATCH
			ROLLBACK TRANSACTION
			SELECT 'Transaction rollbacked'
	END CATCH
END

GO


SELECT * FROM Teachers
SELECT * FROM Languages

Exec AddTeacherLanguage 'Maria', 'FSPAC', 'money', 'RoEnglish', 'Advanced', '2024/12/10'
Exec AddTeacherLanguage 'Ioana', 'Business', 'gold', 'RoRussian', NULL, '2024/12/12'

SELECT * FROM LogTable
SELECT * FROM Teachers
SELECT * FROM Languages

GO

CREATE OR ALTER PROCEDURE AddTeacherLanguage2 (@teacher_name NVARCHAR(255), @studies NVARCHAR(255), @desc NVARCHAR(255), @language_name NVARCHAR(255), @level NVARCHAR(255), @date DATE) AS BEGIN
	DECLARE @ok INT = 1
	
	BEGIN TRANSACTION
	BEGIN TRY
			IF dbo.CheckIfNull(@language_name) = 1
				RAISERROR('Language name must not be null', 14, 1)
			INSERT INTO Languages (name) VALUES(@language_name)
			INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate) VALUES('Add', 'Added Teacher', GETDATE())
			COMMIT TRANSACTION
			SELECT 'Transaction committed - part 1'
	END TRY
	BEGIN  CATCH
			ROLLBACK TRANSACTION
			SELECT 'Transaction rollbacked - part 1'
			SET @ok = 0
	END CATCH
	BEGIN TRANSACTION
	BEGIN TRY
			IF dbo.CheckIfNull(@teacher_name) = 1
				RAISERROR('Teacher name must not be null', 14, 1)
			IF dbo.CheckIfNull(@studies) = 1
				RAISERROR('Teacher studies must not be null', 14, 1)
			INSERT INTO Teachers (name, studies, description) VALUES (@teacher_name, @studies, @desc)
			INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate) VALUES('Add', 'Added Language', GETDATE())
			COMMIT TRANSACTION
			SELECT 'Transaction committed - part 2'
	END TRY
	BEGIN  CATCH
			ROLLBACK TRANSACTION
			SELECT 'Transaction rollbacked - part 2'
			SET @ok = 0
	END CATCH
	
	IF @ok = 0
		RETURN
	BEGIN TRANSACTION
	BEGIN TRY
			IF @level NOT IN ('Beginner', 'Intermediate', 'Advanced')
				RAISERROR('Invalid level', 14, 1)
			IF @date IS NULL
				RAISERROR('Date must not be null', 14, 1)
			INSERT INTO Teacher_Knowledge (level, date_teaching, language_id, teacher_id) VALUES (@level, @date,
				(SELECT MAX(language_id) FROM Languages), (SELECT MAX(teacher_id) FROM Teachers))
			INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate) VALUES('Add', 'Added Teacher Knowledge', GETDATE())
			COMMIT TRANSACTION
			SELECT 'Transaction committed - part 3'
	END TRY
	BEGIN  CATCH
			ROLLBACK TRANSACTION
			SELECT 'Transaction rollbacked - part 3'
	END CATCH
END

GO

SELECT * FROM Teachers
SELECT * FROM Languages

Exec AddTeacherLanguage2 'Ana', 'Letters', NULL, 'RoGerman', 'Beginner', '2024/11/05'
Exec AddTeacherLanguage2 'Eustache', NULL, 'idk', 'RoItalian', 'Intermediate', '2024/11/07'

SELECT * FROM LogTable
SELECT * FROM Teachers
SELECT * FROM Languages
