CREATE TABLE —амолет(
Id INT PRIMARY KEY, 
ћодель VARCHAR(20) UNIQUE NOT NULL, 
¬местимость INT NOT NULL CHECK(¬местимость > 0),
¬есЅагажа INT CHECK(¬есЅагажа > 0) DEFAULT 15, 
√од¬вода¬Ёксплуатацию INT NOT NULL CHECK(√од¬вода¬Ёксплуатацию <= YEAR(CURRENT_TIMESTAMP))) 