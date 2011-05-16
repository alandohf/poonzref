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
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: monitor.db2
--
-- SAMPLE: The sample will demonstrate the usage of the table functions 
--         SNAP_GET_APPL, SNAP_GET_APPL_INFO and the views SYSIBMADM.SNAPUTIL,
--         SYSIBMADM.SNAPUTIL_PROGRESS and SYSIBMADM.TBSP_UTILIZATION in 
--         retrieving the snapshot data associated with the corresponding 
--         snapshot groupings and elements as follows.
--           
--         1.   Retrieve the snapshot statistics about the top CPU consuming
--              applications for the currently connected database on the
--              currently connected partition using the table functions 
--              SNAP_GET_APPL() and SNAP_GET_APPL_INFO().
--
--         2.   Retrieve the snapshot statistics about the  progress of all
--              the active utilities on all partitions using the views  
--              SYSIBMADM.SNAPUTIL and SYSIBMADM.SNAPUTIL_PROGRESS.
--
--         3.   Retrieve the snapshot statistics about the total amount of 
--              space used by all tablespaces in the currently connected 
--              database using the view SYSIBMADM.TBSP_UTILIZATION.
--
-- SQL STATEMENTS USED:
--         CONNECT
--         SELECT
--         TERMINATE
--
-- OUTPUT FILE: monitor.out (available in the online documentation)
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

-- Connect to SAMPLE
CONNECT TO sample;

-- List the top CPU consuming applications for the currently connected 
-- database on the currently connected partition
SELECT s2.APPL_NAME, 
       s2.APPL_ID,
       s1.AGENT_ID,
       s2.PRIMARY_AUTH_ID,
       ((s1.AGENT_USR_CPU_TIME_S + s1.AGENT_SYS_CPU_TIME_S)*1000000 + 
       s1.AGENT_USR_CPU_TIME_MS + s1.AGENT_SYS_CPU_TIME_MS) AS TOTAL_CPU_TIME,
       (s1.AGENT_USR_CPU_TIME_S*1000000 + s1.AGENT_USR_CPU_TIME_MS) AS AGENT_USR_CPU_TIME,
       (s1.AGENT_SYS_CPU_TIME_S*1000000 + s1.AGENT_SYS_CPU_TIME_MS) AS AGENT_SYS_CPU_TIME
   FROM TABLE( SNAP_GET_APPL( '', -1 )) as s1,
        TABLE( SNAP_GET_APPL_INFO( '', -1 )) as s2
   WHERE s1.AGENT_ID = s2.AGENT_ID
   ORDER BY TOTAL_CPU_TIME DESC, s2.APPL_NAME;

-- Retrieving the snapshot statistics about the progress 
-- of all active utilities per partition.
SELECT u1.UTILITY_DBNAME,
       u1.DBPARTITIONNUM,
       u1.UTILITY_ID,
       u1.UTILITY_PRIORITY,
       u1.UTILITY_DESCRIPTION,
       u2.UTILITY_STATE,
       u2.PROGRESS_WORK_METRIC,
       u2.PROGRESS_COMPLETED_UNITS,
       u2.PROGRESS_TOTAL_UNITS,
       DEC( ( FLOAT( u2.PROGRESS_COMPLETED_UNITS ) / FLOAT( u2.PROGRESS_TOTAL_UNITS ) ) * 100, 4, 2 ) 
         AS PERCENT_SEQ_COMPLETE
  FROM SYSIBMADM.SNAPUTIL as u1, SYSIBMADM.SNAPUTIL_PROGRESS as u2
  WHERE u1.UTILITY_ID = u2.UTILITY_ID and u1.DBPARTITIONNUM = u2.DBPARTITIONNUM
  ORDER BY u1.UTILITY_DBNAME, u1.DBPARTITIONNUM, u2.PROGRESS_SEQ_NUM;

-- Retrieving the snapshot statistics about total amount of space
-- used by all tablespaces per partition in the currently connected database.
SELECT SUM( TBSP_TOTAL_SIZE_KB ) AS DBPART_TBSP_TOTAL_SIZE, 
       DBPARTITIONNUM  FROM SYSIBMADM.TBSP_UTILIZATION 
   GROUP BY DBPARTITIONNUM  ORDER BY DBPART_TBSP_TOTAL_SIZE DESC;

-- Connect reset
CONNECT RESET;
