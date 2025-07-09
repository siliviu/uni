USE LanguageCentre


--PROBLEM:
BEGIN TRAN
UPDATE Languages SET name='RoRoEnglish' WHERE language_id=159
INSERT INTO Logs VALUES(GETDATE(), 'Update Languages 1');
WAITFOR DELAY '00:00:3'
UPDATE Courses SET name='Course Course' WHERE course_id=57
INSERT INTO Logs VALUES(GETDATE(), 'Update Courses 1');
COMMIT TRAN

--FIX (CHOOSE VICTIM OR UPDATE IN THE SAME ORDER)

SELECT * FROM Logs
UPDATE Languages SET name='RoEnglish' WHERE language_id=159
UPDATE Courses SET name='Course' WHERE course_id=57	