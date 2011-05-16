-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
--
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
--
-- (C) COPYRIGHT International Business Machines Corp. 1996 - 2006
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: gethealthconfig.db2
--
-- SAMPLE: How to get definition, alert configuration and default alert 
--         configurations 
--
-- SQL STATEMENTS USED:
--         SELECT
--         TERMINATE
--
-- OUTPUT FILE: gethealthconfig.out (available in the online documentation)
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

-- connect to sample database
CONNECT TO SAMPLE;

-- Get the definition for health indicator db2.mon_heap_util
SELECT D.ID, 
       SUBSTR(D.SHORT_DESCRIPTION, 1, 25) AS SHORT_DESCRIPTION, 
       SUBSTR(D.FORMULA, 1, 55) AS FORMULA
  FROM TABLE(SYSPROC.HEALTH_GET_IND_DEFINITION('')) AS D
  WHERE NAME = 'db2.mon_heap_util';

-- Get alert configuration for health indicator db.log_util on database SAMPLE
SELECT SUBSTR(D.NAME, 1, 15) AS NAME,
       C.EVALUATE,
       C.ACTION_ENABLED,
       C.WARNING_THRESHOLD,
       C.ALARM_THRESHOLD
  FROM TABLE(SYSPROC.HEALTH_GET_IND_DEFINITION('')) AS D, 
       TABLE(SYSPROC.HEALTH_GET_ALERT_CFG('DB', 'O', 'SAMPLE', '')) AS C 
  WHERE D.ID = C.ID AND D.NAME = 'db.log_util';

-- Get Global default alert configuration settings for tablespaces on health indicator ts.ts_util 
SELECT SUBSTR(D.NAME, 1, 15) AS NAME,
       C.EVALUATE,
       C.ACTION_ENABLED,
       C.WARNING_THRESHOLD,
       C.ALARM_THRESHOLD
  FROM TABLE(SYSPROC.HEALTH_GET_IND_DEFINITION('')) AS D, 
       TABLE(SYSPROC.HEALTH_GET_ALERT_CFG('TS', 'G', '', '')) AS C 
  WHERE D.ID = C.ID AND D.NAME = 'ts.ts_util';

-- disconnect from the database
CONNECT RESET;

TERMINATE;