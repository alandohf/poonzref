-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
--
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
--
-- (C) COPYRIGHT International Business Machines Corp. 1996 - 2004
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: tbcompress.db2
--
-- SAMPLE: How to create tables with null and default value compression
--         option.
--
-- SQL STATEMENTS USED:
--         ALTER TABLE
--         CREATE TABLE
--         DROP TABLE
--         TERMINATE
--
-- OUTPUT FILE: tbcompress.out (available in the online documentation)
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

-- create a table 'comp_tab'
CREATE TABLE comp_tab(col1 INT NOT NULL WITH DEFAULT,
                      col2 CHAR(7),
                      col3 VARCHAR(7) NOT NULL,
                      col4 DOUBLE);

-- activate VALUE COMPRESSION at table level and COMPRESS SYSTEM DEFAULT at
-- column level

-- rows will be formatted using the new row format on subsequent insert,load
-- and update operation, and NULL values will not be taking up space,
-- if applicable.

-- if the table 'comp_tab' does not have many NULL values, enabling 
-- compression will result in using more disk space than using the 
-- old row format

ALTER TABLE comp_tab ACTIVATE VALUE COMPRESSION;

-- use 'COMPRESS SYSTEM DEFAULT' to save more disk space on system default
-- value for column 'col1'.
-- on subsequent insert, load, and update operations, numerical '0' value 
-- (occupying 4 bytes of storage) for column col1 will not be saved on disk.

ALTER TABLE comp_tab ALTER col1 COMPRESS SYSTEM DEFAULT;

-- switch the table to use the old format.
-- rows inserted, loaded or updated after the ALTER statement will have old 
-- row format.

ALTER TABLE comp_tab DEACTIVATE VALUE COMPRESSION;

-- drop the table
DROP TABLE comp_tab;

-- disconnect from the database
CONNECT RESET;

TERMINATE;
