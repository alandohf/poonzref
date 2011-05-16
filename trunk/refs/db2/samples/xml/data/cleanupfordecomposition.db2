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
-- SOURCE FILE NAME: setupfordecomposition.db2
--
-- SAMPLE: This is the clean up script for the sample xmldecompostion.db2,
--         xmldecomposition.sqc, xmldecomposition.java.
--         The tables are dropped that were created by the setup script.
--
-- SQL STATEMENTS USED:
--         DROP
--
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

--CONNET TO DATABASE
CONNECT TO SAMPLE;

-- Deregister the Schema from XSR
DROP XSROBJECT XDB.BOOKDETAIL;

-- DROP the table XDB.BOOK_CONTENTS
DROP TABLE XDB.BOOK_CONTENTS; 

-- DROP the table ADMIN.BOOK_CONTENTS
DROP TABLE ADMIN.BOOK_AUTHOR;

-- RESET CONNECTION
CONNECT RESET;
