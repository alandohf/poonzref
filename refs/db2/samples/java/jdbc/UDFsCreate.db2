-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
-- 
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
-- 
-- (C) COPYRIGHT International Business Machines Corp. 1997 - 2002
--  All Rights Reserved.
-- 
--  US Government Users Restricted Rights - Use, duplication or
--  disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: UDFsCreate.db2
--    
-- SAMPLE: How to catalog the UDFs contained in UDFsqlsv.java 
--
-- To run this script from the CLP, perform the following steps:
-- 1. connect to the database
-- 2. issue the command "db2 -td@ -vf <script-name>"
--    where <script-name> represents the name of this script
----------------------------------------------------------------------------

CREATE FUNCTION Convert(CHAR(2), DOUBLE, CHAR(2))
RETURNS DOUBLE
EXTERNAL NAME 'UDFsqlsv!Convert'
FENCED
CALLED ON NULL INPUT
NOT VARIANT
READS SQL DATA 
PARAMETER STYLE DB2GENERAL
LANGUAGE JAVA
NO EXTERNAL ACTION@
  
CREATE FUNCTION sumSalary(CHAR(3))
RETURNS DOUBLE
EXTERNAL NAME 'UDFsqlsv!sumSalary'
FENCED
CALLED ON NULL INPUT
NOT VARIANT
READS SQL DATA 
PARAMETER STYLE DB2GENERAL
LANGUAGE JAVA
NO EXTERNAL ACTION@

CREATE FUNCTION tableUDFWITHSQL ( DOUBLE )
RETURNS TABLE ( name VARCHAR(20), job VARCHAR(20), salary DOUBLE )
EXTERNAL NAME 'UDFsqlsv!tableUDF'
LANGUAGE JAVA
PARAMETER STYLE DB2GENERAL
NOT DETERMINISTIC
FENCED
READS SQL DATA
NO EXTERNAL ACTION
SCRATCHPAD 10
FINAL CALL
DISALLOW PARALLEL
NO DBINFO@
  
CREATE TABLE EXCHANGERATE (sourceCurrency char(2),
	                   exchangeRate double,
	                   resultCurrency char(2))@

INSERT INTO EXCHANGERATE VALUES ('US',1.5,'CA')@

INSERT INTO EXCHANGERATE VALUES ('CA', .67, 'US')@

