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
-- SOURCE FILE NAME: Xquery_XmlProc_Create.db2
--
-- SAMPLE: How to catalog the stored procedure contained in Xquery_XmlProc.java
--
-- To run this script from the CLP,
-- issue the command "db2 -td@ -vf Xquery_XmlProc_Create.db2"
----------------------------------------------------------------------------

-- connect to the SAMPLE database
CONNECT TO sample@

-- create the procedure
CREATE PROCEDURE Supp_XML_Proc_Java( IN data XML as CLOB(5000),
                                     OUT CustInfo XML as CLOB(5000),
                                     OUT RetCode INTEGER)
DYNAMIC RESULT SETS 0
NOT DETERMINISTIC
LANGUAGE JAVA
PARAMETER STYLE DB2GENERAL
NO DBINFO
FENCED
THREADSAFE
MODIFIES SQL DATA
PROGRAM TYPE SUB
EXTERNAL NAME 'Xquery_XmlProc.Xquery_Proc'@

CONNECT RESET@
