CREATE TABLE Багаж(
Id INT PRIMARY KEY, 
IdТалона INT NOT NULL REFERENCES ПосадочныйТалон(Id), 
Вес INT NOT NULL CHECK (Вес > 0), 
Описание VARCHAR(20)) 