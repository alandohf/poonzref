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
-- SOURCE FILE NAME: testdata.db2
--    
-- SAMPLE: How to populate a table with randomly generated test data
--
-- DB2 BUILT-IN FUNCTIONS USED:
--         RAND()
--         TRANSLATE()
--
-- SQL STATEMENTS USED:
--         CREATE TABLE
--         INSERT
--         SELECT
--         DROP TABLE
--
-- OUTPUT FILE: testdata.out (available in the online documentation)
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

 CREATE TABLE EMPL (ENO INTEGER, LASTNAME VARCHAR(30),
                 HIREDATE DATE, SALARY INTEGER);
 
 
 INSERT INTO EMPL 
 -- generate 100 records
 WITH DT(ENO) AS (VALUES(1) UNION ALL SELECT ENO+1 FROM DT WHERE ENO < 100 )
 
 -- Now, use the generated records in DT to create other columns
 -- of the employee record.
   SELECT ENO,
     TRANSLATE(CHAR(INTEGER(RAND()*1000000)),
               CASE MOD(ENO,4) WHEN 0 THEN 'aeiou' || 'bcdfg'
                               WHEN 1 THEN 'aeiou' || 'hjklm'
                               WHEN 2 THEN 'aeiou' || 'npqrs'
                                      ELSE 'aeiou' || 'twxyz' END,
                                           '1234567890') AS LASTNAME,
     CURRENT DATE - (RAND()*10957) DAYS AS HIREDATE,
     INTEGER(10000+RAND()*200000) AS SALARY
   FROM DT;
                                                      
 SELECT * FROM EMPL;

 DROP TABLE EMPL;

