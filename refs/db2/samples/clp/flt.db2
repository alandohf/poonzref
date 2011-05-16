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
-- SOURCE FILE NAME: flt.db2
--    
-- SAMPLE: How to do a RECURSIVE QUERY 
--
-- SQL STATEMENTS USED:
--         DROP TABLE
--         CREATE TABLE
--         INSERT
--         SELECT
--
-- OUTPUT FILE: flt.out (available in the online documentation)
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

create table flights (source varchar (8), 
                      destination varchar (8),
                      d_time integer, 
                      a_time integer, 
                      cost smallint,
                      airline varchar (8));

INSERT INTO FLIGHTS VALUES ('Paris',   'Detroit',  null,null,700,'KLM'),
                           ('Paris',   'New York', null,null,600,'KLM'),
                           ('Paris',   'Toronto',   null,null,750,'AC'), 
                           ('Detroit', 'San Jose', null,null,400,'AA'),     
                           ('New York','Chicago',  null,null,200,'AA'),     
                           ('Toronto',  'Chicago',  null,null,275,'AC'),      
                           ('Chicago', 'San Jose', null,null,300,'AA');

WITH 
 REACH (SOURCE, DESTINATION, COST, STOPS) AS
   ( SELECT SOURCE, DESTINATION, COST, CAST(0 AS SMALLINT)
      FROM FLIGHTS
       WHERE SOURCE = 'Paris'
    UNION ALL
     SELECT R.SOURCE, F.DESTINATION, CAST(R.COST+F.COST AS SMALLINT), CAST(R.STOPS+1 AS SMALLINT)
     FROM REACH R, FLIGHTS F
      WHERE R.DESTINATION=F.SOURCE
        AND R.STOPS < 5
   )
SELECT DESTINATION, COST, STOPS FROM REACH;

drop table flights;

