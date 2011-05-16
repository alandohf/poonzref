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
**  SOURCE FILE NAME: dbuse.php
**
**  SAMPLE: How to use a database 
**
**  SQL STATEMENTS USED:
**         CREATE TABLE
**         DROP TABLE
**         DELETE
**
** OUTPUT FILE: dbuse.out (available in the online documentation)
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

/* call the error handler from util_funcs.php */
Error_handler();

/* check and parse the command line arguments */
CmdLineArgChk($argc, $argv, $dbname, $username, $password);

printf("\nTHIS SAMPLE SHOWS HOW TO USE A DATABASE.\n\n");
 
/* connect to the database with specified username and password */
$dbconn = DbConn($dbname, $username, $password);

/* to override the auto commit */
odbc_autocommit($dbconn, FALSE);

if ($dbconn != 0)
{

  /* use static sql statements */
  StaticStmtInvoke($dbconn);
  
  /* use host variables in sql */
  StaticStmtWithHostVarsInvoke($dbconn);
    
  /* execute sql statements */
  DynamicStmtExecute_Immediate($dbconn);
    
  /* prepare and execute sql statements */
  DynamicStmtExecute($dbconn);
  
  /* use sql statements with host variables dynamically */
  DynamicStmtWithMarkersExecuteusingHostVars($dbconn);
    
}

/* disconnect from the database */
DbDisconn($dbconn);

/**************************************************************************
** Description : This function shows how to use sql statements 
**               'CREATE' and 'DROP' by creating and dropping a table using
**               sql statements
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function StaticStmtInvoke($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  CREATE TABLE\n");
  printf("  DROP TABLE\n");
  printf("TO SHOW HOW TO USE STATIC SQL STATEMENTS.\n");

  /* create a table */
  printf("\n  Execute the statement\n");
  printf("    CREATE TABLE table1(col1 INTEGER)\n");

  $statement = "CREATE TABLE table1(col1 INTEGER)" ;

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler from util_funcs.php */
    trigger_error("  CREATE TABLE  Failed   $sqlerror", ERROR);
  }
  else
  {
    /* commit the transaction */
    printf("  Execute Commit.\n");
    odbc_commit($dbconn);
  }

  /* drop a table */
  printf("\n  Execute the statement\n");
  printf("    DROP TABLE table1\n");
  $stmt = "DROP TABLE table1" ;
  
  /* prepare and execute the SQL statement */
  $result_drop = odbc_exec($dbconn, $stmt);
  if ($result_drop == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler from util_funcs.php */
    trigger_error("  DROP TABLE  Failed   $sqlerror", ERROR);
  }
  else
  {
    /* commit the transaction */
    printf("  Execute Commit.\n");
    odbc_commit($dbconn);
  }
  
} /* StaticStmtInvoke */

/**************************************************************************
** Description : This function shows how to use host variables in a 
**               sql statement
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function StaticStmtWithHostVarsInvoke($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  DELETE\n");
  printf("  ROLLBACK\n");
  printf("TO SHOW HOW TO USE HOST VARIABLES.\n");

  /* execute the statement with host variables */
  printf("\n  Execute\n");
  printf("    DELETE FROM org\n");
  printf("      WHERE deptnumb = :hostVar1 AND\n");
  printf("            division = :hostVar2\n");
  printf("  for\n");
  printf("    hostVar1 = 15\n");
  printf("    hostVar2 = 'Eastern'\n");
  
  $hostVar1 = 15;
  $hostVar2 = "Eastern";
  $statement = "DELETE FROM org ".
                " WHERE deptnumb =  $hostVar1 AND ".
                  " division = '$hostVar2' " ;

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler from util_funcs.php */
    trigger_error("  DELETE  Failed  $sqlerror", ERROR);
  }
  else
  {
    /* rollback the transaction */
    printf("\n  Rollback the transaction.\n");
    odbc_rollback($dbconn);
  }
  
} /* StaticStmtWithHostVarsInvoke */

/**************************************************************************
** Description : This function shows how to execute  sql statements 
**               by odbc_exec, which prepares and executes sql statements. 
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function DynamicStmtExecute_Immediate($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nTO SHOW HOW TO EXECUTE SQL STATEMENTS.\n");

  /* create a table */
  $stmt1  = "CREATE TABLE table1(col1 INTEGER)";
  
  printf("\n  Execute the statement\n");
  printf("    Execute  stmt1\n");
  printf("  for\n");
  printf("    stmt1 = %s\n", $stmt1);

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $stmt1);
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler from util_funcs.php */
    trigger_error("  CREATE TABLE  Failed   $sqlerror", ERROR);
  }
  else
  {
    /* drop a table */
    $stmt2 = "DROP TABLE table1";
    printf("\n  Execute the statement\n");
    printf("    Execute  stmt2\n");
    printf("  for\n");
    printf("    stmt2 = %s\n", $stmt2);
    $result = odbc_exec($dbconn, $stmt2);
    if ($result == 0)
    {
      $sqlerror = odbc_errormsg($dbconn);

      /* call the error handler from util_funcs.php */
      trigger_error("  DROP TABLE  Failed   $sqlerror", ERROR);
    }
    
  }
  
} /* DynamicStmtExecute_Immediate */

/**************************************************************************
** Description : This function shows how to Prepare and Execute sql  
**               statements with odbc_prepare and odbc_execute
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function DynamicStmtExecute($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nTO SHOW HOW TO PREPARE AND EXECUTE SQL STATEMENTS.\n");

  /* prepare the statement */
  $hostVarStmt = "DELETE FROM org WHERE deptnumb = 15";
  
  printf("\n  Execute the statement\n");
  printf("    Prepare Stmt FROM :hostVarStmt\n");
  printf("  for\n");
  printf("    hostVarStmt = %s\n", $hostVarStmt);

  $stmt = odbc_prepare($dbconn, $hostVarStmt);
  if ($stmt == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler on util_funcs.php */
    trigger_error("  Prepare  Failed   $sqlerror", ERROR);
  }
  else
  {
    /* execute the statement */
    printf("\n  Execute the statement\n");
    printf("    Execute Stmt\n");

    $exe_id  = odbc_execute($stmt);
    if ($exe_id == 0)
    {
      $sqlerror = odbc_errormsg($dbconn);

      /* call the error handler on util_funcs.php */
      trigger_error("  Execute  Failed   $sqlerror ", ERROR);
    }
    else
    {
      /* ROLLBACK the transaction */
      printf("\n  Rollback the transaction.\n");
      odbc_rollback($dbconn);
    }
    
  }
  
}/* DynamicStmtExecute */

/**************************************************************************
** Description : This function shows how to Prepare  and Execute  sql 
**               statements with host variables giving dynamic values to it
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function DynamicStmtWithMarkersExecuteusingHostVars($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nTO SHOW HOW TO PREPARE AND EXECUTE STATEMENTS WITH " );
  printf(" HOST VARIABLES.\n");

  /* prepare the statement */
  $hostVarStmt1 = "DELETE FROM org WHERE deptnumb = ? ";
  
  printf("\n  Execute the statement\n");
  printf("    Prepare Stmt1 FROM :hostVarStmt1\n");
  printf("  for\n");
  printf("    hostVarStmt1 = %s\n", $hostVarStmt1);

  $stmt = odbc_prepare($dbconn, $hostVarStmt1);
  if ($stmt == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler on util_funcs.php */
    trigger_error("  Prepare  Failed   $sqlerror", ERROR);
  }
  else
  {
    /* execute the statement for hostVarDeptnumb = 15 */
    $hostvarDeptnumb = array() ;
    $hostvarDeptnumb[1] = 15;

    printf("\n  Execute the statement\n");
    printf("    Execute Stmt1 USING :hostVarDeptnumb\n");
    printf("  for\n");
    printf("    hostVarDeptnumb = %d\n", $hostvarDeptnumb[1]);

    $exe_id  = odbc_execute($stmt, $hostvarDeptnumb);
    if ($exe_id == 0)
    {
      $sqlerror = odbc_errormsg($dbconn);

      /* call the error handler on util_funcs.php */
      trigger_error("  Execute  Failed   $sqlerror", ERROR);
    }
    else
    {

      /* execute the statement for hostVarDeptnumb = 84 */
      $hostvarDeptnumb[1] = 84;

      /* execute the statement */
      printf("\n  Execute the statement\n");
      printf("    Execute Stmt1 USING :hostVarDeptnumb\n");
      printf("  for\n");
      printf("    hostVarDeptnumb = %d\n", $hostvarDeptnumb[1]);

      $exe_id  = odbc_execute($stmt, $hostvarDeptnumb);
      if ($exe_id == 0)
      {
        $sqlerror = odbc_errormsg($dbconn);

        /* call the error handler on util_funcs.php */
        trigger_error("  Execute  Failed   $sqlerror", ERROR);
      }
      
      /* ROLLBACK the transaction */
      printf("\n  Rollback the transaction.\n");
      odbc_rollback($dbconn);
    }
    
  }
  
} /* DynamicStmtWithMarkersExecuteusingHostVars */
?>

