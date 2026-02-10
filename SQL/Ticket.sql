CREATE TABLE Билет(
Номер INT PRIMARY KEY, 
IdПассажира INT NOT NULL REFERENCES Пассажир(Id), 
НомерРейса VARCHAR(6) NOT NULL REFERENCES Рейс(Номер), 
ДатаОтправления DATE NOT NULL,
Класс CHAR(1) DEFAULT 'Y' CHECK(Класс IN ('Y', 'W', 'C', 'F')),
UNIQUE(IdПассажира, НомерРейса))