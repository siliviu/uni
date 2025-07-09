USE LanguageCentre


DROP PROCEDURE IF EXISTS AddTable 
DROP PROCEDURE IF EXISTS AddView 
DROP PROCEDURE IF EXISTS AddTest 
DROP PROCEDURE IF EXISTS AddTestTable 
DROP PROCEDURE IF EXISTS AddTestView 
DROP PROCEDURE IF EXISTS RunTest
DROP PROCEDURE IF EXISTS PopulateTable
DELETE FROM TestTables
DELETE FROM TestViews
DELETE FROM TestRunViews
DELETE FROM TestRunTables
DELETE FROM Tests
DELETE FROM TestRuns
DELETE FROM Tables
DELETE FROM Views
GO

CREATE PROCEDURE AddTable (@name NVARCHAR(255)) AS BEGIN
	IF @name NOT IN (SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES)
		THROW 50000, 'Table doesn''t exist', 1;
	IF @name IN (SELECT Name from Tables)
		THROW 50000, 'Table has already been added', 1;
	INSERT INTO Tables(Name) VALUES(@name)
END 
GO

CREATE PROCEDURE AddView (@name NVARCHAR(255)) AS BEGIN
	IF @name NOT IN (SELECT TABLE_NAME FROM INFORMATION_SCHEMA.VIEWS)
		THROW 50000, 'View doesn''t exist', 1;
	IF @name IN (SELECT Name from Views)
		THROW 50000, 'View has already been added', 1;
	INSERT INTO Views(Name) VALUES(@name)
END
GO

CREATE PROCEDURE AddTest (@name NVARCHAR(255)) AS BEGIN
	IF @name IN (SELECT Name from Tests)
		THROW 50000, 'Test has already been added', 1;
	INSERT INTO Tests(Name) VALUES(@name)
END 
GO

CREATE PROCEDURE AddTestTable(@testname NVARCHAR(255), @tablename NVARCHAR(255), @rows INT) AS BEGIN
	IF @testname NOT IN (SELECT Name From Tests)
		THROW 50000, 'Test not added to tests', 1;
	IF @tablename NOT IN (SELECT Name From Tables)
		THROW 50000, 'Table not added to tables', 1;
	DECLARE @testid INT = (SELECT TestId FROM Tests WHERE Name=@testname)
	DECLARE @tableid INT = (SELECT TableId FROM Tables WHERE Name=@tablename)
	IF EXISTS (SELECT * From TestTables WHERE TestID=@testid AND TableID=@tableid)
		THROW 50000, 'TestTable already added', 1;
	INSERT INTO TestTables(TestID,TableID,NoOfRows,Position) VALUES (@testid,@tableid,@rows,(SELECT COUNT(*) FROM TestTables WHERE TestID=@testid)+1)
END 
GO

CREATE PROCEDURE AddTestView(@testname NVARCHAR(255), @viewname NVARCHAR(255)) AS BEGIN
	IF @testname NOT IN (SELECT Name From Tests)
		THROW 50000, 'Test not added to tests', 1;
	IF @viewname NOT IN (SELECT Name From Views)
		THROW 50000, 'View not added to tables', 1;
	DECLARE @testid INT = (SELECT TestId FROM Tests WHERE Name=@testname)
	DECLARE @viewid INT = (SELECT ViewID FROM Views WHERE Name=@viewname)
	IF EXISTS (SELECT * From TestViews WHERE TestID=@testid AND ViewID=@viewid)
		THROW 50000, 'TestView already added', 1;
	INSERT INTO TestViews(TestID,ViewID) VALUES (@testid, @viewid)
END 
GO

CREATE PROCEDURE RunTest(@testname NVARCHAR(255), @desc NVARCHAR(255)) AS BEGIN
	DECLARE @teststart DATETIME = sysdatetime()
	DECLARE @testid INT = (SELECT TestID FROM Tests t WHERE Name=@testname)
	INSERT INTO TestRuns(Description,StartAt) VALUES(@desc,@teststart);
	DECLARE @testrunid INT = IDENT_CURRENT('TestRuns');


	DECLARE table_cursor CURSOR SCROLL FOR 
	SELECT t.Name, t.tableID, tt.NoOfRows
	FROM TestTables tt
	JOIN Tables t ON t.TableID=tt.TableID 
	WHERE TestID = @testid
	ORDER BY tt.Position
	
	DECLARE @tablename VARCHAR(255);
	DECLARE @tableid INT;
	DECLARE @rows INT;
	OPEN table_cursor
	FETCH FIRST FROM table_cursor INTO @tablename, @tableid, @rows
	
	WHILE @@FETCH_STATUS=0 BEGIN
		EXEC ('DELETE FROM ' + @tablename)
		FETCH NEXT FROM table_cursor INTO @tablename, @tableid, @rows
	END
	
	FETCH LAST FROM table_cursor INTO @tablename, @tableid, @rows

	WHILE @@FETCH_STATUS=0 BEGIN
		DECLARE @tablestart DATETIME = sysdatetime()
		DECLARE @command NVARCHAR(255) = 'Populate' + @tablename

		IF @command NOT IN (SELECT ROUTINE_NAME FROM INFORMATION_SCHEMA.ROUTINES)
			THROW 50000, 'You must have a corresponding populate procedure for each table you add', 1;

		EXEC @command @rows
		
		DECLARE @tableend DATETIME = sysdatetime()
		INSERT INTO TestRunTables(TestRunID,TableID,StartAt,EndAt) VALUES(@testrunid, @tableid, @tablestart,@tableend)
		FETCH PRIOR FROM table_cursor INTO @tablename, @tableid, @rows
	END

	CLOSE table_cursor
	DEALLOCATE table_cursor

	
	DECLARE view_cursor CURSOR FOR 
	SELECT v.Name, v.viewID
	FROM TestViews tv
	JOIN Views v ON v.VIEWID=tv.ViewID 
	WHERE TestID = @testid


	DECLARE @viewname VARCHAR(255);
	DECLARE @viewid INT;
	OPEN view_cursor
	FETCH NEXT FROM view_cursor INTO @viewname, @viewid
	WHILE @@FETCH_STATUS=0 BEGIN
		DECLARE @viewstart DATETIME = sysdatetime()
		EXEC ('SELECT * FROM ' + @viewname)
		DECLARE @viewend DATETIME = sysdatetime()
		INSERT INTO TestRunViews(TestRunID,ViewID,StartAt,EndAt) VALUES(@testrunid, @viewid, @viewstart,@viewend)
		FETCH NEXT FROM view_cursor INTO @viewname, @viewid
	END
	
	CLOSE view_cursor
	DEALLOCATE view_cursor

	DECLARE @testend DATETIME = sysdatetime()
	UPDATE TestRuns SET EndAt = @testend WHERE TestRunId=@testrunid;
END 
GO

DROP VIEW IF EXISTS getNewID
DROP FUNCTION IF EXISTS RandomNumber
GO

CREATE VIEW getNewID AS SELECT newid() new_id
GO

CREATE FUNCTION RandomNumber (@max INT)
RETURNS INT AS
BEGIN
 RETURN 1+(ABS(CHECKSUM((SELECT new_id FROM getNewID))) % (@max-1))
END

GO
-- PART 1

DROP PROCEDURE IF EXISTS PopulatePupils;
DROP VIEW IF EXISTS ViewPupils
GO

CREATE VIEW ViewPupils AS
	SELECT pupil_Id ID, name NAME, date_birth BIRTHDATE, description DESCRIPTION
	FROM Pupils
	WHERE MONTH(date_birth) = 2
GO	

CREATE PROCEDURE PopulatePupils (@rows INT) AS BEGIN
	WHILE @rows > 0 BEGIN
		INSERT INTO Pupils(name, date_birth) VALUES ('random' +  CONVERT(VARCHAR(255), @rows), DATEADD(day, dbo.RandomNumber(2000), 25000))
		SET @rows = @rows-1
	END
END
GO


-- PART 2
DROP PROCEDURE IF EXISTS PopulateClasses;
DROP PROCEDURE IF EXISTS PopulateCourses;
DROP PROCEDURE IF EXISTS PopulateLanguages;
DROP VIEW IF EXISTS ViewClasses
GO

CREATE VIEW ViewClasses AS
	SELECT cl.name CLASS, cl.year YEAR, co.name COURSE, co.difficulty DIFFICULTY, l.name LANGUAGE
	FROM Classes cl
	JOIN Courses co ON cl.course_id=co.course_id
	JOIN Languages l ON l.language_id=co.language_id
	WHERE 
	l.name LIKE 'language__' AND
	co.difficulty != 'difficulty1'
	AND cl.year>2011
GO	


CREATE PROCEDURE PopulateClasses (@rows INT) AS BEGIN
	WHILE @rows > 0 BEGIN
		INSERT INTO Classes(name, year, course_id) VALUES ('name' + CONVERT(VARCHAR(255), @rows), 2010+dbo.RandomNumber(10), (SELECT TOP 1 course_id FROM Courses ORDER BY NEWID()))
		SET @rows = @rows-1
	END
END
GO

CREATE PROCEDURE PopulateCourses (@rows INT) AS BEGIN
	WHILE @rows > 0 BEGIN
		INSERT INTO Courses(name, length, difficulty, language_id) VALUES 
		('name' + CONVERT(VARCHAR(255), @rows), dbo.RandomNumber(10), 'difficulty'+CONVERT(VARCHAR(255),dbo.RandomNumber(5)), (SELECT TOP 1 language_id FROM Languages ORDER BY NEWID()))
		SET @rows = @rows-1
	END
END
GO

CREATE PROCEDURE PopulateLanguages (@rows INT) AS BEGIN
	WHILE @rows > 0 BEGIN
		INSERT INTO Languages(name) VALUES ('language' +  CONVERT(VARCHAR(255), @rows))
		SET @rows = @rows-1
	END
END
GO

-- PART 3
DROP PROCEDURE IF EXISTS PopulateEnrollments;
DROP VIEW IF EXISTS ViewEnrollments
GO

CREATE VIEW ViewEnrollments AS
	SELECT cl.year YEAR, SUM(e.cost) CNT
	FROM Enrollments e
	JOIN Pupils p ON e.pupil_id=p.pupil_id
	JOIN Classes cl ON e.class_id=cl.class_id
	GROUP BY cl.year
GO	

CREATE PROCEDURE PopulateEnrollments (@rows INT) AS BEGIN
	IF @rows > (SELECT COUNT(*) FROM Classes) * (SELECT COUNT(*) FROM Pupils)
		THROW 50000, 'Cannot create this many enrollments', 1;
	
	DECLARE populate_cursor CURSOR FOR
		SELECT class_id, pupil_id
		FROM Classes, Pupils
	DECLARE @classid INT
	DECLARE @pupilid INT
	OPEN populate_cursor
	FETCH NEXT FROM populate_cursor INTO @classid,@pupilid

	WHILE @rows > 0 BEGIN
		FETCH NEXT FROM populate_cursor INTO @classid,@pupilid
		INSERT INTO Enrollments(class_id, pupil_id, date, cost) VALUES (@classid,@pupilid,DATEADD(day, 0, 2500), dbo.RandomNumber(5))
		SET @rows = @rows-1
	END
	CLOSE populate_cursor
	DEALLOCATE populate_cursor
END
GO

EXEC AddTable Pupils
EXEC AddTable Classes
EXEC AddTable Courses
EXEC AddTable Languages
EXEC AddTable Enrollments
EXEC AddView ViewEnrollments
EXEC AddView ViewClasses
EXEC AddView ViewPupils
EXEC AddTest Test
EXEC AddTestTable Test, Enrollments, 10000
EXEC AddTestTable Test, Pupils, 5000
EXEC AddTestTable Test, Classes, 500
EXEC AddTestTable Test, Courses, 100
EXEC AddTestTable Test, Languages, 50
EXEC AddTestView Test, ViewPupils
EXEC AddTestView Test, ViewClasses
EXEC AddTestView Test, ViewEnrollments
EXEC RunTest Test, 'Testing EVERYTTHING'


SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews
