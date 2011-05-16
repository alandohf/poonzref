----------------------------------------------------------------------------
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
----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: xquery_xmlproc_create.db2
--
-- SAMPLE: How to catalog the DB2 CLI stored procedure contained in
--         xquery_xmlproc.c
--
-- To run this script from the CLP, issue the command 
--                     db2 -td@ -vf xquery_xmlproc_create.db2
----------------------------------------------------------------------------
-- For more information on the sample programs, see the README file.
--
-- For information on developing CLI applications, see the CLI Guide
-- and Reference.
--
-- For information on using SQL statements, see the SQL Reference.
--
-- For the latest information on programming, building, and running DB2
-- applications, visit the DB2 application development website:
--     http://www.software.ibm.com/data/db2/udb/ad
-----------------------------------------------------------------------------

-- connect to the SAMPLE database
CONNECT TO sample@

-- creating procedure
CREATE PROCEDURE Supp_XML_Proc_CLI( IN  inXML XML as CLOB(5000),
                                    OUT outXML XML as CLOB(5000))
LANGUAGE C
PARAMETER STYLE SQL
FENCED
PARAMETER CCSID UNICODE
EXTERNAL NAME 'xquery_xmlproc!xquery_proc'@

CONNECT RESET@


