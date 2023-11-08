USE LanguageCentre

DROP TABLE IF EXISTS Version
DROP PROCEDURE IF EXISTS Do1;
DROP PROCEDURE IF EXISTS Undo1;
DROP PROCEDURE IF EXISTS Do2;
DROP PROCEDURE IF EXISTS Undo2;
DROP PROCEDURE IF EXISTS Do3;
DROP PROCEDURE IF EXISTS Undo3;
DROP PROCEDURE IF EXISTS Do4;
DROP PROCEDURE IF EXISTS Undo4;
DROP PROCEDURE IF EXISTS Do5;
DROP PROCEDURE IF EXISTS Undo5;
DROP PROCEDURE IF EXISTS ChangeVersion;

CREATE TABLE Version (
version INT PRIMARY KEY
);

INSERT INTO Version VALUES (0);

GO

CREATE PROCEDURE Do1 AS
BEGIN
	ALTER TABLE Languages
	ALTER COLUMN name VARCHAR(50) NOT NULL
END
GO 

CREATE PROCEDURE Undo1 AS
BEGIN
	ALTER TABLE Languages
	ALTER COLUMN name VARCHAR(25) NOT NULL
END
GO

CREATE PROCEDURE Do2 AS
BEGIN 
	ALTER TABLE Courses
	ADD CONSTRAINT default_length 
	DEFAULT 52 FOR length
END
GO

CREATE PROCEDURE Undo2 AS
BEGIN
	ALTER TABLE Courses
	DROP CONSTRAINT IF EXISTS default_length 
END
GO

CREATE PROCEDURE Do3 AS
BEGIN 
	CREATE TABLE LanguageFamily (
	family_id	INT		PRIMARY KEY	IDENTITY,
	name		INT		UNIQUE
	)
END
GO

CREATE PROCEDURE Undo3 AS
BEGIN
	DROP TABLE IF EXISTS LanguageFamily
END
GO

CREATE PROCEDURE Do4 AS
BEGIN 
	ALTER TABLE Languages 
	ADD family_id INT
END
GO

CREATE PROCEDURE Undo4 AS
BEGIN
	ALTER TABLE Languages
	DROP COLUMN IF EXISTS family_id;
END
GO

CREATE PROCEDURE Do5 AS
BEGIN
	ALTER TABLE Languages
	ADD CONSTRAINT fk_family
	FOREIGN KEY(family_id) REFERENCES LanguageFamily(family_id) ON DELETE CASCADE
END
GO


CREATE PROCEDURE Undo5 AS
BEGIN
	ALTER TABLE Languages
	DROP CONSTRAINT IF EXISTS fk_family;
END
GO

CREATE PROCEDURE ChangeVersion @version INT
AS
BEGIN
	DECLARE @current_version AS INT = (SELECT version FROM VERSION);
	DECLARE @str NVARCHAR(20)
	
	WHILE (@current_version < @version)
	BEGIN
		SET @current_version = @current_version + 1;
		SET @STR= CONCAT('DO',@current_version)
		EXECUTE @str
		--PRINT @str
	END
	
	WHILE (@current_version > @version)
	BEGIN
		SET @str = CONCAT('UNDO',@current_version)
		EXECUTE @str
		SET @current_version = @current_version - 1;
		--PRINT @str
	END
	
	UPDATE Version SET version = @version
END
	--PRINT @version
GO 


EXEC ChangeVersion 1
EXEC ChangeVersion 3
EXEC ChangeVersion 0
EXEC ChangeVersion 4
EXEC ChangeVersion 2
EXEC ChangeVersion 5
EXEC ChangeVersion 1


EXEC ChangeVersion 0
