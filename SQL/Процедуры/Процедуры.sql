CREATE PROCEDURE AddPass
    @passengerId INT,
	@seat VARCHAR(4),
    @ticketId INT OUTPUT,
	@message VARCHAR(50) OUTPUT
AS
BEGIN
	SET @ticketId = (SELECT Номер FROM Билет WHERE @passengerId = IdПассажира)
	IF @ticketId NOT IN (SELECT НомерБилета FROM ПосадочныйТалон)
		BEGIN
			INSERT INTO ПосадочныйТалон(Id, НомерБилета, Место) VALUES (@PassengerId, @ticketId, @seat)
			SET @message = 'Посадочный талон успешно создан.';
		END
	ELSE
		SET @message = 'У данного пассажира уже есть талон.'
END

CREATE PROCEDURE FindAirplaneSeats
    @ticketId INT,
	@seats INT OUTPUT
AS
BEGIN
	SET @seats = (SELECT Вместимость FROM Самолет, Билет, Рейс WHERE Самолет.Id = Рейс.IdСамолета AND Билет.НомерРейса = Рейс.Номер AND @ticketId = Билет.Номер)
END

CREATE PROCEDURE OccupiedSeats
    @ticketId INT
AS
BEGIN
    declare @seats TABLE(flight VARCHAR(4), flightDate DATE, seat VARCHAR(4))
	INSERT INTO @seats SELECT Билет.НомерРейса, Билет.ДатаОтправления, ПосадочныйТалон.Место  FROM ПосадочныйТалон, Билет 
	WHERE ПосадочныйТалон.НомерБилета = Билет.Номер AND @ticketId = Билет.Номер
END

CREATE PROCEDURE GetOccupiedSeats 
@ticketId INT
AS
BEGIN
DECLARE @departureDate DATE, @flightNumber VARCHAR(6)
    SELECT @departureDate = Билет.ДатаОтправления, @flightNumber = Билет.НомерРейса FROM Билет WHERE Билет.Номер = @ticketId

    DECLARE @OccupiedSeats TABLE 
    (
        НомерРейса VARCHAR(6),
        ДатаОтправления DATE,
        Место VARCHAR(4)
    );

    INSERT INTO @OccupiedSeats (НомерРейса, ДатаОтправления, Место) SELECT Билет.НомерРейса, Билет.ДатаОтправления, ПосадочныйТалон.Место FROM ПосадочныйТалон
	JOIN Билет ON ПосадочныйТалон.НомерБилета = Билет.Номер
	WHERE @departureDate = ДатаОтправления AND @flightNumber = НомерРейса

    SELECT * FROM @OccupiedSeats
END

EXEC GetOccupiedSeats 12

CREATE PROCEDURE AddNewBoardingPass
    @Id INT,
    @НомерБилета INT,
    @Место VARCHAR(4),
	@message VARCHAR(100) OUTPUT
AS
BEGIN
	IF NOT EXISTS (SELECT 1 FROM Билет WHERE Номер = @НомерБилета)
    BEGIN
        SET @message = 'Такого номера билета не существует'
        RETURN
    END

	IF EXISTS (SELECT 1 FROM ПосадочныйТалон WHERE Id = @Id)
    BEGIN
        SET @message = 'Номер талона уже занят'
        RETURN
    END

	IF EXISTS (SELECT 1 FROM ПосадочныйТалон WHERE НомерБилета = @НомерБилета)
    BEGIN
        SET @message = 'Талон с таким номером билета уже существует'
        RETURN
    END

	DECLARE @OccupiedSeats TABLE (НомерРейса VARCHAR(6), ДатаОтправления DATE, Место VARCHAR(4))
    INSERT INTO @OccupiedSeats EXEC dbo.GetOccupiedSeats @НомерБилета

    IF EXISTS (SELECT 1 FROM @OccupiedSeats WHERE Место = @Место)
    BEGIN
        SET @message = 'Это место уже занято'
        RETURN
    END

    INSERT INTO ПосадочныйТалон (Id, НомерБилета, Место) VALUES (@Id, @НомерБилета, @Место);

    SET @message = 'Талон успешно добавлен';
END

CREATE PROCEDURE UpdateBoardingPass
    @Id INT,
    @НомерБилета INT,
    @Место VARCHAR(4),
	@message VARCHAR(100) OUTPUT
AS
BEGIN
   DECLARE @OccupiedSeats TABLE (НомерРейса VARCHAR(6), ДатаОтправления DATE, Место VARCHAR(4))
    INSERT INTO @OccupiedSeats EXEC dbo.GetOccupiedSeats @НомерБилета

	IF NOT EXISTS (SELECT 1 FROM Билет WHERE Номер = @НомерБилета)
    BEGIN
        SET @message = 'Такого номера билета не существует'
        RETURN
    END

	IF EXISTS (SELECT 1 FROM ПосадочныйТалон WHERE Id = @Id)
    BEGIN
        SET @message = 'Номер талона уже занят'
        RETURN
    END

    IF EXISTS (SELECT 1 FROM @OccupiedSeats WHERE Место = @Место)
    BEGIN
        SET @message = 'Это место уже занято'
        RETURN
    END

    UPDATE ПосадочныйТалон SET НомерБилета = @НомерБилета, Место = @Место WHERE Id = @Id;
	SET @message = 'Талон успешно изменен';
END

CREATE PROCEDURE MaxWeight
	@IdТалона INT,
	@maxWeight INT OUTPUT
AS
BEGIN
	SET @maxWeight = (SELECT ВесБагажа FROM Самолет, Рейс, ПосадочныйТалон, Билет 
	WHERE Самолет.Id = Рейс.IdСамолета AND Рейс.Номер = Билет.НомерРейса AND Билет.Номер = ПосадочныйТалон.НомерБилета AND ПосадочныйТалон.Id = @IdТалона)
END

CREATE PROCEDURE AddNewBaggageTag
    @Id INT,
    @IdТалона INT,
    @Описание VARCHAR(20),
	@Вес INT,
	@message VARCHAR(100) OUTPUT
AS
BEGIN
	DECLARE @maxWeight INT
	EXEC MaxWeight @IdТалона, @maxWeight OUTPUT

	IF NOT EXISTS (SELECT 1 FROM ПосадочныйТалон WHERE Id = @IdТалона)
    BEGIN
        SET @message = 'Такого номера талона не существует'
        RETURN
    END
	IF EXISTS (SELECT 1 FROM Багаж WHERE Id = @Id)
    BEGIN
        SET @message = 'Номер багажной бирки уже занят'
        RETURN
    END

	IF @Вес > @maxWeight
    BEGIN
		SET @message = 'Вес превышает допустимое значение'
        RETURN
    END

    INSERT INTO Багаж (Id, IdТалона, Вес, Описание) VALUES (@Id, @IdТалона, @Вес, @Описание);

    SET @message = 'Багажная бирка успешно добавлена';
END

CREATE PROCEDURE UpdateBaggageTag
    @Id INT,
    @IdТалона INT,
    @Описание VARCHAR(20),
	@Вес INT,
	@message VARCHAR(100) OUTPUT
AS
BEGIN
	DECLARE @maxWeight INT
	EXEC MaxWeight @IdТалона, @maxWeight OUTPUT

	IF @Вес > @maxWeight
    BEGIN
		SET @message = 'Вес превышает допустимое значение'
        RETURN
    END

	IF @Id IN (SELECT Id FROM Багаж)
    BEGIN
		SET @message = 'Номер багажной бирки уже занят'
        RETURN
    END

    UPDATE Багаж SET IdТалона = @IdТалона, Описание = @Описание, Вес = @Вес WHERE Id = @Id
	SET @message = 'Бирка успешно изменена'
END

CREATE PROCEDURE UpdateAirplaneStatus
    @airplaneId INT,
    @newStatus NVARCHAR(50)
AS
BEGIN
    UPDATE Самолет SET Статус = @newStatus WHERE Id = @airplaneId
END

CREATE PROCEDURE UpdateLastServiceDate
	@AirplaneId INT, 
	@LastServiceDate DATETIME
AS BEGIN
	UPDATE Самолет SET ДатаПоследнегоОбслуживания = @lastServiceDate WHERE Самолет.Id = @airplaneId
END

CREATE PROCEDURE UpdateAircraftStatusForInspection
AS
BEGIN
    UPDATE Самолет
    SET Статус = 'Требуется осмотр'
    WHERE DATEDIFF(DAY, ДатаПоследнегоОбслуживания, GETDATE()) >= 1 OR ДатаПоследнегоОбслуживания IS NULL;
END

EXECUTE UpdateAircraftStatusForInspection

CREATE PROCEDURE UpdateAirplaneId
    @FlightId VARCHAR(6),
    @NewAirplaneId INT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Самолет WHERE Id = @NewAirplaneId AND Статус = 'в ремонте')
    BEGIN
        RAISERROR('Самолет с таким Id находится в ремонте и не может быть использован.', 16, 1);
        RETURN;
    END
	IF NOT EXISTS (SELECT 1 FROM Самолет WHERE Id = @NewAirplaneId)
    BEGIN
        RAISERROR('Самолет с таким Id не существует.', 16, 1);
        RETURN;
    END
	IF EXISTS (SELECT 1 FROM Рейс WHERE Рейс.IdСамолета = @NewAirplaneId)
		RAISERROR('Самолет с таким Id уже используется', 16, 1);
    UPDATE Рейс
    SET IdСамолета = @NewAirplaneId
    WHERE Номер = @FlightId;
END

CREATE PROCEDURE GetAirplaneStatus
    @AirplaneId INT
AS
BEGIN
    SELECT Статус
    FROM Самолет
    WHERE Id = @AirplaneId;
END

EXECUTE GetAirplaneStatus 150