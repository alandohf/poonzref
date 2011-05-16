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
-- SOURCE FILE NAME: simple_xmlproc_create.db2
--
-- SAMPLE: How to catalog the DB2 C stored procedure contained in
--         simple_xmlproc.sqc
--
-- To run this script from the CLP 
--    issue the command "db2 -td@ -vf <script-name>"
--    where <script-name> represents the name of this script
----------------------------------------------------------------------------
-- For more information on the sample programs, see the README file.
--
-- For information on developing C applications, see the C Guide
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
CREATE PROCEDURE Simple_XML_Proc_C( IN inXML XML as CLOB(5000), 
                                    OUT outXML XML as CLOB(5000),
                                    OUT outReturnCode INTEGER)
LANGUAGE C
PARAMETER STYLE SQL
FENCED
DYNAMIC RESULT SETS 1
PARAMETER CCSID UNICODE
EXTERNAL NAME 'simple_xmlproc!simple_proc'@

CONNECT RESET@


