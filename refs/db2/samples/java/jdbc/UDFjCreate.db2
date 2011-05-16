-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
-- 
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
-- 
-- (C) COPYRIGHT International Business Machines Corp. 1997 - 2002
-- All Rights Reserved.
-- 
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: UDFjCreate.db2
--    
-- SAMPLE: How to catalog the Java UDFs contained in UDFjsrv.java 
--
-- To run this script from the CLP, perform the following steps:
-- 1. connect to the database
-- 2. issue the command "db2 -td@ -vf <script-name>"
--    where <script-name> represents the name of this script
----------------------------------------------------------------------------

CREATE FUNCTION scalarUDF(CHAR(5), DOUBLE)
RETURNS DOUBLE
EXTERNAL NAME 'UDFjsrv!scalarUDF'
LANGUAGE JAVA
PARAMETER STYLE JAVA
NOT VARIANT
FENCED
CALLED ON NULL INPUT
NO SQL
NO EXTERNAL ACTION@

