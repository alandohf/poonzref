-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
--
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
--
-- (C) COPYRIGHT International Business Machines Corp. 1995 - 2006
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: autocfg.db2
--
-- SAMPLE: How to automatically configure DB and DBM cfg parameters based on
--         the Performance Configuration Wizard's recommendations.
--
-- SQL STATEMENT USED:
--         CREATE
--         AUTOCONFIGURE
--         CONNECT
--         GET DB CFG
--         DROP
--
-- OUTPUT FILE: autocfg.out (available in the online documentation)
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

-- Disconnect from any existing database connection
CONNECT RESET;

-- Create a database EXAMPLE using AUTOCONFIGURE parameter
-- Use 'APPLY DB ONLY' to display and apply the recommended changes to
-- DB cfg, buffer pool settings

CREATE DATABASE EXAMPLE
  AUTOCONFIGURE USING MEM_PERCENT 80 NUM_STMTS 20
  APPLY DB ONLY;

-- Restarting the instance to make these changes effective
DB2STOP FORCE;
DB2START;

-- Use 'APPLY DB AND DBM' to display and apply the recommended changes to
-- DB cfg and DBM cfg, buffer pool settings
-- NOTE: Un-commenting and running this will change the DBM cfg parameters

  -- DROP DB EXAMPLE;
  -- CREATE DATABASE EXAMPLE
  -- AUTOCONFIGURE USING MEM_PERCENT 70 NUM_LOCAL_APPS 20 NUM_STMTS 20
  --   APPLY DB AND DBM;

  -- Restarting the instance to make these changes effective
    -- DB2STOP FORCE;
    -- DB2START;

-- Use 'APPLY NONE' to display recommended changes without applying them
DROP DB EXAMPLE;
CREATE DATABASE EXAMPLE
  AUTOCONFIGURE USING MEM_PERCENT 70 NUM_LOCAL_APPS 20 NUM_STMTS 20
  APPLY NONE;

-- Restarting the instance to make these changes effective
DB2STOP FORCE;
DB2START;

-- To autoconfigure an existing EXAMPLE database
CONNECT TO EXAMPLE;
AUTOCONFIGURE USING MEM_PERCENT 90 APPLY DB ONLY;
CONNECT RESET;

-- Restarting the instance to make these changes effective
DB2STOP FORCE;
DB2START;

-- To obtain DB cfg parameters values set by AUTOCONFIGURE
CONNECT TO EXAMPLE;
GET DB CFG FOR EXAMPLE SHOW DETAIL;
CONNECT RESET;

-- Drop EXAMPLE database
DROP DB EXAMPLE;
TERMINATE;
