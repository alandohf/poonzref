-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
--
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
--
-- (C) COPYRIGHT International Business Machines Corp. 2006
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: truncate.db2
--
-- SAMPLE: How to implemenet truncate table functionality.
--
-- SQL STATEMENTS USED:
--	   DROP PROCEDURE
--	   DROP TABLE
--         CALL
--         CONNECT
--         CREATE PROCEDURE
--         CREATE TABLE
--         INSERT INTO
--         SELECT
--         TERMINATE
--
-- Note: Use following command to execute the sample:
--         db2 -td@ -vf truncate.db2
--
-- OUTPUT FILE: truncate.out (available in the online documentation)
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

-- Connect to 'sample' database
CONNECT TO SAMPLE@

-- 'TRUNCATE' stored procedure removes all rows from the table without using
-- DELETE operation thereby eliminating extensive logging and resulting in
-- better performance.
-- Create a stored Procedure 'truncate' to implement the truncate table
-- functionality. Use IMPORT with REPLACE INTO clause to implement truncate.
-- IMPORT is done using ADMIN_CMD in SQL. Use '/dev/null'(for UNIX) &
-- 'NUL'(for windows) for IMPORT as this file always exists & does not
-- contain anything.

-- Create the stored procedure 'truncate'

CREATE PROCEDURE truncate(IN sch_name VARCHAR(130),IN tab_name VARCHAR(130)) 
  LANGUAGE SQL
  ---------------------------------
  -- SQL Stored Procedure truncate
  ---------------------------------
  BEGIN

    DECLARE stmt VARCHAR(1000);
    DECLARE param VARCHAR(1000);
    DECLARE full_name VARCHAR(1000);
    DECLARE a VARCHAR(130);

    IF sch_name IS NULL 
      THEN
        SET full_name = tab_name;

        -- Check whether the table exists or not
        SELECT tabname INTO a
          FROM SYSCAT.TABLES
          WHERE tabname = UCASE(tab_name);

    ELSE
      SET full_name = sch_name||'.'||tab_name;

      -- Check whether the table exists or not
      SELECT tabname INTO a
        FROM SYSCAT.TABLES
        WHERE tabname = UCASE(tab_name) AND tabschema = UCASE(sch_name);

    END IF;

    IF UCASE(a) = UCASE(tab_name) 
      THEN
        -- Uncomment one of the following statements depending on the
        -- platform on which the sample is run.
        SET param = 'IMPORT FROM /dev/null OF DEL REPLACE INTO '||full_name;
        -- SET param = 'IMPORT FROM NUL OF DEL REPLACE INTO '||full_name;

        SET stmt = 'CALL SYSPROC.ADMIN_CMD (?)';
 
        PREPARE s1 FROM stmt;
        EXECUTE s1 USING param;

    ELSE

      -- Table does not exists.

    END IF;

  END @

-- Create and insert some values into the table 'tab1'
CREATE TABLE tab1 ( col1  INTEGER, col2  VARCHAR(130) )@

INSERT INTO tab1 VALUES ( 1, 'some data' ), ( 2, NULL )@

-- Verify the current contents of table tab1
SELECT * FROM tab1@

-- Call the truncate stored procedure for the DB2INST1 schema, and the 
-- table 'tab1'
CALL truncate(CURRENT SCHEMA, 'tab1')@

-- Verify that the table contents have been truncated.
SELECT * FROM tab1@

-- Insert some new values into the tab1 table
INSERT INTO tab1 VALUES ( 2, 'some new data' ), ( 3, NULL )@

SELECT * FROM tab1@

-- Call the truncate procedure with a NULL schema
CALL truncate(NULL, 'tab1')@

-- Verify that the table contents have been truncated.
SELECT * FROM tab1@

-- Drop the table tab1
DROP TABLE tab1@

-- Drop the procedure TRUNCATE
DROP PROCEDURE TRUNCATE@

-- Disconnect from the sample database
CONNECT RESET@

TERMINATE@