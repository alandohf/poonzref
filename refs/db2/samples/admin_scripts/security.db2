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
-- SOURCE FILE NAME: security.db2
--
-- SAMPLE: How users can query details about the groups, authorities,
--         privileges and ownerships by using APIs without querying various
--         catalog tables for this purpose.
--
--         The sample shows how to:
--         1. Retrieve the groups to which the user belongs to using the UDF
--            SYSPROC.AUTH_LIST_GROUPS_FOR_AUTHID
--         2. Retrieve the objects owned by the user by using the view
--            SYSCAT.OBJECTOWNERS
--         3. Retrieve authorities/privileges directly granted to the user
--            by using the view SYSCAT.PRIVILEGES
--         4. Retrieve the authid type of an authid by using the view
--            SYSCAT.AUTHORIZATIONIDS.
--
-- SQL STATEMENTS USED:
--         CONNECT
--         SELECT
--         TERMINATE
--
-- OUTPUT FILE: security.out (available in the online documentation)
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
-- Connect to sample database
CONNECT TO SAMPLE;

-- Retrieve the group to which the user belongs to
SELECT * FROM table (SYSPROC.AUTH_LIST_GROUPS_FOR_AUTHID (CURRENT USER)) AS ST;

-- Retrieve the objects owned by the current user
SELECT * FROM  SYSIBMADM.OBJECTOWNERS WHERE OWNER = CURRENT USER;
    
-- Retrieve authorities/privileges directly granted to the user
SELECT * FROM SYSIBMADM.PRIVILEGES WHERE AUTHID = CURRENT USER;

-- Retrieve the authorization type of the authid
SELECT * FROM SYSIBMADM.AUTHORIZATIONIDS WHERE AUTHID = CURRENT USER;

-- Disconnect from the sample database;
CONNECT RESET;

TERMINATE;
