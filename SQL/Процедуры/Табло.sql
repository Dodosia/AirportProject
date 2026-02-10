DECLARE TabloDeparture CURSOR LOCAL FORWARD_ONLY STATIC
FOR SELECT DISTINCT Рейс.Номер, Рейс.ВремяОтправления FROM Рейс
WHERE Рейс.ВремяОтправления >=  DATEADD(minute, -15, CAST(GETDATE() AS TIME))
  AND Рейс.ВремяОтправления <= DATEADD(hour, 3, CAST(GETDATE() AS TIME))

OPEN TabloDeparture
DECLARE @flight VARCHAR(6), @departure TIME(7), @id INT = 1, @status VARCHAR(20)
DECLARE @table TABLE (id INT, flight VARCHAR(6), departure TIME(7), stat VARCHAR(20))
FETCH NEXT FROM TabloDeparture INTO @flight, @departure
WHILE @@FETCH_STATUS = 0
BEGIN
	IF @departure <= CAST(GETDATE() AS TIME) SET @status = 'Отправлен'
	ELSE SET @status = 'Регистрация'
	INSERT INTO ТаблоВылета VALUES (@id, @flight, @departure, @status)
	SET @id = @id + 1
	FETCH NEXT FROM TabloDeparture INTO @flight, @departure
END

SELECT * FROM @table
CLOSE TabloDeparture
DEALLOCATE TabloDeparture

CREATE PROCEDURE UpdateTabloDeparture
AS
BEGIN
	DECLARE @count INT = (SELECT MAX(Id) FROM ТаблоВылета)
    DECLARE @currentDate DATE = CAST(GETDATE() AS DATE);
    DECLARE @currentTime TIME(7) = CAST(GETDATE() AS TIME(7));
    DECLARE @endDate DATE = CAST(DATEADD(DAY, 1, GETDATE()) AS DATE);
    DECLARE @endTime TIME(7) = @currentTime;

	DELETE FROM ТаблоВылета WHERE ТаблоВылета.Время <= DATEADD(HOUR, -1, @currentTime) AND Статус = 'Вылетел'

	DECLARE @todayFlights TABLE( НомерРейса VARCHAR(6), ВремяОтправления TIME(7), Дата DATE)
    DECLARE @tomorrowFlights TABLE( НомерРейса VARCHAR(6), ВремяОтправления TIME(7), Дата DATE)

	INSERT INTO @todayFlights
    SELECT Рейс.Номер, Рейс.ВремяОтправления, @currentDate FROM Рейс WHERE Рейс.АэропортВылета = 'SVO'

    INSERT INTO @tomorrowFlights
    SELECT Рейс.Номер, Рейс.ВремяОтправления, DATEADD(DAY, 1, @currentDate)
    FROM Рейс WHERE Рейс.АэропортВылета = 'SVO'

	DECLARE flight_cursor CURSOR FOR
    SELECT НомерРейса, ВремяОтправления, Дата FROM @todayFlights WHERE ВремяОтправления >= DATEADD(HOUR, -1, @currentTime) AND Дата = @currentDate;

    OPEN flight_cursor;
	DECLARE @номерРейса VARCHAR(6)
	DECLARE @времяОтправления TIME(7)
	DECLARE @дата DATE
	DECLARE @status VARCHAR(50)
    FETCH NEXT FROM flight_cursor INTO @номерРейса, @времяОтправления, @дата;

    WHILE @@FETCH_STATUS = 0
    BEGIN
		DECLARE @timeDifference INT = DATEDIFF(MINUTE, @currentTime, @ВремяОтправления)
        SET @count = @count + 1;
		BEGIN
			IF @timeDifference <= 240 AND @timeDifference > 60
				SET @status = 'Идет регистрация'
			ELSE IF @timeDifference <= 60 AND @timeDifference > 0
				SET @status = 'Идет посадка'
			ELSE IF @timeDifference <= 0
				SET @status = 'Вылетел'
			ELSE
				SET @status = 'Планируется'
		END
		IF @номерРейса NOT IN (SELECT НомерРейса FROM ТаблоВылета)
			BEGIN
				SET @count = @count + 1
				INSERT INTO ТаблоВылета VALUES (@count, @номерРейса, @времяОтправления, @status);
			END
			ELSE
		BEGIN
			DECLARE @OldStatus VARCHAR(60) = (SELECT Статус FROM ТаблоВылета WHERE НомерРейса = @номерРейса)
				IF @OldStatus != 'Отменен' OR @status != 'Задержан'
					UPDATE ТаблоВылета SET Статус = @status WHERE НомерРейса = @номерРейса
		END
        FETCH NEXT FROM flight_cursor INTO @номерРейса, @времяОтправления, @дата;
    END
    CLOSE flight_cursor;
    DEALLOCATE flight_cursor;

    DECLARE flight_cursor_tomorrow CURSOR FOR
    SELECT НомерРейса, ВремяОтправления, Дата FROM @tomorrowFlights WHERE ВремяОтправления <= DATEADD(HOUR, -1, @endTime) AND Дата = @endDate;

    OPEN flight_cursor_tomorrow
	DECLARE @номерРейса2 VARCHAR(6)
	DECLARE @времяОтправления2 TIME(7)
	DECLARE @дата2 DATE
    FETCH NEXT FROM flight_cursor_tomorrow INTO @номерРейса2, @времяОтправления2, @дата2;

    WHILE @@FETCH_STATUS = 0
    BEGIN
		IF NOT EXISTS (SELECT 1 FROM ТаблоВылета WHERE НомерРейса = @номерРейса2 AND Время = @времяОтправления2)
		BEGIN
			SET @count = @count + 1
			INSERT INTO ТаблоВылета VALUES (@count,  @номерРейса2, @времяОтправления2, 'Планируется');
		END
        FETCH NEXT FROM flight_cursor_tomorrow INTO @номерРейса2, @времяОтправления2, @дата2;
    END

    CLOSE flight_cursor_tomorrow;
    DEALLOCATE flight_cursor_tomorrow;

	SELECT * FROM ТаблоВылета
END

DELETE FROM ТаблоВылета
EXECUTE UpdateTabloDeparture

DECLARE TabloArrival CURSOR LOCAL FORWARD_ONLY STATIC
FOR SELECT DISTINCT Рейс.Номер, ВремяПрибытия FROM Рейс 
WHERE Рейс.ВремяПрибытия BETWEEN DATEADD(minute, -15, CAST(GETDATE() AS TIME)) AND DATEADD(minute, 30, CAST(GETDATE() AS TIME))

OPEN TabloArrival
DECLARE @flight2 VARCHAR(6), @arrival TIME(7), @id2 INT = 1, @status2 VARCHAR(20)
DECLARE @table2 TABLE (id INT, flight VARCHAR(6), arrival TIME(7), stat VARCHAR(20))
FETCH NEXT FROM TabloArrival INTO @flight2, @arrival
WHILE @@FETCH_STATUS = 0
BEGIN
	IF @arrival <= CAST(GETDATE() AS TIME) SET @status2 = 'Прибыл'
	ELSE SET @status2 = 'Посадка'
	INSERT INTO @table2 VALUES (@id2, @flight2, @arrival, @status2)
	SET @id2 = @id2 + 1
	FETCH NEXT FROM TabloArrival INTO @flight2, @arrival
END

SELECT * FROM @table2
CLOSE TabloArrival
DEALLOCATE TabloArrival

CREATE PROCEDURE UpdateTabloArrival
AS
BEGIN
	DECLARE @count INT = (SELECT MAX(Id) FROM ТаблоПрилета)
    DECLARE @currentDate DATE = CAST(GETDATE() AS DATE);
    DECLARE @currentTime TIME(7) = CAST(GETDATE() AS TIME(7));
    DECLARE @endDate DATE = CAST(DATEADD(DAY, 1, GETDATE()) AS DATE);
    DECLARE @endTime TIME(7) = @currentTime;

	DELETE FROM ТаблоПрилета WHERE ТаблоПрилета.Время <= DATEADD(HOUR, -1, @currentTime)

	DECLARE @todayFlights TABLE( НомерРейса VARCHAR(6), ВремяПрибытия TIME(7), Дата DATE)
    DECLARE @tomorrowFlights TABLE( НомерРейса VARCHAR(6), ВремяПрибытия TIME(7), Дата DATE)

	INSERT INTO @todayFlights
    SELECT Рейс.Номер, Рейс.ВремяПрибытия, @currentDate FROM Рейс WHERE Рейс.АэропортПрилета = 'SVO'

    INSERT INTO @tomorrowFlights
    SELECT Рейс.Номер, Рейс.ВремяПрибытия, DATEADD(DAY, 1, @currentDate)
    FROM Рейс WHERE Рейс.АэропортПрилета = 'SVO'

	DECLARE flight_cursor CURSOR FOR
    SELECT НомерРейса, ВремяПрибытия, Дата FROM @todayFlights WHERE ВремяПрибытия >= DATEADD(HOUR, -1, @currentTime) AND Дата = @currentDate;

    OPEN flight_cursor;
	DECLARE @номерРейса VARCHAR(6)
	DECLARE @времяПрибытия TIME(7)
	DECLARE @дата DATE
	DECLARE @status VARCHAR(50)
    FETCH NEXT FROM flight_cursor INTO @номерРейса, @времяПрибытия, @дата;

    WHILE @@FETCH_STATUS = 0
    BEGIN
		DECLARE @timeDifference INT = DATEDIFF(MINUTE, @currentTime, @времяПрибытия)
        SET @count = @count + 1;
		BEGIN
			IF @timeDifference < 0
				SET @status = 'Прилетел'
			ELSE
				SET @status = 'Ожидается'
		END
		IF @номерРейса NOT IN (SELECT НомерРейса FROM ТаблоПрилета)
		BEGIN
			SET @count = @count + 1
			INSERT INTO ТаблоПрилета VALUES (@count, @номерРейса, @времяПрибытия, @status);
		END
		ELSE
			DECLARE @OldStatus VARCHAR(60) = (SELECT Статус FROM ТаблоВылета WHERE НомерРейса = @номерРейса)
				IF @OldStatus != 'Отменен' OR @status != 'Задержан'
					UPDATE ТаблоПрилета SET Статус = @status WHERE НомерРейса = @номерРейса
        FETCH NEXT FROM flight_cursor INTO @номерРейса, @времяПрибытия, @дата;
    END;
    CLOSE flight_cursor;
    DEALLOCATE flight_cursor;

    DECLARE flight_cursor_tomorrow CURSOR FOR
    SELECT НомерРейса, ВремяПрибытия, Дата FROM @tomorrowFlights WHERE ВремяПрибытия <= DATEADD(HOUR, -1, @endTime) AND Дата = @endDate;

    OPEN flight_cursor_tomorrow
	DECLARE @номерРейса2 VARCHAR(6)
	DECLARE @времяОтправления2 TIME(7)
	DECLARE @дата2 DATE
    FETCH NEXT FROM flight_cursor_tomorrow INTO @номерРейса2, @времяОтправления2, @дата2;

    WHILE @@FETCH_STATUS = 0
    BEGIN
		IF NOT EXISTS (SELECT 1 FROM ТаблоПрилета WHERE НомерРейса = @номерРейса2 AND Время = @времяОтправления2)
		BEGIN
			SET @count = @count + 1
			INSERT INTO ТаблоПрилета VALUES (@count,  @номерРейса2, @времяОтправления2, 'Ожидается');
		END
        FETCH NEXT FROM flight_cursor_tomorrow INTO @номерРейса2, @времяОтправления2, @дата2;
    END

    CLOSE flight_cursor_tomorrow;
    DEALLOCATE flight_cursor_tomorrow;

	SELECT * FROM ТаблоПрилета
END

DELETE FROM ТаблоПрилета
EXECUTE UpdateTabloArrival