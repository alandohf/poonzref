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
-- SOURCE FILE NAME: spcreate.db2
--    
-- SAMPLE: How to catalog COBOL stored procedures
--
-- To run this script from the CLP, perform the following steps:
-- 1. connect to the database
-- 2. issue the command "db2 -td@ -vf spcreate.db2"
-----------------------------------------------------------------------------
--
-- For more information on the sample programs, see the README file.
--
-- For information on developing COBOL applications, see the Application
-- Development Guide.
--
-- For information on using SQL statements, see the SQL Reference.
--
-- For the latest information on programming, building, and running DB2 
-- applications, visit the DB2 application development website: 
--     http://www.software.ibm.com/data/db2/udb/ad
-----------------------------------------------------------------------------

CREATE PROCEDURE INPSRV ( IN DEPTNUM SMALLINT,
                          IN DEPTNAME CHAR(14),
                          IN LOCATION CHAR(13),
                          OUT SQLCODE INT)
--- Embedded SQL in COBOL currently does not support result sets.
--- However, if you intend to call this COBOL stored procedure from
--- a client application that can handle result sets, set the DYNAMIC
--- RESULT SETS clause to 1, and follow the instructions in the code
--- comments in inpsrv.sqb.
  DYNAMIC RESULT SETS 0
  LANGUAGE COBOL 
  PARAMETER STYLE GENERAL
  NO DBINFO
  FENCED
  NOT THREADSAFE
  MODIFIES SQL DATA
  PROGRAM TYPE SUB
  EXTERNAL NAME 'inpsrv!inpsrv'@
