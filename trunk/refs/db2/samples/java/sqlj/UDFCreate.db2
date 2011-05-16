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
-- SOURCE FILE NAME: UDFCreate.db2
--    
-- SAMPLE: How to catalog the UDFs contained in UDFsrv.java 
--
-- To run this script from the CLP, perform the following steps:
-- 1. connect to the database
-- 2. issue the command "db2 -td@ -vf <script-name>"
--    where <script-name> represents the name of this script
----------------------------------------------------------------------------

CREATE FUNCTION scratchpadScUDF( )
RETURNS INTEGER
EXTERNAL NAME 'UDFsrv!scratchpadScUDF'
FENCED
SCRATCHPAD 10
FINAL CALL
VARIANT
NO SQL
PARAMETER STYLE DB2GENERAL
LANGUAGE JAVA
NO EXTERNAL ACTION@

CREATE FUNCTION scUDFReturningErr( DOUBLE, DOUBLE )
RETURNS DOUBLE
EXTERNAL NAME 'UDFsrv!scUDFReturningErr'
FENCED
NOT VARIANT
NO SQL
PARAMETER STYLE DB2GENERAL
LANGUAGE JAVA
NO EXTERNAL ACTION@

CREATE FUNCTION tableUDF ( DOUBLE )
RETURNS TABLE ( name VARCHAR(20), job VARCHAR(20), salary DOUBLE )
EXTERNAL NAME 'UDFsrv!tableUDF'
LANGUAGE JAVA
PARAMETER STYLE DB2GENERAL
NOT DETERMINISTIC
FENCED
NO SQL
NO EXTERNAL ACTION
SCRATCHPAD 10
FINAL CALL
DISALLOW PARALLEL
NO DBINFO@

