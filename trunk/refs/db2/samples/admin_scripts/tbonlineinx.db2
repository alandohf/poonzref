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
-- SOURCE FILE NAME: tbonlineinx.db2
--
-- SAMPLE: How to create and reorg indexes on a table
--
-- SQL STATEMENTS USED:
--         CREATE BUFFERPOOL
--         CREATE INDEX
--         CREATE TABLE
--         CREATE TABLESPACE
--         DROP BUFFERPOOL
--         DROP INDEX
--         DROP TABLE
--         DROP TABLESPACE
--
-- OUTPUT FILE: tbonlineinx.out (available in the online documentation)
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

-- create online index on a table

-- connect to sample database
CONNECT TO SAMPLE;

-- create an index on a table with different levels of access to the table 
-- like read-write, read-only, no access

-- create an online index with read-write access to the table 
CREATE INDEX index1 ON employee (lastname ASC);

-- drop the index
DROP INDEX index1;

-- create an index on a table while allowing only read access to it
LOCK TABLE employee IN SHARE MODE;

CREATE INDEX index1 ON employee (lastname ASC);

-- drop the index
DROP INDEX index1;

-- create an online index allowing no access to the table
LOCK TABLE employee IN EXCLUSIVE MODE;

CREATE INDEX index1 ON employee (lastname ASC);

-- reorg online index on the table

-- reorganize the indexes on the table allowing read-write
REORG INDEXES ALL FOR TABLE employee 
  ALLOW WRITE ACCESS 
  ON ALL DBPARTITIONNUMS; 

-- reorganize the indexes on the table allowing read-only
REORG INDEXES ALL FOR TABLE employee 
  ALLOW READ ACCESS 
  ON ALL DBPARTITIONNUMS; 

-- reorganize the indexes on the table allowing no access
REORG INDEXES ALL FOR TABLE employee 
  ALLOW NO ACCESS 
  ON ALL DBPARTITIONNUMS; 

-- drop the index
DROP INDEX index1;

-----------------------------------------------------------------------------
-- create index with large index key part on larger columns upto 8KB

-- create bufferpool with 32K pagesize
CREATE BUFFERPOOL bupl32k SIZE 500 PAGESIZE 32K;

-- create tablespace using above created bufferpool
CREATE TABLESPACE tbsp32k 
  PAGESIZE 32k
  MANAGED BY DATABASE 
  USING (FILE 'tbsp32k' 500)
  BUFFERPOOL bupl32k;

-- create table with large coloumn size.
CREATE TABLE inventory_ident (dept INTEGER,
                              serial_numbers VARCHAR(8190) NOT NULL)
  IN tbsp32k;

-- create a system temporary table space with 32K pages.
-- When the INDEXSORT database configuration parameter is set to Yes
-- (which is the default), then that data is sorted before it is passed
-- to index manager. If sort heap is big enough for the amount of data
-- being sorted, the sort will occur entirely in memory.  However, just
-- in case we need to spill to disk, DB2 will ensure that there is a
-- system temporary tablespace with a large enough page size to spill to.

CREATE SYSTEM TEMPORARY TABLESPACE tmptbsp32k 
  PAGESIZE 32K 
  MANAGED BY SYSTEM 
  USING ('tmp_tbsp_32k')
  EXTENTSIZE 2
  BUFFERPOOL bupl32k;

-- create an index on the serial_numbers column 
-- The upper bound for an index key length is variable based on  
-- page size. The maximum length of an index key part can be:    
-- 1024 bytes for 1K page size, 
-- 2048 bytes for 8K page size,
-- 4096 bytes for 16K page size,
-- 8192 bytes for 32K page size, 
-- and, the index name can be upto 128 char
CREATE INDEX inventory_serial_number_index_ident
  ON inventory_ident (serial_numbers);

-- perform cleanup
DROP INDEX inventory_serial_number_index_ident;
DROP TABLE inventory_ident;
DROP TABLESPACE tmptbsp32k;
DROP TABLESPACE tbsp32k;
DROP BUFFERPOOL bupl32k;

-- disconnect from the database
CONNECT RESET;
TERMINATE;
