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
-- SOURCE FILE NAME: tbrowcompress.db2
--
-- SAMPLE: How to perform row compression on a table 
--
--         This sample shows:
--         1. How to enable the row compression after a table is created.
--         2. How to enable the row compression during table creation.
--         3. Usage of the options to REORG to use the exiting dictionary 
--            or creating a new dictionary.   
--         4. How to estimate the effectiveness of the compression.
--
--
-- SQL STATEMENTS USED:
--         ALTER TABLE
--         CREATE TABLE
--         DELETE
--         DROP TABLE
--         EXPORT
--         IMPORT
--         INSERT
--         INSPECT
--         LOAD
--         REORG
--         RUNSTATS
--         TERMINATE
--         UPDATE
--
-- OUTPUT FILE: tbrowcompress.out (available in the online documentation)
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

-- Connect to sample database. 
CONNECT TO sample;

-- Create a schema
CREATE SCHEMA testschema;

-- Create a temporary table
CREATE TABLE testschema.temp(empno INT, sal DOUBLE);

-- Insert data into the table and export the data in order to obtain 
-- dummy.del file in the required format for load. 
INSERT INTO testschema.temp VALUES(100, 20000);
INSERT INTO testschema.temp VALUES(200, 30000);
INSERT INTO testschema.temp VALUES(300, 30500);
 
EXPORT TO dummy.del OF DEL SELECT * FROM testschema.temp;

-- Drop the table.
DROP TABLE testschema.temp;

-- Create a table without enabling row compression at the time of table creation. 
CREATE TABLE testschema.empl (emp_no INT, salary DOUBLE);
 
-- Perform a load operation to load three rows of data into empl.
LOAD FROM dummy.del OF DEL INSERT INTO testschema.empl;
 
-- Enable row compression.  
ALTER TABLE testschema.empl COMPRESS YES;

-- Perform non-inplace reorg to compress rows and to retain existing dictionary.
REORG TABLE testschema.empl;
 
-- Drop the table.
DROP TABLE testschema.empl;

-- Create a table enabling compression initially.  
CREATE TABLE testschema.empl (emp_no INT, salary DOUBLE) COMPRESS YES;

-- Load data into table.
LOAD FROM dummy.del OF DEL INSERT INTO testschema.empl;

-- Perform reorg to compress rows.
REORG TABLE testschema.empl;

-- Perform modifications on table.
INSERT INTO testschema.empl VALUES(400, 30000);
UPDATE testschema.empl SET salary = salary + 1000;
DELETE FROM testschema.empl WHERE emp_no = 200;

-- Disable row compression for the table.
ALTER TABLE testschema.empl COMPRESS NO;

-- Perform reorg to remove existing dictionary.
-- New dictionary will be created and all the rows processed by the reorg 
-- are decompressed. 
 
REORG TABLE testschema.empl RESETDICTIONARY;
 
-- Drop the table.
DROP TABLE testschema.empl; 
 
-- Create a table, load data, perform some modifications on the table.
-- All the rows will be in non-compressed state till reorg is performed. 
 
CREATE TABLE testschema.empl (emp_no INT, salary DOUBLE);

IMPORT FROM dummy.del OF DEL INSERT INTO testschema.empl;

ALTER TABLE testschema.empl COMPRESS YES;

INSERT INTO testschema.empl VALUES(400, 30000);

-- Perform inspect to estimate the effectiveness of compression.
-- Inspect has to be run before the REORG utility. 
-- Inspect allows you to look over tablespaces and tables for their
-- architectural integrity.
-- 'result' file contains percentage of bytes saved from compression,
-- Percentage of rows ineligible for compression due to small row size,
-- Compression dictionary size, Expansion dictionary size etc.
-- To view the contents of 'result' file perform
--    db2inspf result result.out; This formats the 'result' file to 
-- readable form.

INSPECT ROWCOMPESTIMATE TABLE NAME empl SCHEMA testschema RESULTS KEEP result;
 
REORG TABLE testschema.empl;

-- All the rows will be compressed including the one inserted after reorg.
INSERT INTO testschema.empl VALUES(500, 40000);

-- Disable row compression for the table. 
-- Rows inserted after this will be non-compressed. 
ALTER TABLE testschema.empl COMPRESS NO;
INSERT INTO testschema.empl VALUES(600, 40500);

-- Enable row compression again to compress the rows inserted later. 
ALTER TABLE testschema.empl COMPRESS YES;
INSERT INTO testschema.empl VALUES(700, 40600);

-- Perform runstats to measure the effectiveness of compression using 
-- compression related catalog fields. New columns will be updated to 
-- catalog table after runstats is performed on a compressed table.
 
RUNSTATS ON TABLE testschema.empl;

-- Display the contents of 'empl' table.
SELECT * FROM testschema.empl;

-- Display the contents of 'SYSCAT.TABLES' to measure effectiveness 
-- of compression. 
SELECT avgrowsize, avgcompressedrowsize, pctpagessaved, avgrowcompressionratio, 
  pctrowscompressed from SYSCAT.TABLES WHERE tabname = 'EMPL'; 

-- Drop the table.
DROP TABLE testschema.empl;

-- Drop the schema
DROP SCHEMA testschema RESTRICT;

-- Remove temporary file.
! rm dummy.del;

-- Delete the 'result1' file created by INSPECT command
-- Uncomment one of the following based on the platform it is run

-- ! rm $HOME/sqllib/db2dump/result;
-- ! del $HOME\sqllib\db2dump\result;

-- Disconnect from database.
CONNECT RESET;

TERMINATE;
