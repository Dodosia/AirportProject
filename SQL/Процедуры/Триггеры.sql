CREATE TRIGGER CheckStatusChange
ON Самолет
AFTER UPDATE
AS
BEGIN
	IF (SELECT COUNT(*) FROM inserted) = 1
        BEGIN
            DECLARE @ДатаПоследнегоОбслуживания DATETIME;
            DECLARE @Статус VARCHAR(60);
            DECLARE @id INT;

            SET @ДатаПоследнегоОбслуживания = (SELECT ДатаПоследнегоОбслуживания FROM inserted);
            SET @Статус = (SELECT Статус FROM inserted);
            SET @id = (SELECT Id FROM deleted);

            IF @Статус != 'Требуется осмотр'
            BEGIN
                IF @ДатаПоследнегоОбслуживания < DATEADD(minute, -5, GETDATE())
                BEGIN
                    RAISERROR('Невозможно изменить статус без проведения осмотра.', 16, 1)
                    RETURN
                END
                ELSE
                    UPDATE Самолет SET Статус = @Статус WHERE Id = @id;
            END
        END
END

CREATE TRIGGER CheckAirplaneChange
ON Рейс
AFTER UPDATE
AS
BEGIN
	IF (SELECT COUNT(*) FROM inserted) = 1
        BEGIN
            DECLARE @IdСамолета INT
			DECLARE @number VARCHAR(6)
			DECLARE @NewIdСамолета INT
			SET @IdСамолета = (SELECT IdСамолета FROM deleted)
			SET @number = (SELECT Номер FROM deleted)
			SET @NewIdСамолета = (SELECT IdСамолета FROM inserted)

			IF (SELECT Статус FROM Самолет WHERE Id = @NewIdСамолета) = 'На ремонте'
			BEGIN
				RAISERROR('Самолет находится на ремонте.', 16, 1)
			    RETURN
			END

			IF @IdСамолета NOT IN (SELECT Id FROM Самолет)
			BEGIN
				RAISERROR('Такого самолета не существует.', 16, 1)
			    RETURN
			END

			IF @IdСамолета IN (SELECT IdСамолета FROM Рейс)
			BEGIN
				RAISERROR('Самолет уже используется.', 16, 1)
			    RETURN
			END

			ELSE
				UPDATE Рейс SET IdСамолета = @NewIdСамолета WHERE Номер = @number
        END
END

CREATE TRIGGER CheckBoardingPassLimit
ON ПосадочныйТалон
AFTER INSERT, UPDATE
AS
BEGIN
    DECLARE @НомерРейса VARCHAR(6);
    DECLARE @IdСамолета INT;
    DECLARE @Вместимость INT;

    SET @НомерРейса = (SELECT Билет.НомерРейса  FROM inserted i JOIN Билет ON i.НомерБилета = Билет.Номер);

    SET @IdСамолета = (SELECT Рейс.IdСамолета FROM Рейс WHERE Рейс.Номер = @НомерРейса);

    SET @Вместимость = (SELECT Самолет.Вместимость FROM Самолет WHERE Самолет.Id = @IdСамолета);

    DECLARE @ВыданныеТалоны INT;
    SET @ВыданныеТалоны = (SELECT COUNT(*) FROM ПосадочныйТалон JOIN Билет  ON ПосадочныйТалон.НомерБилета = Билет.Номер WHERE Билет.НомерРейса = @НомерРейса);

    IF @ВыданныеТалоны > @Вместимость
    BEGIN
        RAISERROR('Превышена вместимость самолета для рейса %s.', 16, 1, @НомерРейса);
        RETURN
    END
END