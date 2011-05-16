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
-- SOURCE FILE NAME: simple_xmlproc_drop.db2
--
-- SAMPLE: Uncatalog the DB2 CLI stored procedure contained in simple_xmlproc.c
--
-- To run this script from the CLP, issue the command 
--    "db2 -td@ -vf <script-name>"
--    where <script-name> represents the name of this script
----------------------------------------------------------------------------

-- connect to the SAMPLE database
CONNECT TO sample@

-- drop the procedure
DROP PROCEDURE Simple_XML_Proc_CLI ( XML as CLOB(5000),
                                     XML as CLOB(5000))@
CONNECT RESET@
