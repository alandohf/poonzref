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
-- SOURCE FILE NAME: iterate.db2
--    
-- SAMPLE: To create the ITERATOR SQL procedure 
--
-- To create the SQL procedure:
-- 1. Connect to the database
-- 2. Enter the command "db2 -td@ -vf iterate.db2"
--
-- To call the SQL procedure from the command line:
-- 1. Connect to the database
-- 2. Enter the following command:
--    db2 "CALL iterator ()" 
--
-- You can also call this SQL procedure by compiling and running the
-- C embedded SQL client application, "iterate", using the iterate.sqc
-- source file available in the sqlproc samples directory.
----------------------------------------------------------------------------
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

CREATE PROCEDURE iterator()
LANGUAGE SQL 
BEGIN 
   DECLARE SQLSTATE CHAR(5);
   DECLARE v_dept CHAR(3);
   DECLARE v_deptname VARCHAR(29);
   DECLARE v_admdept CHAR(3);
   DECLARE at_end INT DEFAULT 0;

   DECLARE not_found CONDITION FOR SQLSTATE '02000';
   DECLARE c1 CURSOR FOR 
     SELECT deptno, deptname, admrdept 
     FROM department
     ORDER BY deptno;
   DECLARE CONTINUE HANDLER FOR not_found
     SET at_end = 1;

   OPEN c1;
   ins_loop:
   LOOP
     FETCH c1 INTO v_dept, v_deptname, v_admdept;
     IF at_end = 1 THEN
       LEAVE ins_loop;
     ELSEIF v_dept = 'D11' THEN
       ITERATE ins_loop;
     END IF;
     INSERT INTO department (deptno, deptname, admrdept)
       VALUES ('NEW', v_deptname, v_admdept);
   END LOOP;
   CLOSE c1;
END @
