DROP INDEX nr ON Echipe

SELECT Denumire, NrMembrii
FROM Echipe 
ORDER BY NrMembrii 


CREATE INDEX nr
ON Echipe (NrMembrii, Denumire)