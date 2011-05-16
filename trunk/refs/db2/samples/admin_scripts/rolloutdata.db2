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
-- SOURCE FILE NAME: rolloutdata.db2
--
-- SAMPLE: How to perform data-roll-out from a partitioned table.
--
-- SQL STATEMENTS USED:
--         ALTER TABLE
--         CREATE TABLE
--         CREATE TABLESPACE
--         DROP TABLE
--         INSERT
--         TERMINATE
--
-- OUTPUT FILE: rolloutdata.out (available in the online documentation)
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

-- Create DMS tablespaces.
CREATE TABLESPACE tbsp1 MANAGED BY DATABASE USING (FILE 'conta' 1000);
CREATE TABLESPACE tbsp2 MANAGED BY DATABASE USING (FILE 'contb' 1000);

-- Create a partitioned table on a list of tablespaces. A table 'emp_table' 
-- with three partitions will be created i.e. part0 is placed in tbsp1, 
-- part1 is placed in tbsp2, and part2 is placed in tbsp1. Data partitions   
-- are placed in tablespaces in Round Robin fashion. 

CREATE TABLE emp_table (emp_no INTEGER NOT NULL, 
                  emp_name VARCHAR(10),
                  dept VARCHAR(5),
                  salary DOUBLE DEFAULT 3.14)
  IN  tbsp1, tbsp2
  PARTITION BY RANGE (emp_no)
    (STARTING FROM (1) ENDING (100),
    STARTING FROM (101) ENDING (200),
    STARTING FROM (201) ENDING (300));

-- Insert data into 'emp_table'.
INSERT INTO emp_table VALUES
        	  (1,   'Sam',  'E31', 3.34),
        	  (101, 'James','E32', 4.00),
    		  (201, 'Bill', 'E33', 3.75);

-- Detach a partition from 'emp_table'. 
-- ALTER TABLE statement along with DETACH PARTITION clause is used to 
-- remove a partition from the base table.
ALTER TABLE emp_table DETACH PARTITION part1 INTO emp_part0;

-- Display the contents of each table.
SELECT emp_no, emp_name, dept, salary FROM emp_part0;
SELECT emp_no, emp_name, dept, salary FROM emp_table;

-- Drop the tables.
DROP TABLE emp_part0;
DROP TABLE emp_table;

-- Drop the tablespaces.
DROP TABLESPACE tbsp1;
DROP TABLESPACE tbsp2;

-- Disconnect from database.
CONNECT RESET;

TERMINATE;
