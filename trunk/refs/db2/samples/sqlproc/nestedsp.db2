----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
-- Governed under the terms of the IBM Public License
--
-- (C) COPYRIGHT International Business Machines Corp. 2002        
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: nestedsp.db2
--    
-- SAMPLE: To create the OUT_AVERAGE, OUT_MEDIAN and MAX_SALARY SQL procedures
--         which are used to calculate the average salary, median salary and 
--         maximum salary of the EMPLOYEE table respectively.
--
-- To create the SQL procedures:
-- 1. Connect to the database
-- 2. Enter the command "db2 -td@ -vf nestedsp.db2"
--
-- To call the SQL procedure from the command line:
-- 1. Connect to the database
-- 2. Enter the following command:
--    db2 "CALL out_average (?,?,?)" 
--
-- To drop the SQL stored procedures created with nestedsp.db2 script:
-- 1. Connect to the database
-- 2. Enter the command "db2 -td@ -vf nestedspdrop.db2"
--
-- You can also call this SQL procedure by compiling and running the
-- Java client application using the NestedSP.java
-- source file available in the sqlproc samples directory.
----------------------------------------------------------------------------

CREATE PROCEDURE MAX_SALARY (OUT maxSalary DOUBLE)
LANGUAGE SQL 
READS SQL DATA

BEGIN
  
  SELECT MAX(salary) INTO maxSalary FROM staff;

END @


CREATE PROCEDURE OUT_MEDIAN (OUT medianSalary DOUBLE, OUT maxSalary DOUBLE)
DYNAMIC RESULT SETS 0
LANGUAGE SQL 
MODIFIES SQL DATA
BEGIN 

  DECLARE v_numRecords INT DEFAULT 1;
  DECLARE v_counter INT DEFAULT 0;
  DECLARE v_mod INT DEFAULT 0;
  DECLARE v_salary1 DOUBLE DEFAULT 0;
  DECLARE v_salary2 DOUBLE DEFAULT 0;
 
  DECLARE c1 CURSOR FOR 
    SELECT CAST(salary AS DOUBLE) FROM staff 
    ORDER BY salary;

  SELECT COUNT(*) INTO v_numRecords FROM staff;

  SET v_mod = MOD(v_numRecords, 2);
  OPEN c1;  

  CASE v_mod
    WHEN 0 THEN
      WHILE v_counter < (v_numRecords / 2 + 1) DO
        SET v_salary1 = v_salary2;
        FETCH c1 INTO v_salary2;
        SET v_counter = v_counter + 1;
      END WHILE;
      SET medianSalary = (v_salary1 + v_salary2)/2;
    WHEN 1 THEN
      WHILE v_counter < (v_numRecords / 2 + 1) DO
        FETCH c1 INTO medianSalary;
        SET v_counter = v_counter + 1;
      END WHILE;
  END CASE;
  
  CLOSE c1;

  CALL MAX_SALARY(maxSalary);

END @


CREATE PROCEDURE OUT_AVERAGE (OUT averageSalary DOUBLE, OUT medianSalary DOUBLE, OUT maxSalary DOUBLE)
DYNAMIC RESULT SETS 2
LANGUAGE SQL 
MODIFIES SQL DATA
BEGIN 

  DECLARE r1 CURSOR WITH RETURN TO CLIENT FOR
    SELECT name, job, CAST(salary AS DOUBLE)
    FROM staff
    WHERE salary > averageSalary
    ORDER BY name ASC;
    
  DECLARE r2 CURSOR WITH RETURN TO CLIENT FOR
    SELECT name, job, CAST(salary AS DOUBLE)
    FROM staff
    WHERE salary < averageSalary
    ORDER BY name ASC; 

  SELECT AVG(salary) INTO averageSalary FROM staff;
  CALL OUT_MEDIAN(medianSalary, maxSalary); 

  -- open the cursors to return result sets
  OPEN r1;

  OPEN r2;

END @

