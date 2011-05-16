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
-- SOURCE FILE NAME: cte.db2
--    
-- SAMPLE: How to create a COMMON TABLE EXPRESSION 
--
-- SQL STATEMENT USED:
--         SELECT
--
-- OUTPUT FILE: cte.out (available in the online documentation)
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

WITH
   PAYLEVEL AS
      (SELECT EMPNO, YEAR(HIREDATE) AS HIREYEAR, EDLEVEL,
              SALARY+BONUS+COMM AS TOTAL_PAY
              FROM EMPLOYEE
                   WHERE EDLEVEL > 16
      ),

   PAYBYED (EDUC_LEVEL, YEAR_OF_HIRE, AVG_TOTAL_PAY) AS
      (SELECT EDLEVEL, HIREYEAR, AVG(TOTAL_PAY)
              FROM PAYLEVEL
              GROUP BY EDLEVEL, HIREYEAR
      )

 SELECT EMPNO, EDLEVEL, YEAR_OF_HIRE, TOTAL_PAY, AVG_TOTAL_PAY
   FROM PAYLEVEL, PAYBYED
    WHERE EDLEVEL=EDUC_LEVEL
          AND HIREYEAR = YEAR_OF_HIRE
          AND TOTAL_PAY < AVG_TOTAL_PAY;

