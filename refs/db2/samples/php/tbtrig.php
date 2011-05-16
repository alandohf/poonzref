<?php
/***************************************************************************
** Licensed Materials - Property of IBM
**
** Governed under the terms of the International
** License Agreement for Non-Warranted Sample Code.
**
** (C) COPYRIGHT International Business Machines Corp. 1996 - 2003
** All Rights Reserved.
**
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
****************************************************************************
**
**  SOURCE FILE NAME: tbtrig.php
**
**  SAMPLE: How to use a trigger on a table
**
**  SQL STATEMENTS USED:
**         SELECT
**         CREATE TABLE
**         DROP
**         CREATE TRIGGER
**         INSERT
**         DELETE
**         UPDATE
**
**  OUTPUT FILE: tbtrig.out (available in the online documentation)
****************************************************************************
**
** For more information on the sample programs, see the README file.
**
** For information on developing PHP applications, see the Application
** Development Guide.
**
** For information on using SQL statements, see the SQL Reference.
**
** For the latest information on programming, building, and running DB2
** applications, visit the DB2 application development website:
**     http://www.software.ibm.com/data/db2/udb/ad
***************************************************************************/

/* include the common functions */
include_once("util_funcs.php");

/* call the error handler in util_funcs.php */
Error_handler();

/* check and parse the command line arguments */
CmdLineArgChk($argc, $argv, $dbname, $username, $password);

printf("\nTHIS SAMPLE SHOWS HOW TO USE TRIGGERS.\n\n");

/* connect to the database with specified username and password */
$dbconn = DbConn($dbname, $username, $password);

/* override the auto commit option */
odbc_autocommit($dbconn, FALSE);

if ($dbconn != 0)
  {
    /* call TbBeforeInsertTriggerUse */
    TbBeforeInsertTriggerUse($dbconn);

    /* call TbAfterInsertTriggerUse */
    TbAfterInsertTriggerUse($dbconn);

    /* call TbBeforeDeleteTriggerUse */
    TbBeforeDeleteTriggerUse($dbconn);

    /* call TbBeforeUpdateTriggerUse */
    TbBeforeUpdateTriggerUse($dbconn);

    /* call TbAfterUpdateTriggerUse */
    TbAfterUpdateTriggerUse($dbconn);
  }
  
/* disconnect from the database */
DbDisconn($dbconn);

/**************************************************************************
** Description : This function is used to display the contents of the table
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function StaffTbContentDisplay($dbconn)
{
  $statement = "SELECT * FROM staff WHERE id <= 50 ";

  printf("\n  $statement\n\n");

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  /* call the function defined in util_funcs.php */
  $array = odbc_fetch_resultset($result);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Select statement Failed   $sqlerror", ERROR);
  }
  else
  {
    printf("    ID  NAME     DEPT JOB   YEARS    SALARY      COMM\n");
    printf("    --- -------- ---- ----- -----   --------    --------\n");
    
    for ($i=1; odbc_fetch_row($result,$i); $i++)
    {
      printf("    %3d %-8.8s %4d", $array[$i]["ID"], $array[$i]["NAME"],
                  $array[$i]["DEPT"]);
             
      if ($array[$i]["JOB"] >= 0)
      {
        printf(" %-5.5s", $array[$i]["JOB"]);
      }
      else
      {
        printf("     -");
      }

      if ($array[$i]["YEARS"] != 0)
      {
        printf(" %5d", $array[$i]["YEARS"]);
      }
      else
      {
        printf("     -");
      }

      printf(" %7.2f", $array[$i]["SALARY"]);
      
      if ($array[$i]["COMM"] > 0)
      {
        printf(" %7.2f\n", $array[$i]["COMM"]);
      }
      else
      {
        printf("          -\n");
      }

    }

  }

} /* StaffTbContentDisplay */

/**************************************************************************
** Description : This function is used to create and insert values into
**               a table
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function StaffStatsTbCreate($dbconn)
{
  printf("\n  CREATE TABLE staff_stats(nbemp SMALLINT)\n");

  $statement = "CREATE TABLE staff_stats(nbemp SMALLINT)";
  
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  CREATE TABLE  Failed   $sqlerror", ERROR);
  }
  else
  {
    printf("\n  INSERT INTO staff_stats VALUES(SELECT COUNT(*)");
    printf(" FROM staff)");
    
    $statement = "INSERT INTO staff_stats VALUES(SELECT COUNT(*) ".
                 "  FROM staff)";
                 
    /* prepare and execute the SQL statement */
    $result = odbc_exec($dbconn, $statement);
    
    if ($result == 0)
    {
      $sqlerror = odbc_errormsg($dbconn);

      /* call the error handler in util_funcs.php */
      trigger_error("  INSERT statement  Failed   $sqlerror",ERROR);
    }

    odbc_commit($dbconn);
  }

} /* StaffStatsTbCreate */

/**************************************************************************
** Description : This function is used to display the contents of the table
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function StaffStatsTbContentDisplay($dbconn)
{
  printf("\n  SELECT nbemp FROM staff_stats\n");
  printf("    NBEMP\n");
  printf("    -----\n");

  $statement = "SELECT * FROM staff_stats";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  /* call the function defined in util_funcs.php */
  $array = odbc_fetch_resultset($result);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Select statement Failed   $sqlerror", ERROR);
  }
  else
  {
    printf("    %5d\n", $array[1]["NBEMP"]);
  }

} /* StaffStatsTbContentDisplay*/

/**************************************************************************
** Description : This function is used to drop staff_stats table
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function StaffStatsTbDrop($dbconn)
{
  printf("\n  DROP TABLE staff_stats\n");
  
  $statement = "DROP TABLE staff_stats";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Drop statement Failed   $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }

} /* StaffStatsTbDrop */

/**************************************************************************
** Description : This function is used to create and insert values
**               into  salary_status table
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function SalaryStatusTbCreate($dbconn)
{
  printf("\n  CREATE TABLE salary_status(emp_name VARCHAR(9),");
  printf("\n                             sal DECIMAL(7, 2),");
  printf("\n                             status CHAR(15))\n");
  
  $statement = "CREATE TABLE salary_status(emp_name VARCHAR(9), ".
               "                           sal DECIMAL(7, 2), ".
               "                           status CHAR(15) ) ";
               
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  CREATE TABLE  Failed   $sqlerror", ERROR);
  }
  else
  {
    printf("\n  INSERT INTO salary_status\n");
    printf("  SELECT name, salary, 'Not Defined'\n");
    printf("  FROM staff\n");
    printf("  WHERE id <= 50\n");

    $statement = " INSERT INTO salary_status ".
                 "   SELECT name, salary, 'Not Defined' ".
                 "     FROM staff ".
                 "     WHERE id <= 50 ";

    /* prepare and execute the SQL statement */
    $result = odbc_exec($dbconn, $statement);

    if ($result == 0)
    {
      $sqlerror = odbc_errormsg($dbconn);

      /* call the error handler in util_funcs.php */
      trigger_error("  INSERT statement  Failed   $sqlerror", ERROR);
    }

    odbc_commit($dbconn);
  }

} /* SalaryStatusTbCreate*/

/**************************************************************************
** Description : This function is used to display the contents of the
**               salary_status table
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function SalaryStatusTbContentDisplay($dbconn)
{
  printf("\n  Select * from salary_status\n");
  printf("    EMP_NAME     SALARY   STATUS          \n");
  printf("    ----------   -------- ----------------\n");

  $statement = "SELECT * FROM salary_status";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Select statement Failed   $sqlerror", FATAL);
  }
  else
  {
    /* call the function defined in util_funcs.php */
    $array = odbc_fetch_resultset($result);

    for ($i = 1; odbc_fetch_row($result, $i); $i++)
    {
      printf("    %-10s %7.2f %-15s\n", $array[$i]["EMP_NAME"],
              $array[$i]["SAL"], $array[$i]["STATUS"]);
      
    }

  }

} /* SalaryStatusTbContentDisplay */

/**************************************************************************
** Description : This function is used to drop the salary_status table
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function SalaryStatusTbDrop($dbconn)
{
  printf("\n  DROP TABLE salary_status\n");

  $statement = " DROP TABLE salary_status";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  DROP Table Failed  $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }

} /* SalaryStatusTbDrop */

/**************************************************************************
** Description : This function shows how to create salary_history table
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function SalaryHistoryTbCreate($dbconn)
{
  printf("\n  CREATE TABLE salary_history(employee_name VARCHAR(9),");
  printf("\n                              salary_record DECIMAL(7, 2),");
  printf("\n                              change_date DATE)\n");
  
  $statement = "CREATE TABLE salary_history(employee_name VARCHAR(9), ".
               "                            salary_record DECIMAL(7, 2), ".
               "                            change_date DATE)";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  CREATE TABLE  Failed   $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }

} /* SalaryHistoryTbCreate*/

/**************************************************************************
** Description : This function is used to display the contents of the
**               salary_history table
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function SalaryHistoryTbContentDisplay($dbconn)
{
  printf("\n  Select * from salary_history\n");
  printf("    EMPLOYEE_NAME    SALARY_RECORD    CHANGE_DATE\n");
  printf("    --------------   --------------   -----------\n");

  $statement = "SELECT * FROM salary_history";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Select statement Failed   $sqlerror", FATAL);
  }
  else
  {
    /* call the function defined in util_funcs.php */
    $array = odbc_fetch_resultset($result);

    for ($i=1; odbc_fetch_row($result, $i); $i++)
    {
      printf("    %-14s%14.2f   %-15s\n", $array[$i]["EMPLOYEE_NAME"],
              $array[$i]["SALARY_RECORD"], $array[$i]["CHANGE_DATE"]);
    }
    
  }

} /* SalaryHistoryTbContentDisplay*/

/**************************************************************************
** Description : This function is used to drop the salary_history table
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function SalaryHistoryTbDrop($dbconn)
{
  printf("\n  DROP TABLE salary_history\n");

  $statement = " DROP TABLE salary_history";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler n util_funcs.php */
    trigger_error("  DROP Table Failed  $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }

} /* SalaryHistoryTbDrop */

/**************************************************************************
** Description : This function shows how to use a 'BEFORE INSERT' trigger 
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function TbBeforeInsertTriggerUse($dbconn)
{

  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  CREATE TRIGGER\n");
  printf("  INSERT\n");
  printf("  DROP TRIGGER\n");
  printf("TO SHOW A 'BEFORE INSERT' TRIGGER.\n");

  /* display the initual content of the table */
  StaffTbContentDisplay($dbconn);

  printf("\n  CREATE TRIGGER min_salary".
         "\n    NO CASCADE BEFORE".
         "\n    INSERT ON staff".
         "\n    REFERENCING NEW AS newstaff".
         "\n    FOR EACH ROW".
         "\n    BEGIN ATOMIC".
         "\n      SET newstaff.salary =".
         "\n        CASE".
         "\n          WHEN newstaff.job = 'Mgr' AND ".
                          "newstaff.salary < 17000.00".
         "\n            THEN 17000.00".
         "\n          WHEN newstaff.job = 'Sales' AND ".
                          "newstaff.salary < 14000.00".
         "\n            THEN 14000.00".
         "\n          WHEN newstaff.job = 'Clerk' AND ".
                          "newstaff.salary < 10000.00".
         "\n            THEN 10000.00".
         "\n          ELSE newstaff.salary".
         "\n        END;".
         "\n    END\n");


  $statement = "CREATE TRIGGER min_salary ".
               "  NO CASCADE BEFORE ".
               "  INSERT ON staff ".
               "  REFERENCING NEW AS newstaff ".
               "  FOR EACH ROW ".
               "  BEGIN ATOMIC ".
               "    SET newstaff.salary = ".
               "      CASE " .
               "        WHEN newstaff.job = 'Mgr' AND ".
               "             newstaff.salary < 17000.00 ".
               "          THEN 17000.00 ".
               "        WHEN newstaff.job = 'Sales' AND ".
               "             newstaff.salary < 14000.00 ".
               "          THEN 14000.00 ".
               "        WHEN newstaff.job = 'Clerk' AND ".
               "             newstaff.salary < 10000.00 ".
               "          THEN 10000.00 ".
               "        ELSE newstaff.salary " .
               "      END; ".
               "  END";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Trigger execute Failed   $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }
  
  /* insert into the table using values */
  printf("\n  Invoke the statement\n");
  printf("    INSERT INTO staff(id, name, dept, job, salary)\n");
  printf("      VALUES(25, 'Pearce', 38, 'Clerk', 7217.50),\n");
  printf("            (35, 'Hachey', 38, 'Mgr', 21270.00),\n");
  printf("            (45, 'Wagland', 38, 'Sales', 11575.00)\n");

  $statement = "INSERT INTO staff(id, name, dept, job, salary) ".
               "  VALUES(25, 'Pearce', 38, 'Clerk', 7217.50), ".
               "        (35, 'Hachey', 38, 'Mgr', 21270.00), ".
               "        (45, 'Wagland', 38, 'Sales', 11575.00) ";
                      
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Insert statement Failed   $sqlerror", ERROR);
  }

  /* display final content of the table */
  StaffTbContentDisplay($dbconn);

  /* rollback transaction */
  printf("\n  Rollback the transaction.\n");

  if (!odbc_rollback($dbconn))
  {
    trigger_error("\n Error in rolling back ", WARNING);
  }
  
  printf("\n  DROP TRIGGER min_salary\n");
  
  $statement = "DROP TRIGGER min_salary";
  
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Drop statement Failed   $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }

} /* TbBeforeInsertTriggerUse */

/**************************************************************************
** Description : This function shows how to use an 'AFTER INSERT' trigger
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function TbAfterInsertTriggerUse($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  CREATE TRIGGER\n");
  printf("  COMMIT\n");
  printf("  INSERT\n");
  printf("  DROP TRIGGER\n");
  printf("TO SHOW AN 'AFTER INSERT' TRIGGER.\n");

  /* create salary_status table */
  StaffStatsTbCreate($dbconn);

  /* display staff_stats table content */
  StaffStatsTbContentDisplay($dbconn);

  printf("\n  CREATE TRIGGER new_hire AFTER".
         "\n    INSERT ON staff".
         "\n    FOR EACH ROW".
         "\n    BEGIN ATOMIC".
         "\n      UPDATE staff_stats SET nbemp = nbemp + 1;".
         "\n    END\n");
  $statement = "CREATE TRIGGER new_hire AFTER ".
               "  INSERT ON staff ".
               "  FOR EACH ROW ".
               "  BEGIN ATOMIC ".
               "    UPDATE staff_stats SET nbemp = nbemp + 1; ".
               "  END";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler on util_funcs.php */
    trigger_error("  Trigger execute Failed   $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }

  /* insert into the table using values */
  printf("\n  Invoke the statement\n");
  printf("    INSERT INTO staff(id, name, dept, job, salary)\n");
  printf("      VALUES(25, 'Pearce', 38, 'Clerk', 7217.50),\n");
  printf("            (35, 'Hachey', 38, 'Mgr', 21270.00),\n");
  printf("            (45, 'Wagland', 38, 'Sales', 11575.00)\n");
  
  $statement = "INSERT INTO staff(id, name, dept, job, salary) ".
               "     VALUES(25, 'Pearce', 38, 'Clerk', 7217.50), ".
               "           (35, 'Hachey', 38, 'Mgr', 21270.00), ".
               "           (45, 'Wagland', 38, 'Sales', 11575.00)";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Insert statement Failed   $sqlerror", ERROR);
  }

  /* display staff_stats table content */
  StaffStatsTbContentDisplay($dbconn);

  /* rollback transaction */
  printf("\n  Rollback the transaction.\n");
  
  if (!odbc_rollback($dbconn))
  {
    trigger_error("\n Error in rolling back ",WARNING);
  }

  printf("\n  DROP TRIGGER new_hire\n");
  $statement = "DROP TRIGGER new_hire";
  
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Drop statement Failed   $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }

  /* drop staff_stats table */
  StaffStatsTbDrop($dbconn);
  
} /* TbAfterInsertTriggerUse */

/**************************************************************************
** Description : This function shows how to use a 'BEFORE DELETE' trigger
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function TbBeforeDeleteTriggerUse($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  CREATE TRIGGER\n");
  printf("  COMMIT\n");
  printf("  DELETE\n");
  printf("  DROP TRIGGER\n");
  printf("TO SHOW A 'BEFORE DELETE' TRIGGER.\n");

  /* display initial content of the table */
  StaffTbContentDisplay($dbconn);

  printf("\n  CREATE TRIGGER do_not_del_sales ".
         "\n    NO CASCADE BEFORE ".
         "\n    DELETE ON staff".
         "\n    REFERENCING OLD AS oldstaff".
         "\n    FOR EACH ROW".
         "\n    WHEN(oldstaff.job = 'Sales')".
         "\n    BEGIN ATOMIC".
         "\n      SIGNAL SQLSTATE '75000' ".
         "('Sales can not be deleted now.');".
         "\n    END\n");

  $statement = "CREATE TRIGGER do_not_del_sales ".
               "  NO CASCADE BEFORE ".
               "  DELETE ON staff ".
               "  REFERENCING OLD AS oldstaff ".
               "  FOR EACH ROW ".
               "  WHEN(oldstaff.job = 'Sales') ".
               "  BEGIN ATOMIC ".
               "    SIGNAL SQLSTATE '75000' ".
	       "    ('Sales can not be deleted now.');".
               "  END";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Trigger execute Failed   $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }
  
  /* delete table */
  printf("\n  Invoke the statement\n");
  printf("    DELETE FROM staff WHERE id <= 50\n");
  
  $statement = "DELETE FROM staff WHERE id <= 50";
  
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);
    $errorstate = odbc_error($dbconn);
    printf ( "\n  SQL0438N Sales can not be deleted now. SQLSTATE = %s\n",
                    $errorstate);
                    
  }

  /* display final content of the table */
  StaffTbContentDisplay($dbconn);

  /* rollback transaction */
  printf("\n  Rollback the transaction.\n");
  
  if (!odbc_rollback($dbconn))
  {
      trigger_error("\n Error in rolling back ", WARNING);
  }

  printf("\n  DROP TRIGGER do_not_del_sales\n");
  
  $statement = "DROP TRIGGER do_not_del_sales";
  
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Trigger execution failed $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }
  
} /* TbBeforeDeleteTriggerUse */

/**************************************************************************
** Description : This function shows how to use a 'BEFORE UPDATE' trigger 
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function TbBeforeUpdateTriggerUse($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  CREATE TRIGGER\n");
  printf("  COMMIT\n");
  printf("  UPDATE\n");
  printf("  DROP TRIGGER\n");
  printf("TO SHOW A 'BEFORE UPDATE' TRIGGER.\n");

  /* create salary_status table */
  SalaryStatusTbCreate($dbconn);

  /* display salary_status table content */
  SalaryStatusTbContentDisplay($dbconn);

  printf("\n  CREATE TRIGGER salary_status ".
         "\n    NO CASCADE BEFORE".
         "\n    UPDATE OF sal".
         "\n    ON salary_status".
         "\n    REFERENCING NEW AS new OLD AS old".
         "\n    FOR EACH ROW".
         "\n    BEGIN ATOMIC".
         "\n      SET new.status =".
         "\n        CASE".
         "\n          WHEN new.sal < old.sal THEN 'Decreasing' ".
         "\n          WHEN new.sal > old.sal THEN 'Increasing' ".
         "\n        END;".
	     "\n    END\n" );
  $statement =  "CREATE TRIGGER sal_status ".
                "  NO CASCADE BEFORE ".
                "  UPDATE OF sal ".
                "  ON salary_status ".
                "  REFERENCING NEW AS new OLD AS old ".
                "  FOR EACH ROW ".
                "  BEGIN ATOMIC ".
                "    SET new.status = ".
                "      CASE ".
                "        WHEN new.sal < old.sal THEN 'Decreasing' ".
                "        WHEN new.sal > old.sal THEN 'Increasing' ".
                "      END;".
                "  END ";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Trigger execute Failed   $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }

  /* update table */
  printf("\n  Invoke the statement\n");
  printf("    UPDATE salary_status SET sal = 18000.00\n");

  $statement = "UPDATE salary_status SET sal = 18000.00";
  
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  UPDATE statement Failed   $sqlerror", ERROR);
  }

  /* display final content of the table */
  SalaryStatusTbContentDisplay($dbconn);

  /* rollback transaction */
  printf("\n  Rollback the transaction.\n");

  if (!odbc_rollback($dbconn))
  {
      trigger_error("\n Error in rolling back ", WARNING);
  }

  $statement = "  DROP TRIGGER sal_status";
  printf("\n%s\n", $statement);

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  DROP Trigger Failed   $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }
  
  /* drop salary_status table */
  SalaryStatusTbDrop($dbconn);
  
} /* TbBeforeUpdateTriggerUse */

/**************************************************************************
** Description : This function shows how to use an 'AFTER UPDATE' trigger 
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function TbAfterUpdateTriggerUse($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  CREATE TRIGGER\n");
  printf("  COMMIT\n");
  printf("  UPDATE\n");
  printf("  DROP TRIGGER\n");
  printf("TO SHOW AN 'AFTER UPDATE' TRIGGER.\n");

  /* create salary_history table */
  SalaryHistoryTbCreate($dbconn);
  
  /* display salary_history table content */
  SalaryHistoryTbContentDisplay($dbconn);
  
  printf("\n  CREATE TRIGGER sal_history".
         "\n    AFTER".
         "\n    UPDATE OF salary ON staff".
         "\n    REFERENCING NEW AS newstaff".
         "\n    FOR EACH ROW".
         "\n    BEGIN ATOMIC".
         "\n      INSERT INTO salary_history".
         "\n        VALUES(newstaff.name, newstaff.salary, CURRENT DATE);".
         "\n    END\n");

  $statement = "  CREATE TRIGGER sal_history ".
               "    AFTER ".
               "    UPDATE OF salary ON staff ".
               "    REFERENCING NEW AS newstaff ".
               "    FOR EACH ROW ".
               "    BEGIN ATOMIC ".
               "      INSERT INTO salary_history ".
               "        VALUES(newstaff.name, ".
               "               newstaff.salary, CURRENT DATE);".
               "    END ";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Trigger execute Failed   $sqlerror",ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }

  /* update table */
  printf("\n  Invoke the statement\n");
  printf("    UPDATE staff SET salary = 20000.00 WHERE name = 'Sanders'\n");
  
  $statement = " UPDATE staff SET salary = 20000.00 ".
               "   WHERE name = 'Sanders' ";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  UPDATE statement Failed   $sqlerror", ERROR);
  }
  printf("\n  Invoke the statement\n");
  printf("    UPDATE staff SET salary = 21000.00 WHERE name = 'Sanders'\n");

  $statement = " UPDATE staff SET salary = 21000.00 ".
               "   WHERE name = 'Sanders' ";
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  UPDATE statement Failed   $sqlerror", ERROR);
  }

  printf("\n  Invoke the statement\n");
  printf("    UPDATE staff SET salary = 23000.00 WHERE name = 'Sanders'\n");

  $statement = " UPDATE staff SET salary = 23000.00 ".
               "   WHERE name = 'Sanders' ";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  UPDATE statement Failed   $sqlerror", ERROR);
  }

  printf("\n  Invoke the statement\n");
  printf("    UPDATE staff SET salary = 20000.00 WHERE name = 'Hanes'\n");
  
  $statement = " UPDATE staff SET salary = 20000.00 ".
               "   WHERE name = 'Hanes' ";
               
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  UPDATE statement Failed   $sqlerror", ERROR);
  }

  printf("\n  Invoke the statement\n");
  printf("    UPDATE staff SET salary = 21000.00 WHERE name = 'Hanes'\n");
  
  $statement = " UPDATE staff SET salary = 21000.00 ".
               "   WHERE name = 'Hanes' ";
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  UPDATE statement Failed   $sqlerror", ERROR);
  }

  /* display salary_history table content */
  SalaryHistoryTbContentDisplay($dbconn);

  /* rollback transaction */
  printf("\n  Rollback the transaction.\n");
  
  if (!odbc_rollback($dbconn))
  {
    /* call the error handler in util_funcs.php */
	trigger_error("\n Error in rolling back ", WARNING);
  }

  $statement = "  DROP TRIGGER sal_history";
  
  printf("\n%s\n", $statement);

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  DROP Trigger Failed   $sqlerror", ERROR);
  }
  else
  {
    odbc_commit($dbconn);
  }
  
  /* drop salary_history table */
  SalaryHistoryTbDrop($dbconn);

} /* TbAfterUpdateTriggerUse */

?>
