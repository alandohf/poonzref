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
-- SOURCE FILE NAME: xmldb2look.db2
--
-- SAMPLE: How to perform db2look for XML datatype
--
-- PREREQUISITES:
--         Create a directory "tempdir" in the current working directory.
--         A schema WALID, created by user NEWTON must exist.
--
-- SQL STATEMENT USED:
--         CONNECT
--         TERMINATE
--
-- SYSTEM COMMANDS USED:
--         DB2LOOK
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

-- connect to the SAMPLE database
CONNECT TO sample;

-- Generate DDL statements needed to recreate the objects in database SAMPLE 
-- and Exports XSR objects into 'tempdir' directory.
-- The db2look output is sent to file xmldb2look_out1.sql
!db2look -d sample -e -xs -xdir tempdir -o xmldb2look_out1.sql;

-- Generate the DDL statements needed to recreate the objects 
-- created by user NEWTON in database SAMPLE 
-- and Exports XSR objects into 'tempdir' directory
-- The db2look output is sent to file xmldb2look_out2.sql
!db2look -d sample -e -xs -xdir tempdir -u NEWTON -o xmldb2look_out2.sql;

-- Generate the DDL statements needed to recreate the objects
-- that have schema WALID, created by user NEWTON, in database SAMPLE 
-- and Exports XSR objects into 'tempdir' directory. 
-- The db2look output is sent to file xmldb2look_out3.sql
!db2look -d sample -e -xs -xdir tempdir -u NEWTON -z WALID -o xmldb2look_out3.sql;

-- Generate the DDL statements needed to recreate the objects 
-- created by all users in the database SAMPLE 
-- and Exports XSR objects into 'tempdir' directory.
-- The db2look output is sent to file xmldb2look_out4.sql
!db2look -d sample -e -xs -xdir tempdir -a -o xmldb2look_out4.sql;

-- disconnect from the database
CONNECT RESET;

TERMINATE;

