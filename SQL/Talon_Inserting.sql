DECLARE Talon CURSOR LOCAL FORWARD_ONLY STATIC
FOR SELECT IdПассажира, ДатаОтправления, Билет.Номер, НомерРейса, Вместимость FROM Билет, Самолет, Рейс 
WHERE Самолет.Id = Рейс.IdСамолета AND Билет.НомерРейса = Рейс.Номер AND ДатаОтправления = CAST(GETDATE() AS DATE) ORDER BY НомерРейса

OPEN Talon
DECLARE @id INT = 1
DECLARE @id_pas INT, @date DATE, @ticket INT, @max_seats INT
DECLARE @flight VARCHAR(6), @prev_flight VARCHAR(6)
SELECT @prev_flight = НомерРейса FROM Билет WHERE Номер = 1

DECLARE @seat_row INT = 1
DECLARE @seat_letter CHAR(1) = 'A' 
DECLARE @prev_ticket INT = NULL 
DECLARE @seat_letters VARCHAR(6) = 'ABCDEF'
DECLARE @seat_letter_index INT = 1

DECLARE @table TABLE (id INT, id_pas INT, ticket INT, seat VARCHAR(4)) 

FETCH NEXT FROM Talon INTO @id_pas, @date, @ticket, @flight, @max_seats
WHILE @@FETCH_STATUS = 0
BEGIN
	IF @flight != @prev_flight
	BEGIN
		SET @seat_row = 1
        SET @seat_letter_index = 1 
        SET @seat_letter = SUBSTRING(@seat_letters, @seat_letter_index, 1)
		SET @prev_flight = @flight
	END

	INSERT INTO ПосадочныйТалон VALUES (@id, @id_pas, @ticket, CAST(@seat_row AS VARCHAR(4)) + @seat_letter)

	SET @id = @id + 1

	SET @seat_letter_index = @seat_letter_index + 1
	IF @seat_letter_index > LEN(@seat_letters)
    BEGIN
        SET @seat_row = @seat_row + 1
        SET @seat_letter_index = 1 
    END

    SET @seat_letter = SUBSTRING(@seat_letters, @seat_letter_index, 1)
	
	FETCH NEXT FROM Talon INTO @id_pas, @date, @ticket, @flight, @max_seats
END

SELECT * FROM @table
CLOSE Talon
DEALLOCATE Talon