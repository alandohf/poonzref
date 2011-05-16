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
-- SOURCE FILE NAME: loop.db2
--    
-- SAMPLE: To create the LOOP_UNTIL_SPACE SQL procedure 
--
-- To create the SQL procedure:
-- 1. Connect to the database
-- 2. Enter the command "db2 -td@ -vf loop.db2"
--
-- To call the SQL procedure from the command line:
-- 1. Connect to the database
-- 2. Enter the following command:
--    db2 "CALL loop_until_space (?)" 
--
-- You can also call this SQL procedure by compiling and running the
-- C embedded SQL client application, "loop", using the loop.sqc
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

CREATE PROCEDURE loop_until_space(OUT counter INT)
LANGUAGE SQL
BEGIN
  DECLARE v_firstnme VARCHAR(12);
  DECLARE v_midinit CHAR(1);
  DECLARE v_lastname VARCHAR(15);
  DECLARE v_counter SMALLINT DEFAULT 0;

  DECLARE c1 CURSOR FOR 
    SELECT firstnme, midinit, lastname 
    FROM employee
    ORDER BY midinit DESC;
  DECLARE CONTINUE HANDLER FOR NOT FOUND
    SET counter = -1;

  -- initialize OUT parameter
  SET counter = 0;
  OPEN c1;
  fetch_loop:
  LOOP
    FETCH c1 INTO 
      v_firstnme, v_midinit, v_lastname;
    -- Use a local variable for the iterator variable
    -- because SQL procedures only allow you to assign 
    -- values to an OUT parameter
    SET v_counter = v_counter + 1;
    IF v_midinit = ' ' THEN
      LEAVE fetch_loop;
    END IF;
  END LOOP fetch_loop;
  CLOSE c1;

  -- Now assign the value of the local
  -- variable to the OUT parameter
  SET counter = v_counter;
END @
