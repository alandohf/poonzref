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
-- SOURCE FILE NAME: SpDrop.db2
--    
-- SAMPLE: How to uncatalog the stored procedures contained in SpServer.java
--
-- To run this script from the CLP, perform the following steps:
-- 1. connect to the database
-- 2. issue the command "db2 -td@ -vf <script-name>"
--    where <script-name> represents the name of this script
----------------------------------------------------------------------------

DROP PROCEDURE OUT_LANGUAGE (CHAR(8))@

DROP PROCEDURE OUT_PARAM (DOUBLE)@

DROP PROCEDURE IN_PARAMS (DOUBLE, DOUBLE, DOUBLE, CHAR(3))@

DROP PROCEDURE INOUT_PARAM (DOUBLE)@

DROP PROCEDURE CLOB_EXTRACT (CHAR(6), VARCHAR(1000))@

DROP PROCEDURE DECIMAL_TYPE (DECIMAL(10,2))@

DROP PROCEDURE ALL_DATA_TYPES (SMALLINT, INTEGER, BIGINT, REAL, DOUBLE,
     CHAR(1), CHAR(15), VARCHAR(12), DATE, TIME)@

DROP PROCEDURE ONE_RESULT_SET (DOUBLE)@

DROP PROCEDURE TWO_RESULT_SETS (DOUBLE)@

