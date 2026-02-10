CREATE TABLE Рейс(
Номер VARCHAR(6) PRIMARY KEY, 
IdСамолета INT NOT NULL REFERENCES Самолет(Id),
АэропортВылета VARCHAR(3) NULL REFERENCES Аэропорт(Код) DEFAULT 'SVO', 
АэропортПрилета VARCHAR(3) NULL REFERENCES Аэропорт(Код) DEFAULT 'SVO',
ВремяОтправления TIME NOT NULL UNIQUE,
ВремяПрибытия TIME NOT NULL UNIQUE,
ВремяВпути TIME NOT NULL)