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
-- SOURCE FILE NAME: join.db2
--    
-- SAMPLE: How to OUTER JOIN tables 
--
-- SQL STATEMENT USED:
--         SELECT 
--
-- OUTPUT FILE: join.out (available in the online documentation)
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
 DEPT_MGR AS
  ( SELECT DEPTNO, DEPTNAME, EMPNO, LASTNAME, FIRSTNME, PHONENO
     FROM DEPARTMENT D, EMPLOYEE E
      WHERE D.MGRNO=E.EMPNO AND E.JOB='MANAGER'
  ),

 DEPT_NO_MGR AS
  ( SELECT DEPTNO, DEPTNAME, MGRNO AS EMPNO
      FROM DEPARTMENT
   EXCEPT ALL
    SELECT DEPTNO, DEPTNAME, EMPNO
      FROM DEPT_MGR
  ),

 MGR_NO_DEPT (DEPTNO, EMPNO, LASTNAME, FIRSTNME, PHONENO) AS
  ( SELECT WORKDEPT, EMPNO, LASTNAME, FIRSTNME, PHONENO
      FROM EMPLOYEE
       WHERE JOB='MANAGER'
   EXCEPT ALL
    SELECT DEPTNO,EMPNO, LASTNAME, FIRSTNME, PHONENO
      FROM DEPT_MGR
  )

SELECT DEPTNO, DEPTNAME, EMPNO, LASTNAME, FIRSTNME, PHONENO 
  FROM DEPT_MGR
UNION ALL
SELECT DEPTNO, DEPTNAME, EMPNO,
       CAST(NULL AS VARCHAR(15)) AS LASTNAME,
       CAST(NULL AS VARCHAR(12)) AS FIRSTNME,
       CAST(NULL AS CHAR(4)) AS PHONENO
  FROM DEPT_NO_MGR
UNION ALL
SELECT DEPTNO,
       CAST(NULL AS VARCHAR(29)) AS DEPTNAME,
       EMPNO, LASTNAME, FIRSTNME, PHONENO
  FROM MGR_NO_DEPT
ORDER BY 4;

