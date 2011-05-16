-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
-- 
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
--
-- (C) COPYRIGHT International Business Machines Corp. 1995 - 2002        
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: const.db2
--    
-- SAMPLE: How to create a table with a check constraint
--
-- SQL STATEMENTS USED:
--         CREATE TABLE
--         INSERT
--         DROP
--
-- OUTPUT FILE: const.out (available in the online documentation)
-----------------------------------------------------------------------------
--
-- For more information about the command line processor (CLP) scripts, 
-- see the README file.
--
-- For information on using SQL statements, see the SQL Reference.
--
-- For the latest information on programming, building, and running DB2 
-- applications, visit the DB2 application development website: 
--     http://www.software.ibm.com/data/db2/udb/ad
-----------------------------------------------------------------------------

CREATE TABLE EMPL                                                     
 (ID           SMALLINT NOT NULL,                                         
  NAME         VARCHAR(9),                                                
  DEPT         SMALLINT CHECK (DEPT BETWEEN 10 AND 100),
  JOB          CHAR(5)  CHECK (JOB IN ('Sales', 'Mgr', 'Clerk')),
  HIREDATE     DATE,                                                      
  SALARY       DECIMAL(7,2),                                              
  COMM         DECIMAL(7,2),                                              
  PRIMARY KEY (ID),                                                       
  CONSTRAINT YEARSAL CHECK (YEAR(HIREDATE) > 1986 OR SALARY > 40500) 
 );

-- Attempt to insert a row into table EMPL
-- The attempt will fail, as it would violate check constraint YEARSAL
INSERT INTO EMPL VALUES (1,'Lee', 15, 'Mgr', '1985-01-01' , 40000.00, 1000.00);

DROP TABLE EMPL;
