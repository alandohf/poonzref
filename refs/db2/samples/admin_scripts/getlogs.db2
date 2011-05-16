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
-- SOURCE FILE NAME: getlogs.db2
--
-- SAMPLE: How to get the customer view of diagnostic log file entries
-- 
--         This sample shows:
--         1. How to retrieve messages from the notification log starting 
--	      at a specified point in time.
--         2. How to retrieve messages from the notification log written 
--	      over the last week or over the last 24 hours.
--
-- SQL STATEMENTS USED:
--        CONNECT
--	  SELECT 
--        TERMINATE  	 
--
-- OUTPUT FILE: getlogs.out (available in the online documentation)
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

-- Connect to sample database. 
CONNECT TO sample;

-- Retrieve all notification messages written after the specified 
-- timestamp (for example '2006-02-22', '06.44.44')
-- If NULL is specified as the input timestamp to PD_GET_LOG_MSGS UDF, 
-- then all the log entries will be returned.
SELECT dbname,
       msgseverity
  FROM TABLE (PD_GET_LOG_MSGS(TIMESTAMP('2006-02-22','06.44.44'))) AS t
  ORDER BY TIMESTAMP;

-- Retrieve all notification messages written in the last week from 
-- all partitions in chronological order.
SELECT instancename,
       dbpartitionnum,
       dbname,
       msgtype
  FROM TABLE(PD_GET_LOG_MSGS(current_timestamp - 7 days)) AS t 
  ORDER BY TIMESTAMP;

-- Get all critical log messages logged over the last 24 hours, order 
-- by most recent 
SELECT timestamp,
       instancename,
       dbname,
       appl_id,
       msg
  FROM SYSIBMADM.PDLOGMSGS_LAST24HOURS WHERE msgseverity = 'C' 
  ORDER BY TIMESTAMP DESC;

-- Disconnect from database.
CONNECT RESET;

TERMINATE;
