ALTER PROCEDURE CreatePass
	@ticket INT,
	@passanger VARCHAR(50) OUTPUT,
	@flight VARCHAR(6) OUTPUT,
	@date DATE OUTPUT,
	@time TIME(7) OUTPUT,
	@citydepart VARCHAR(15) OUTPUT,
	@cityarriv VARCHAR(15) OUTPUT,
	@aerdepart VARCHAR(3) OUTPUT,
	@aerarriv VARCHAR(3) OUTPUT
AS BEGIN
	SET @passanger = (SELECT ФИО FROM Пассажир, Билет WHERE Пассажир.Id = Билет.IdПассажира AND Билет.Номер = @ticket)
	SET @flight = (SELECT НомерРейса FROM Билет WHERE Билет.Номер = @ticket)
	SET @date = (SELECT ДатаОтправления FROM Билет WHERE Билет.Номер = @ticket)
	SET @time = (SELECT ВремяОтправления FROM Рейс, Билет WHERE Билет.НомерРейса = Рейс.Номер AND Билет.Номер = @ticket)
	SET @aerdepart = (SELECT АэропортВылета FROM Рейс, Билет WHERE Билет.НомерРейса = Рейс.Номер AND Билет.Номер = @ticket)
	SET @aerarriv = (SELECT АэропортПрилета FROM Рейс, Билет WHERE Билет.НомерРейса = Рейс.Номер AND Билет.Номер = @ticket)
	SET @citydepart = (SELECT Город FROM Аэропорт, Рейс, Билет WHERE Билет.НомерРейса = Рейс.Номер AND Аэропорт.Код = Рейс.АэропортВылета AND Билет.Номер = @ticket)
	SET @cityarriv = (SELECT Город FROM Аэропорт, Рейс, Билет WHERE Билет.НомерРейса = Рейс.Номер AND Аэропорт.Код = Рейс.АэропортПрилета AND Билет.Номер = @ticket)
END

declare @_passanger VARCHAR(50)
declare @_flight VARCHAR(6)
declare @_date DATE 
declare @_time TIME(7)
declare @_citydepart VARCHAR(15) 
declare @_cityarriv VARCHAR(15) 
declare @_aerdepart VARCHAR(15) 
declare @_aerarriv VARCHAR(15)

EXECUTE CreatePass 4, @_passanger OUTPUT, @_flight OUTPUT, @_date OUTPUT, @_time OUTPUT, @_citydepart OUTPUT, @_cityarriv OUTPUT, @_aerdepart OUTPUT, @_aerarriv OUTPUT
PRINT @_passanger
PRINT @_flight
PRINT @_date
PRINT @_time
PRINT @_citydepart
PRINT @_cityarriv
PRINT @_aerdepart 
PRINT @_aerarriv