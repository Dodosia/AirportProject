DECLARE Bagage CURSOR LOCAL FORWARD_ONLY STATIC
FOR SELECT ПосадочныйТалон.Id, ВесБагажа FROM ПосадочныйТалон, Самолет, Билет, Рейс
WHERE ПосадочныйТалон.НомерБилета = Билет.Номер AND Билет.НомерРейса = Рейс.Номер AND Рейс.IdСамолета = Самолет.Id

OPEN Bagage
DECLARE @talon INT, @max_weight INT,@weight INT, @id INT = 1

DECLARE @table TABLE (id INT, talon INT, weig INT, decl VARCHAR(20)) 

FETCH NEXT FROM Bagage INTO @talon, @max_weight

WHILE @@FETCH_STATUS = 0
BEGIN
	SET @weight = RAND() * (@max_weight - 1) + 1
	INSERT INTO Багаж VALUES (@id, @talon, @weight, NULL)
	SET @id = @id + 1
	
	FETCH NEXT FROM Bagage INTO @talon, @max_weight
END

SELECT * FROM @table
CLOSE Bagage
DEALLOCATE Bagage

UPDATE Багаж SET Описание = 'Ручная кладь' WHERE Вес < 10