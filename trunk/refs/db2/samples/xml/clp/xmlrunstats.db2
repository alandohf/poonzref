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
-- SOURCE FILE NAME: xmlrunstats.db2
--
-- SAMPLE: How to perform runstats on a table containing XML type columns
--
-- SQL STATEMENT USED:
--         CREATE SCHEMA
--         CREATE TABLE
--         DROP SCHEMA
--         DROP TABLE
--         INSERT
--         SELECT
--         TERMINATE
--
-- OUTPUT FILE: xmlrunstats.out (available in the online documentation)
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

-- connect to database
CONNECT TO sample;

-- create a schema
CREATE SCHEMA testschema;

-- create a table
CREATE TABLE testschema.customer LIKE customer;

-- insert into the table customer
INSERT INTO testschema.customer (SELECT * FROM customer);

-- perform Runstats on the table
-- update statistics for the table customer

-- perform runstats on table customer for all columns including XML columns
RUNSTATS ON TABLE testschema.customer;

-- perform runstats on table testschema.customer for XML columns 
RUNSTATS ON TABLE testschema.customer ON COLUMNS (Info, History);

-- perform runstats on table customer for XML columns 
-- with the following options:
--
--                 Distribution statistics for all partitions
--                 Frequent values for table set to 30
--                 Quantiles for table set to -1 (NUM_QUANTILES as in DB Cfg)
--                 Allow others to have read-only while gathering statistics
RUNSTATS ON TABLE testschema.customer
  ON COLUMNS(Info, History LIKE STATISTICS)
  WITH DISTRIBUTION ON KEY COLUMNS
  DEFAULT
  NUM_FREQVALUES 30
  NUM_QUANTILES -1
  ALLOW READ ACCESS;

-- perform runstats on table customer 
-- with the following options:
--
--                 EXCLUDING XML COLUMNS.
-- This option allows the user to exclude all XML type columns 
-- from statistics collection. Any XML type columns that have been 
-- specified in the cols-list will be ignored and no statistics will
-- be collected from them. This clause facilitates the collection of 
-- statistics on non-XML columns.
RUNSTATS ON TABLE testschema.customer
  ON COLUMNS(Info, History LIKE STATISTICS)
  WITH DISTRIBUTION ON KEY COLUMNS
  EXCLUDING XML COLUMNS;

-- make sure to rebind all packages that use this table to make
-- use of updated statistics after executing the RUNSTATS command.

-- drop the table customer
DROP TABLE testschema.customer;

-- drop the schema
DROP SCHEMA testschema RESTRICT;

-- disconnect from the database
CONNECT RESET; 

TERMINATE;
