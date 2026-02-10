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

ALTER PROCEDURE UpdateTabloDeparture
AS
BEGIN
    DELETE FROM ТаблоВылета

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
	CLOSE TabloDeparture
	DEALLOCATE TabloDeparture

	SELECT * FROM ТаблоВылета
END

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

ALTER PROCEDURE UpdateTabloArrival
AS
BEGIN
    DELETE FROM ТаблоПрилета

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
		INSERT INTO ТаблоПрилета VALUES (@id2, @flight2, @arrival, @status2)
		SET @id2 = @id2 + 1
		FETCH NEXT FROM TabloArrival INTO @flight2, @arrival
	END
	
	CLOSE TabloArrival
	DEALLOCATE TabloArrival

	SELECT * FROM ТаблоПрилета
END
