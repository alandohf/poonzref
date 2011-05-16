-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
-- 
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
--
-- (C) COPYRIGHT International Business Machines Corp. 1995 - 2004        
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: spdrop.db2
--    
-- SAMPLE: How to uncatalog the stored procedures contained in spserver.sqc 
--
-- To run this script from the CLP, perform the following steps:
-- 1. connect to the database
-- 2. issue the command "db2 -td@ -vf <script-name>"
--    where <script-name> represents the name of this script
-----------------------------------------------------------------------------
-- For more information on the sample programs, see the README file.
--
-- For information on developing C applications, see the Application
-- Development Guide.
--
-- For information on using SQL statements, see the SQL Reference.
--
-- For the latest information on programming, building, and running DB2 
-- applications, visit the DB2 application development website: 
--     http://www.software.ibm.com/data/db2/udb/ad
-----------------------------------------------------------------------------

connect to sample@

DROP PROCEDURE OUT_LANGUAGE (CHAR(8))@

DROP PROCEDURE OUT_PARAM (DOUBLE)@

DROP PROCEDURE IN_PARAMS (DOUBLE, DOUBLE, DOUBLE, CHAR(3))@

DROP PROCEDURE INOUT_PARAM (DOUBLE)@

DROP PROCEDURE CLOB_EXTRACT (CHAR(6), VARCHAR(1000))@

DROP PROCEDURE DBINFO_EXAMPLE (CHAR(8), DOUBLE, CHAR(128), CHAR(8))@

DROP PROCEDURE MAIN_EXAMPLE (CHAR(8), DOUBLE)@

DROP PROCEDURE ALL_DATA_TYPES (SMALLINT, INTEGER, BIGINT, REAL, DOUBLE,
     CHAR(1), CHAR(15), VARCHAR(12), DATE, TIME)@

DROP PROCEDURE ONE_RESULT_SET (DOUBLE)@

DROP PROCEDURE TWO_RESULT_SETS (DOUBLE)@

DROP PROCEDURE GENERAL_EXAMPLE (INTEGER, INTEGER, CHAR(32))@

DROP PROCEDURE GENERAL_WITH_NULLS_EXAMPLE (INTEGER, INTEGER, CHAR(32))@

connect reset@     
