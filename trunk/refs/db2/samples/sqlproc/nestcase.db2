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
-- SOURCE FILE NAME: nestcase.db2
--    
-- SAMPLE: To create the BUMP_SALARY SQL procedure 
--
-- To create the SQL procedure:
-- 1. Connect to the database
-- 2. Enter the command "db2 -td@ -vf nestcase.db2"
--
-- To call the SQL procedure from the command line:
-- 1. Connect to the database
-- 2. Enter the following command:
--    db2 "CALL bump_salary (51)" 
--
-- You can also call this SQL procedure by compiling and running the
-- C embedded SQL client application, "nestcase", using the nestcase.sqc
-- source file available in the sqlproc samples directory.
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

CREATE PROCEDURE bump_salary (IN deptnumber SMALLINT) 
LANGUAGE SQL 
BEGIN 
   DECLARE SQLSTATE CHAR(5);
   DECLARE v_salary DOUBLE;
   DECLARE v_id SMALLINT;
   DECLARE v_years SMALLINT;
   DECLARE at_end INT DEFAULT 0;
   DECLARE not_found CONDITION FOR SQLSTATE '02000';

   DECLARE C1 CURSOR FOR
     SELECT id, CAST(salary AS DOUBLE), years 
     FROM staff 
     WHERE dept = deptnumber;
   DECLARE CONTINUE HANDLER FOR not_found 
     SET at_end = 1;

   OPEN C1;
   FETCH C1 INTO v_id, v_salary, v_years;
   WHILE at_end = 0 DO
     CASE 
       WHEN (v_salary < 2000 * v_years)
         THEN UPDATE staff 
           SET salary = 2150 * v_years 
           WHERE id = v_id;
       WHEN (v_salary < 5000 * v_years)
         THEN CASE 
           WHEN (v_salary < 3000 * v_years) 
             THEN UPDATE staff 
               SET salary = 3000 * v_years 
               WHERE id = v_id;
           ELSE UPDATE staff 
             SET salary = v_salary * 1.10 
             WHERE id = v_id;
         END CASE;
       ELSE UPDATE staff 
         SET job = 'PREZ' 
         WHERE id = v_id;
     END CASE;
     FETCH C1 INTO v_id, v_salary, v_years;
   END WHILE;
   CLOSE C1;
END @
