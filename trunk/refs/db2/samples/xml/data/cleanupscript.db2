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
-- SOURCE FILE NAME: cleanupscript.db2
--
-- SAMPLE: Clean up script for the sample reltoxmltype.
--
-- SQL STATEMENTS USED:
--         DROP
--
-- OUTPUT FILE: cleaupscript.out (available in the online documentation)
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
CONNECT TO SAMPLE;
DROP TABLE Products_Relational;
DROP TABLE CustomerInfo_Relational;
DROP TABLE PurchaseOrder_Relational;
DROP TABLE LineItem_Relational;
DROP TABLE CustomerInfo_New;
DROP TABLE PurchaseOrder_new;
CONNECT RESET;
