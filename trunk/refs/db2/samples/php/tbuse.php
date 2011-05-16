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
**  SOURCE FILE NAME: tbuse.php
**
**  SAMPLE: How to get information at the table level
**
**  SQL STATEMENTS USED :
**          SELECT
**          INSERT
**          UPDATE
**          DELETE
**
**  OUTPUT FILE: tbuse.out (available in the online documentation)
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

/* check the command line arguments */
CmdLineArgChk($argc, $argv, $dbname, $username, $password);

print("  THIS SAMPLE SHOWS HOW TO CONNECT TO/DISCONNECT ");
print(" FROM A DATABASE\n  AND PERFORM BASIC DATABASE");
print(" OPERATIONS.\n\n");

/* connect to the database with specified username and password */
$dbconn = DbConn($dbname, $username, $password);

/* override the auto commit option */
odbc_autocommit($dbconn,FALSE);

if ($dbconn != 0)
  {
    /* perform a query with the 'org' table */
    BasicQuery($dbconn);
    
    /* insert rows into the 'staff' table */
    BasicInsert($dbconn);

    /* update a set of rows in the 'staff' table */
    BasicUpdate($dbconn);
    
    /* delete a set of rows from the 'staff' table */
    BasicDelete($dbconn);
    
  }

/* disconnect from the database */
DbDisconn($dbconn);

/**************************************************************************
** Description : This function demonstrates how to perform a standard query
** Input       : ODBC  connection id
** Output      : None
****************************************************************************/
function BasicQuery($dbconn)
{
  printf("----------------------------------------------------------\n" .
        " USE THE SQL STATEMENT: \n" .
        "  SELECT\n" .
        "TO QUERY DATA FROM A TABLE.\n");
  printf("\n  Execute Statement:\n" .
        "    SELECT deptnumb, location FROM org WHERE deptnumb < 25\n");

  $statement = "SELECT deptnumb, location FROM org WHERE deptnumb < 25";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn,$statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Select statement Failed   $sqlerror", ERROR);
  }
  else
  {
    /* function defined in util_funcs.php which fetches
     the rows and put it into a array */
    $array = odbc_fetch_resultset($result);
    
    printf("\n  Results:\n ".
                        "    DEPTNUMB LOCATION\n".
                        "    -------- --------------\n");
    for($i=1; odbc_fetch_row($result,$i); $i++)
    {
      printf ( "      %-5s    %-15s \n",
	            $array[$i]["DEPTNUMB"], $array[$i]["LOCATION"]);
    }

  }

} /* BasicQuery */

/**************************************************************************
** Description : This function demonstrates how to insert rows into a table
** Input       : ODBC  connection id
** Output      : None
****************************************************************************/
function BasicInsert($dbconn)
{
  printf(
        "----------------------------------------------------------\n" .
        "USE THE SQL STATEMENT:\n" .
        "  INSERT\n" .
        "TO INSERT DATA INTO A TABLE USING VALUES.\n");

  /* display contents of the 'staff' table before inserting rows */
  StaffTbContentDisplay($dbconn);

  /* use the INSERT statement to insert data into the 'staff' table. */
  printf("\n".
         "  Invoke the statement:\n" .
         "    INSERT INTO staff(id, name, dept, job, salary)\n" .
         "      VALUES(380, 'Pearce', 38, 'Clerk', 13217.50),\n" .
         "            (390, 'Hachey', 38, 'Mgr', 21270.00),\n" .
         "            (400, 'Wagland', 38, 'Clerk', 14575.00)");

  $statement = "INSERT INTO staff(id, name, dept, job, salary) " .
                        "  VALUES (380, 'Pearce', 38, 'Clerk', 13217.50), ".
                        "         (390, 'Hachey', 38, 'Mgr', 21270.00), " .
                        "         (400, 'Wagland', 38, 'Clerk', 14575.00) ";

  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Insert statement Failed   $sqlerror", ERROR);
  }

  /* display the content in the 'staff' table after the INSERT. */
  StaffTbContentDisplay($dbconn);

  /* rollback transaction */
  printf("\n  Rollback the transaction.\n");
  if (!odbc_rollback($dbconn))
  {
    trigger_error("\n Error in rolling back ", WARNING);
  }

} /* BasicInsert */

/**************************************************************************
** Description : This function demonstrates how to update rows in a table
** Input       : ODBC  connection id
** Output      : None
****************************************************************************/
function BasicUpdate($dbconn)
{
  printf("\n".
         "----------------------------------------------------------\n" .
         "USE THE SQL STATEMENT:\n" .
         "  UPDATE\n" .
         "TO UPDATE TABLE DATA USING A SUBQUERY IN THE 'SET' CLAUSE.\n");

  /* display contents of the 'staff' table before updating rows */
  StaffTbContentDisplay($dbconn);

  printf( "\n  UPDATE staff  \n".
          "    SET salary = (SELECT MIN(salary) \n".
          "    FROM staff".
          "    WHERE id >= 310 ");

  /* update the data of table 'staff' by using a subquery in the SET
   clause */
  $statement = "UPDATE staff " .
                        "  SET salary = (SELECT MIN(salary) " .
                        "                  FROM staff " .
                        "                  WHERE id >= 310) " .
                        "  WHERE id = 310";
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Update statement Failed   $sqlerror", ERROR);
  }

  /* display the content in the 'staff' table after the UPDATE. */
  StaffTbContentDisplay($dbconn);

  /* rollback transaction */
  printf("\n  Rollback the transaction.\n");
  if (!odbc_rollback($dbconn))
  {
    trigger_error("\n Error in rolling back ", WARNING);
  }

} /* BasicUpdate*/

/**************************************************************************
** Description : This function demonstrates how to delete rows from a table
** Input       : ODBC  connection id
** Output      : None
****************************************************************************/
function BasicDelete($dbconn)
{
   printf("\n".
        "----------------------------------------------------------\n" .
        "USE THE SQL STATEMENT:\n" .
        "  DELETE\n" .
        "TO DELETE TABLE DATA.\n");

  /* display contents of the 'staff' table before deleting rows*/
  StaffTbContentDisplay($dbconn);

  /* delete rows from the 'staff' table where id >= 310 and
     salary > 20000 */
  
  printf("\n".
        "  Invoke the statement:\n".
        "    DELETE FROM staff WHERE id >= 310 AND salary > 20000\n");

  $statement = "DELETE FROM staff " .
                        "  WHERE id >= 310 " .
                        "  AND salary > 20000";

  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php*/
    trigger_error("  Delete statement Failed   $sqlerror", ERROR);
  }

  /* display the content in the 'staff' table after the DELETE. */
  StaffTbContentDisplay($dbconn);

  /* rollback transaction */
  printf("\n  Rollback the transaction.\n");
  if (!odbc_rollback($dbconn))
  {
      trigger_error("\n Error in rolling back ", WARNING);
  }

} /* BasicDelete */
        
/**************************************************************************
** Description : Display the contents of the table
** Input       : ODBC  connection id
** Output      : prints the result on console
***************************************************************************/
function StaffTbContentDisplay($dbconn)
{
  $statement = "SELECT * FROM staff WHERE id >= 310 " ;

  printf("\n  $statement\n\n");

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn,$statement);

  /* function defined in util_funcs.php which fetches
     the rows and put it into a array*/
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
    for($i=1; odbc_fetch_row($result,$i); $i++)
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
        printf("       -\n");
      }

    }

  }
} /* StaffTbContentDisplay */
?>

