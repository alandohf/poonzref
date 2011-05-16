----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
-- Governed under the terms of the IBM Public License
--
-- (C) COPYRIGHT International Business Machines Corp. 2006
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: Simple_XmlProc_Drop.db2
--
-- SAMPLE: How to uncatalog the stored procedure in Simple_XmlProc.java
--
-- To run this script from the CLP, 
--  issue the command "db2 -td@ -vf Simple_XmlProc_Drop.db2"
----------------------------------------------------------------------------

-- connect to the SAMPLE database
CONNECT TO sample@

-- drop the procedure
DROP PROCEDURE Simple_XML_Proc_Java( XML AS CLOB(5000), XML AS CLOB(5000), INTEGER)@

CONNECT RESET@

