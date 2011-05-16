-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
--
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
--
-- (C) COPYRIGHT International Business Machines Corp. 1996 - 2006
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: admincmd_tbload.db2
--
-- SAMPLE: How to load data in to table using ADMIN_CMD routine.
--
-- SQL STATEMENTS USED:
--         CREATE TABLE
--         DROP TABLE
--         CALL  
--         TERMINATE
--
-- OUTPUT FILE: admincmd_tbload.out (available in the online documentation)
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

-- connect to 'sample' database
CONNECT TO SAMPLE;

-- create a table to prepare LOAD data
CREATE TABLE temp (c1 INT, c2 VARCHAR(20));

-- insert the data into the table 'temp'
INSERT INTO temp VALUES (1, 'A'), (2, 'B'), (3, 'C');

-- export the table data to file 'load_file1.ixf'.
-- below commands are specific to Unix platforms
-- toggle the commented & uncommented statements if executing on Windows
!db2 "EXPORT TO $HOME/load_file1.ixf OF IXF SELECT * FROM temp";
-- !db2 "EXPORT TO %HOME%\\load_file1.ixf OF IXF SELECT * FROM temp";

-- delete the data from the table 'temp'
DELETE FROM temp;

-- insert the data into the table 'temp'.
-- (This data will be used for LOAD with REPLACE)
INSERT INTO temp VALUES (11, 'AA'), (12, 'BB'), (13, 'CC');

-- export the table data to file 'load_file2.ixf'.
-- below commands are specific to Unix platforms
-- toggle the commented & uncommented statements if executing on Windows
!db2 "EXPORT TO $HOME/load_file2.ixf OF IXF SELECT * FROM temp";
-- !db2 "EXPORT TO %HOME%\\load_file2.ixf OF IXF SELECT * FROM temp";

-- creating table to be laoded with data
CREATE TABLE temp_load LIKE temp;

-- loading data from data file inserting data into the table temp_load.
-- below commands are specific to Unix platforms
-- toggle the commented & uncommented statements if executing on Windows
!db2 "CALL ADMIN_CMD('LOAD FROM $HOME/load_file1.ixf of IXF INSERT INTO temp_load')";
-- !db2 "CALL ADMIN_CMD('LOAD FROM %HOME%\\load_file1.ixf of IXF INSERT INTO temp_load')";

-- display the contents of the table 'temp_load'
SELECT * FROM temp_load;

-- loading data from data file replacing data loaded by the previous load.
-- below commands are specific to Unix platforms
-- toggle the commented & uncommented statements if executing on Windows
!db2 "CALL ADMIN_CMD('LOAD FROM $HOME/load_file2.ixf of IXF REPLACE INTO temp_load')";
-- !db2 "CALL ADMIN_CMD('LOAD FROM %HOME%\\load_file2.ixf of IXF REPLACE INTO temp_load')";

-- display the contents of the table 'temp_load'
SELECT * FROM temp_load;

-- dropping the table
DROP TABLE temp_load;

-- Drop the table 'temp'
DROP TABLE temp;

-- disconnect from the database
CONNECT RESET;

TERMINATE;

