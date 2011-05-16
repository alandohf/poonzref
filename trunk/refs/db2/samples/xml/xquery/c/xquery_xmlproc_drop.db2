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
-- SOURCE FILE NAME: xquery_xmlproc_drop.db2
--
-- SAMPLE: How to uncatalog the stored procedures contained in xquery_xmlproc.sqc
--
-- To run this script from the CLP, perform the following steps:
-- 1. issue the command "db2 -td@ -vf xquery_xmlproc_drop.db2"
-----------------------------------------------------------------------------
-- For more information on the sample programs, see the README file.
--
-- For information on developing C applications, see the Application
-- Development Guide.
--
-- For information on using SQL statements, see the SQL Reference.
--
-- For the latest information on programming, building, and running DB2
-- applications, visit the DB2 application development website:
--     http://www.software.ibm.com/data/db2/udb/ad
-----------------------------------------------------------------------------

-- connect to the SAMPLE database
CONNECT TO sample@

-- drop the procedure Supp_XML_Proc_C
DROP PROCEDURE Supp_XML_Proc_C( XML AS CLOB(5000), XML AS CLOB(5000), INTEGER)@

-- reset the connection
CONNECT RESET@


