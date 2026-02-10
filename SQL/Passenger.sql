CREATE TABLE Пассажир(
Id INT PRIMARY KEY, 
ФИО VARCHAR(30) NOT NULL, 
Паспорт VARCHAR(11) UNIQUE NOT NULL CHECK(LEN(Паспорт) = 11), 
ДатаРождения DATE NOT NULL CHECK(ДатаРождения <= CURRENT_TIMESTAMP), 
Пол CHAR(1) NOT NULL, 
Телефон INT) 