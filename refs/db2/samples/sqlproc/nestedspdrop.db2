-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
--
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
--
-- (C) COPYRIGHT International Business Machines Corp. 1995 - 2002        
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: nestedspdrop.db2
--    
-- SAMPLE: To drop the OUT_AVERAGE, OUT_MEADIN and MAX_SALARY SQL procedures 
--         that are created with the nestedsp.db2 script.
--
-- To drop the SQL procedures:
-- 1. Connect to the database
-- 2. Enter the command "db2 -td@ -vf nestedspdrop.db2"
--
-----------------------------------------------------------------------------
--
-- For more information on the sample scripts, see the README file.
--
-- For information on creating SQL procedures, see the Application
-- Development Guide.
--
-- For information on using SQL statements, see the SQL Reference.
--
-- For the latest information on programming, building, and running DB2 
-- applications, visit the DB2 application development website: 
--     http://www.software.ibm.com/data/db2/udb/ad
-----------------------------------------------------------------------------

DROP PROCEDURE OUT_AVERAGE (DOUBLE, DOUBLE, DOUBLE) @

DROP PROCEDURE OUT_MEDIAN (DOUBLE, DOUBLE) @

DROP PROCEDURE MAX_SALARY(DOUBLE) @

