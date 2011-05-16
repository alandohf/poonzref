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
-- SOURCE FILE NAME: largerid.db2
--
-- SAMPLE: How to enable Large RIDs support on both new tables/tablespaces and 
--         existing tables/tablespaces.
--
--         This sample shows:
--         1. Converting a regular DMS tablespaces to a large DMS tablespaces.
--         2. Table level migration - from earlier versions to new version to 
--            support larger table sizes.
--         3. Reorganizing indexes to support Large RIDs.
--
-- SQL STATEMENTS USED:
--         ALTER TABLESPACE
--         CREATE TABLE 
--         CREATE TABLESPACE
--	   REORG
--	   SELECT
--         SET INTEGRITY
--         TERMINATE
--
-- OUTPUT FILE: largerid.out (available in the online documentation)
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

-- Connect to database.
CONNECT TO sample;

-- The following scenario shows how a table which resides in a regular DMS 
-- tablespaces can be converted to reside into large DMS tablespaces to 
-- support large RIDs. 

-- Create a regular DMS tablespace.
CREATE REGULAR TABLESPACE largetbsp MANAGED BY DATABASE USING (FILE 'cont1' 1000);

-- Create a table in 'largetbsp' DMS tablespace.
CREATE TABLE large (max INT, min INT) IN largetbsp;

-- Create an index on 'large' table.
CREATE INDEX large_ind ON large (max);

-- Alter tablespace from a regular DMS tablespace to large DMS tablespace to 
-- support large RIDs.
ALTER TABLESPACE largetbsp CONVERT TO LARGE;

-- Rebuild/Reogranize indexes on table to support large RIDs.
-- Reorg reorganizes all indexes defined on a table by rebuilding the 
-- index data into unfragmented, physically contiguous pages.
-- This will permit the table use 4-byte page numbers but not enable
-- the table to use more than 255 slots on a page. 

-- To use more than 255 slots on a page:
-- a) The table definition and the table space page size must allow it.
-- b) the table must be reorganized using classic, off-line reorg.

REORG INDEXES ALL FOR TABLE large;

-- Drop index, table and tablespace.
DROP INDEX large_ind;
DROP TABLE large;
DROP TABLESPACE largetbsp;

-- The following scenario shows how a partitioned table which resides in a 
-- regular DMS tablespaces  can be converted to reside into large DMS 
-- tablespaces to support large RIDs. 

-- Create regular DMS tablespaces.
CREATE REGULAR TABLESPACE tbsp1 MANAGED BY DATABASE USING (FILE 'cont1' 1000);
CREATE REGULAR TABLESPACE tbsp2 MANAGED BY DATABASE USING (FILE 'cont2' 1000);
CREATE REGULAR TABLESPACE tbsp3 MANAGED BY DATABASE USING (FILE 'CONT3' 1000);

-- Create a partitioned table.
CREATE TABLE large (max SMALLINT NOT NULL, CONSTRAINT CC CHECK (max>0)) 
  PARTITION BY RANGE (max) 
    (PART  part1 STARTING FROM (1) ENDING (3) IN tbsp1, 
    PART part2 STARTING FROM (4) ENDING (6) IN tbsp2, 
    PART part3 STARTING FROM (7) ENDING (9) IN tbsp3);

-- Insert data into the table.
INSERT INTO large VALUES (1), (2), (3), (4), (5), (6), (7), (8), (9);

-- Display records from the table.
SELECT * FROM large;

-- If a partitioned table has data partitions in different regular DMS 
-- tablespaces, then the tablespaces cannot be converted to large
-- with the current definition.
-- To do this, first detach all the partitions of the table, later
-- convert all the tablespaces to large, reorg all the detached 
-- partitions to support large RID. Finally, reattach the partitions.
-- Now the entire table supports large RIDs.

ALTER TABLE large DETACH PARTITION PART3 INTO TABLE detach_part3;
ALTER TABLE large DETACH PARTITION PART2 INTO TABLE detach_part2;

-- Display records contained in each table.
SELECT * FROM large;
SELECT * FROM detach_part2;
SELECT * FROM detach_part3;

-- Convert all tablespaces from regular DMS tablespace to large DMS tablespace.
ALTER TABLESPACE tbsp3 CONVERT TO LARGE;
ALTER TABLESPACE tbsp2 CONVERT TO LARGE;
ALTER TABLESPACE tbsp1 CONVERT TO LARGE;

-- Reorganize the detached partitions in order to support large RIDs. 
-- Reorg reorganizes a table by reconstructing the rows to eliminate 
-- fragmented data, and by compacting information.

REORG TABLE detach_part3;
REORG TABLE detach_part2;
REORG TABLE large;

-- Reattach the reorganized detached partitions for table to support 
-- large RIDs. 
ALTER TABLE large ATTACH PARTITION part2 STARTING FROM (4) ENDING (6) 
  FROM TABLE detach_part2;
ALTER TABLE large ATTACH PARTITION part3 STARTING FROM (7) ENDING (9) 
  FROM TABLE detach_part3;

-- After performing above ALTER statements, table is put into 
-- set integrity peniding  state.
-- Before performing SELECT, table must be brought out from pending state.
SET INTEGRITY FOR large IMMEDIATE CHECKED;

-- Display records from the table.
SELECT * FROM large;

-- Drop tables and tablespaces.
DROP TABLE large;
DROP TABLESPACE tbsp1;
DROP TABLESPACE tbsp2;
DROP TABLESPACE tbsp3;

-- Disconnect from a database.
CONNECT RESET;

TERMINATE;
