USE LanguageCentre


--PROBLEM:
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
--FIX:
--SET TRANSACTION ISOLATION LEVEL READ COMMITTED
BEGIN TRAN
INSERT INTO Logs VALUES(GETDATE(), 'Get Languages');
SELECT * FROM Languages
WAITFOR DELAY '00:00:4'
INSERT INTO Logs VALUES(GETDATE(), 'Get Languages again');
SELECT * FROM Languages
COMMIT TRAN

SELECT * FROM Logs 