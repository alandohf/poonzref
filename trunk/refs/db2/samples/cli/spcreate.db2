----------------------------------------------------------------------------
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
----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: spcreate.db2
--    
-- SAMPLE: How to catalog the DB2 CLI stored procedures contained in 
--         spserver.c 
--
-- To run this script from the CLP, perform the following steps:
-- 1. connect to the database
-- 2. issue the command "db2 -td@ -vf <script-name>"
--    where <script-name> represents the name of this script
----------------------------------------------------------------------------
-- For more information on the sample programs, see the README file.
--
-- For information on developing CLI applications, see the CLI Guide
-- and Reference.
--
-- For information on using SQL statements, see the SQL Reference.
--
-- For the latest information on programming, building, and running DB2 
-- applications, visit the DB2 application development website: 
--     http://www.software.ibm.com/data/db2/udb/ad
-----------------------------------------------------------------------------

CREATE PROCEDURE OUT_LANGUAGE (OUT language CHAR(8))
SPECIFIC CLI_OUT_LANGUAGE
DYNAMIC RESULT SETS 0
DETERMINISTIC
LANGUAGE C 
PARAMETER STYLE SQL
NO DBINFO
FENCED NOT THREADSAFE
READS SQL DATA
PROGRAM TYPE SUB
EXTERNAL NAME 'spserver!outlanguage'@

CREATE PROCEDURE OUT_PARAM (OUT medianSalary DOUBLE)
SPECIFIC CLI_OUT_PARAM
DYNAMIC RESULT SETS 0
NOT DETERMINISTIC
LANGUAGE C 
PARAMETER STYLE SQL
NO DBINFO
FENCED NOT THREADSAFE
READS SQL DATA
PROGRAM TYPE SUB
EXTERNAL NAME 'spserver!out_param'@

CREATE PROCEDURE IN_PARAMS (
  IN lowsal DOUBLE, 
  IN medsal DOUBLE, 
  IN highsal DOUBLE, 
  IN department CHAR(3))
SPECIFIC CLI_IN_PARAMS
DYNAMIC RESULT SETS 0
DETERMINISTIC
LANGUAGE C 
PARAMETER STYLE SQL
NO DBINFO
FENCED NOT THREADSAFE
MODIFIES SQL DATA
PROGRAM TYPE SUB
EXTERNAL NAME 'spserver!in_params'@

CREATE PROCEDURE INOUT_PARAM (INOUT medianSalary DOUBLE)
SPECIFIC CLI_INOUT_PARAM
DYNAMIC RESULT SETS 0
NOT DETERMINISTIC
LANGUAGE C 
PARAMETER STYLE SQL
NO DBINFO
FENCED NOT THREADSAFE
READS SQL DATA
PROGRAM TYPE SUB
EXTERNAL NAME 'spserver!inout_param'@

CREATE PROCEDURE CLOB_EXTRACT (
  IN number CHAR(6), 
  OUT buffer VARCHAR(1000))
SPECIFIC CLI_CLOB_EXTRACT
DYNAMIC RESULT SETS 0
NOT DETERMINISTIC
LANGUAGE C 
PARAMETER STYLE SQL
NO DBINFO
FENCED NOT THREADSAFE
READS SQL DATA
PROGRAM TYPE SUB
EXTERNAL NAME 'spserver!extract_from_clob'@

CREATE PROCEDURE DBINFO_EXAMPLE (
  IN job CHAR(8), 
  OUT salary DOUBLE,
  OUT dbname CHAR(128), 
  OUT dbversion CHAR(8))
SPECIFIC CLI_DBINFO_EXAMPLE
DYNAMIC RESULT SETS 0
NOT DETERMINISTIC
LANGUAGE C 
PARAMETER STYLE SQL
DBINFO
FENCED NOT THREADSAFE
READS SQL DATA
PROGRAM TYPE SUB
EXTERNAL NAME 'spserver!dbinfo_example'@

CREATE PROCEDURE MAIN_EXAMPLE (
  IN job CHAR(8), 
  OUT salary DOUBLE)
SPECIFIC CLI_MAIN_EXAMPLE
DYNAMIC RESULT SETS 0
NOT DETERMINISTIC
LANGUAGE C 
PARAMETER STYLE SQL
NO DBINFO
FENCED NOT THREADSAFE
READS SQL DATA
PROGRAM TYPE MAIN
EXTERNAL NAME 'spserver!main_example'@

CREATE PROCEDURE ALL_DATA_TYPES (
  INOUT small SMALLINT, 
  INOUT intIn INTEGER, 
  INOUT bigIn BIGINT,
  INOUT realIn REAL, 
  INOUT doubleIn DOUBLE,
  OUT charOut CHAR(1), 
  OUT charsOut CHAR(15),
  OUT varcharOut VARCHAR(12),
  OUT dateOut DATE,
  OUT timeOut TIME)
SPECIFIC CLI_ALL_DAT_TYPES
DYNAMIC RESULT SETS 0
NOT DETERMINISTIC
LANGUAGE C 
PARAMETER STYLE SQL
NO DBINFO
FENCED NOT THREADSAFE
READS SQL DATA
PROGRAM TYPE SUB
EXTERNAL NAME 'spserver!all_data_types'@

CREATE PROCEDURE ONE_RESULT_SET (IN salValue DOUBLE)
SPECIFIC CLI_ONE_RES_SET
DYNAMIC RESULT SETS 1
NOT DETERMINISTIC
LANGUAGE C 
PARAMETER STYLE SQL
NO DBINFO
FENCED NOT THREADSAFE
READS SQL DATA
PROGRAM TYPE SUB
EXTERNAL NAME 'spserver!one_result_set_to_caller'@

CREATE PROCEDURE TWO_RESULT_SETS (IN salary DOUBLE)
SPECIFIC CLI_TWO_RES_SETS
DYNAMIC RESULT SETS 2
NOT DETERMINISTIC
LANGUAGE C 
PARAMETER STYLE SQL
NO DBINFO
FENCED NOT THREADSAFE
READS SQL DATA
PROGRAM TYPE SUB
EXTERNAL NAME 'spserver!two_result_sets'@

CREATE PROCEDURE GENERAL_EXAMPLE (
  IN edLevel INTEGER, 
  OUT errCode INTEGER,
  OUT errMsg CHAR(32))
SPECIFIC CLI_GEN_EXAMPLE
DYNAMIC RESULT SETS 1
NOT DETERMINISTIC
LANGUAGE C 
PARAMETER STYLE GENERAL
NO DBINFO
FENCED NOT THREADSAFE
READS SQL DATA
PROGRAM TYPE SUB
EXTERNAL NAME 'spserver!general_example'@

CREATE PROCEDURE GENERAL_WITH_NULLS_EXAMPLE (
  IN quarter INTEGER, 
  OUT errCode INTEGER, 
  OUT errMsg CHAR(32))
SPECIFIC CLI_GEN_NULLS
DYNAMIC RESULT SETS 1
NOT DETERMINISTIC
LANGUAGE C 
PARAMETER STYLE GENERAL WITH NULLS
NO DBINFO
FENCED NOT THREADSAFE
READS SQL DATA
PROGRAM TYPE SUB
EXTERNAL NAME 'spserver!general_with_nulls_example'@
