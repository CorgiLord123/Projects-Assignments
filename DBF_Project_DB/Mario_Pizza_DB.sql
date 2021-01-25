
/* (Database Fundamentals, Assignment Part D) 
 * First author's name:  Bach, Ngyuen (1356601)
 * First author's email:  Bach.Ngyuen@student.uts.edu.au
 * Second author's name:  Kenny, Zhong (13533702)
 * Second author's email: Kenny.Zhong@student.uts.edu.au
 * Third author's name:  Stanley, Li (13539301)
 * Third author's email: Stanley.Li@student.uts.edu.au
 * script name: Tut1_11_Li_ 13539301_Zhong_13533702_Nguyen_13566601_PartD.sql
 * purpose:     Builds PostgreSQL tables for Mario's Pizza Party online food delivery service 
 * The URL for the website related to this database is  https://ordermate.online/manciniswoodfiredpizza/menu 
*/

DROP TABLE if exists Customer CASCADE;
DROP TABLE if exists PaymentDetails CASCADE;
DROP TABLE if exists FoodOrder CASCADE;
DROP TABLE if exists MenuItem CASCADE;
DROP TABLE if exists OrderDetails CASCADE;
DROP TABLE if exists Delivery CASCADE;
DROP TABLE if exists Vehicle CASCADE;
DROP TABLE if exists Employee CASCADE;
DROP TABLE if exists KitchenStaff CASCADE;
DROP TABLE if exists DeliveryDriver CASCADE;


CREATE TABLE Customer
(
    CustomerID          INT             NOT NULL,
    First_Name      	CHAR(20)        NOT NULL,
    Last_Name   	CHAR(20)   	NOT NULL,
    PhoneNo   	        VARCHAR(30)     NOT NULL,
    Email   		VARCHAR(50)     NOT NULL,
    Password  		VARCHAR(30)     NOT NULL,
    UnitNo              VARCHAR(30)     NOT NULL,
    Street              VARCHAR(30)     NOT NULL,
    Suburb              VARCHAR(20)     NOT NULL,
    State               VARCHAR(30)     NOT NULL,
    Postcode            VARCHAR(4)      NOT NULL,
CONSTRAINT Customer_PK Primary KEY (CustomerID)
);
-- Customer Table Data
INSERT INTO Customer VALUES
(10, 'Biggie', 'Chungus', '0498246053', 'notoriousChungus@gmail.com', '12345', '14', 'Whitfield Avenue', 'Ashfield', 'NSW', '2131'),
(11, 'John', 'Schnotter', '0422095117', 'pizzaloverJS@yahoo.com.au', 'il0v3P1zz@', '28', 'Rawson Street', 'Haberfield', 'NSW', '2045'),
(12, 'Thomas', 'Pearfield', '0412863095', 'ThomasPear@outlook.com', 'TxG23fD5a', '90', 'Knox Street', 'Belmore', 'NSW', '2192'),
(13, 'Zhang Wei', 'Zhou', '0446130254', 'woaib11za@foxmail.com', 'ASD45S_5a32', '27', 'Bertram Street', 'Chatswood', 'NSW', '2067'),
(14, 'Ayush', 'Patel', '0417845645', 'Ayushpatel@gmail.com', '^%$#TYrte5', '15', 'Bennett Avenue', 'Strathfield South', 'NSW', '2137'); 


CREATE TABLE PaymentDetails
(
    AccountType   	       CHAR(20)  		NOT NULL,
    BSB      	               VARCHAR(8)   	        NOT NULL,
    AccountNo  		       VARCHAR(20)      	NOT NULL,
    AccountName   	       VARCHAR(40)       	NOT NULL,
    CustomerID   	       INT                      NOT NULL,
CONSTRAINT PaymentDetails_PK PRIMARY KEY (AccountType, CustomerID),
CONSTRAINT PaymentDetails_FK FOREIGN KEY (CustomerID) References Customer(CustomerID)
);
-- PaymentDetails Table Data
INSERT INTO PaymentDetails VALUES
('Savings', '062 105', '1733 0834', 'Biggie Chungus Savings', 10),
('Savings', '062 193', '5118 5827', 'John Schnotter Savings', 11),
('Credit', '062 140', '2545 7124', 'Thomas Pearfield Credit', 12),
('Cheque', '082 811', '1 0980 5926', 'Zhang Wei Zhou Cheque', 13),
('Credit', '082 811', '2 4232 8466', 'Zhang Wei Zhoue Credit', 13),
('Savings', '012 266', '1 0643 2390', 'Ayush Patel Savings', 14);


CREATE TABLE Vehicle
(
    VehicleReg   	 VARCHAR(8)   	 NOT NULL,
    RegExp   		 DATE	         NOT NULL,
    CONSTRAINT Vehicle_PK Primary KEY (VehicleReg)
);

-- Vehicle Table Data
 INSERT INTO Vehicle VALUES
('NBC420', '2021-02-27'),
('PPJD65', '2020-03-15'),
('MPPOD8', '2021-09-03'),
('P1ZZA', '2021-04-02'),
('2BIK3', '2020-11-30');


CREATE TABLE Employee
(
-- Common attributes
    EmployeeID   	 INT                    NOT NULL,
    First_Name      	 CHAR(20)            	NOT NULL,
    Last_Name     	 CHAR(20)            	NOT NULL,
    ManagerID            INT,
--sub type discriminator
    Position   		 CHAR(20)   		NOT NULL,
CONSTRAINT EmployeeID_PK PRIMARY KEY (EmployeeID),
CONSTRAINT EmployeeID_FK FOREIGN KEY (ManagerID) REFERENCES Employee(EmployeeID)
);
-- Employee Table Data
INSERT INTO Employee VALUES
(101, 'Mario', 'Romano', NULL, 'K'),
(102, 'Luigi', 'Romano', 101, 'K'),
(103, 'Natalina', 'Regio', 102, 'K'),
(104, 'Joseph', 'Bruno', 102, 'K'),
(105, 'Christian', 'Di Grande', 102, 'K'),
(106, 'Leone', 'Albani', 101, 'D'),
(107, 'Domenic', 'Michaels', 106, 'D'),
(108, 'Susan', 'Farid', 106, 'D'),
(109, 'Wilson', 'Jones', 106, 'D'),
(110, 'Steve', 'Liao', 106, 'D'); 


-- Create the employee subtypes
CREATE TABLE KitchenStaff
(
        KitchenStaffID   		 INT        			 NOT NULL,
	Hairnet   			 BOOLEAN       			 NOT NULL,
	Constraint KitchenStaff_PK PRIMARY KEY (KitchenStaffID),
	Constraint KitchenStaff_FK FOREIGN KEY (KitchenStaffID) References Employee(EmployeeID)
);
-- KitchenStaff Table Data
INSERT INTO KitchenStaff VALUES
(101, TRUE),
(102, TRUE),
(103, TRUE),
(104, FALSE),
(105, TRUE);

CREATE TABLE DeliveryDriver
(
        DeliveryStaffID  	 INT       		 NOT NULL,
	LicenseNo   		 VARCHAR(12) 		 NOT NULL,
	Constraint DeliveryDriver_PK PRIMARY KEY (DeliveryStaffID),
	Constraint DeliveryDriver_FK FOREIGN KEY (DeliveryStaffID) References Employee (EmployeeID)
);
-- DeliveryDriver Table Data
INSERT INTO DeliveryDriver VALUES
(106, '2 4865 1154'),
(107, '1 5547 9803'),
(108, '1 1005 6855'),
(109, '1 0124 3295'), 
(110, '2 7846 9518'); 

CREATE TABLE Delivery
(
    DeliveryID        INT   			 NOT NULL,
    DeliveryStaffID   INT   			 NOT NULL,
    DeliveryDate      DATE   		         NOT NULL,
    VehicleReg        VARCHAR(8)  	         NOT NULL,
CONSTRAINT Delivery_PK PRIMARY KEY (DeliveryID),
CONSTRAINT Delivery_FK1 FOREIGN KEY (DeliveryStaffID) References DeliveryDriver(DeliveryStaffID),
CONSTRAINT Delivery_FK2 FOREIGN KEY (VehicleReg) References Vehicle(VehicleReg)
);
-- Delivery Table Data
INSERT INTO Delivery VALUES
(1001, 106, '2020-05-29', 'NBC420'),
(1002, 107, '2020-05-30', 'NBC420'),
(1003, 108, '2020-05-30', 'P1ZZA'),
(1004, 108, '2020-05-31', '2BIK3'),
(1005, 106, '2020-05-31', 'MPPOD8');

CREATE TABLE FoodOrder
(
    OrderID               INT              NOT NULL,
    AccountType           CHAR(20)         NOT NULL,
    CustomerID   	  INT   	   NOT NULL,
    KitchenStaffID	  INT              NOT NULL,
    DeliveryID            INT              NOT NULL,
CONSTRAINT FoodOrder_PK Primary KEY (OrderID),
CONSTRAINT FoodOrder_FK1 FOREIGN KEY(CustomerID, AccountType) References PaymentDetails(CustomerID, AccountType),
CONSTRAINT FoodOrder_FK2 FOREIGN KEY(DeliveryID) References Delivery(DeliveryID),
CONSTRAINT FoodOrder_FK3 FOREIGN KEY(KitchenStaffID) References KitchenStaff(KitchenStaffID)
);
-- FoodOrder Table Data
INSERT INTO FoodOrder VALUES
(2001, 'Savings', 11, 101, 1001),
(2002, 'Credit', 12, 101, 1001),
(2003, 'Savings', 11, 102, 1002),
(2004, 'Savings', 11, 103, 1003),
(2005, 'Cheque', 13, 105, 1004),
(2006, 'Credit', 12, 105, 1005);


CREATE TABLE MenuItem
(
    FoodID   	     INT   	     NOT NULL,
    ItemName         CHAR(20)        NOT NULL,
    FoodCategory     CHAR(20)        NOT NULL,
    Price            NUMERIC(5, 2)   NOT NULL,
CONSTRAINT MenuItem_PK PRIMARY KEY (FoodID)
);
-- MenuItem Table Data
INSERT INTO MenuItem VALUES
(201, 'Arancini Balls', 'Entree', '14.00'),
(202, 'Garlic Prawns', 'Entree', '16.50'),
(203, 'Garlic Bread', 'Entree', '5.80'),
(301, 'Carbonara', 'Pasta', '18.50'),
(302, 'Marinara', 'Pasta', '23.90'),
(401, 'Napoletana', 'Pizza', '17.00'),
(402, 'Capricciosa', 'Pizza', '17.00'),
(403, 'Pescatore', 'Pizza', '21.50'); 

CREATE TABLE OrderDetails
(
    OrderID   	 INT   		 NOT NULL,
    FoodID       INT   		 NOT NULL,
    Quantity   	 INT   		 NOT NULL,
    Additions      VARCHAR(40),
CONSTRAINT OrderDetails_PK PRIMARY KEY (OrderID, FoodID),
CONSTRAINT OrderDetails_FK1 FOREIGN KEY (FoodID) References MenuItem(FoodID),
CONSTRAINT OrderDetails_FK2 FOREIGN KEY (OrderID) References FoodOrder(OrderID)
);
-- OrderDetails Table Data
INSERT INTO OrderDetails VALUES
(2001, 401, 2, 'Extra sauce'),
(2001, 402, 3, 'Extra olives'),
(2002, 301, 1, 'Less bacon'),
(2002, 302, 1, 'No added salt'),
(2004, 201, 3, NULL),
(2004, 403, 1, NULL),
(2005, 301, 1, NULL),
(2005, 202, 1, NULL),
(2005, 402, 1, NULL),
(2006, 203, 5, 'No garlic');

-- All Table Data
SELECT * FROM Customer;
SELECT * FROM PaymentDetails;
SELECT * FROM FoodOrder;
SELECT * FROM MenuItem;
SELECT * FROM OrderDetails;
SELECT * FROM delivery;
SELECT * FROM Vehicle;
SELECT * FROM employee;
SELECT * FROM KitchenStaff;
SELECT * FROM DeliveryDriver;

-- SQL Queries
  -- Show number of orders for all customers
SELECT CustomerID, First_Name, Last_Name,
(SELECT count(*)
    FROM FoodOrder
        GROUP BY customerID
            HAVING customerID = c.customerID)
AS Number_of_orders
FROM customer c;



