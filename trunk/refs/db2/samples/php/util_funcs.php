<?php
/****************************************************************************
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
*****************************************************************************
**
**  SOURCE FILE NAME: util_funcs.php
**
**  SAMPLE: Defines common functions for command line argument checking,
**          connecting to the database,disconnecting from the database,
**          error handling routines,rolling back if an error occurs.
**
*****************************************************************************
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
****************************************************************************/

/**************************************************************************
** Description : This function checks and parses the command line arguments
** Input       : Command line arguments passed to the calling program 
** Output      : None
****************************************************************************/
function CmdLineArgChk($arg_c, &$arg_v, &$dbname, &$username, &$password)
{
  switch ($arg_c)
  {
    /* assume defaults if no command line arguments are given */
    case 1:
      $dbname = "sample";
      $username = "";
      $password = "";
      break;
    
    /* if only the database name is given */
    case 2:
      $dbname = $arg_v[1];
      $username = "";
      $password = "";
      break;
    
    /* if the database name, username and password are given */
    case 4:
      $dbname = $arg_v[1];
      $username = $arg_v[2];
      $password = $arg_v[3];
      break;
    
    /* if the usage is wrong */
    default:
      printf("  USAGE: %s [dbAlias [userid passwd]]\n", $arg_v[0]);
      exit(1);
      break;
  }

} /* CmdLineArgChk */
   
/**************************************************************************
** Description : This function creates a connection to the database
** Input       : Database name,username and password
** Output      : ODBC connection id
****************************************************************************/
function Dbconn($dbname, $username, $password)
{
  print "  Connecting to '$dbname' database...  " ;
  
  /* odbc_connect returns 0 if the connection attempt fails;
     otherwise it returns a connection ID that can be used 
     by other ODBC functions */
  $dbconn = odbc_connect($dbname, $username, $password);

  if ($dbconn == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);
    trigger_error("Error $sqlerror in connecting to the Database ", FATAL);
  }
  else
  {
    print "\n  Connected to '$dbname' database.\n";
  }

  return($dbconn);
} /* Dbconn */
  
/**************************************************************************
** Description : This function fetches the rows and put them into an array
** Input       : ODBC result id
** Output      : Result set in the form of an associative array
****************************************************************************/
function odbc_fetch_resultset($resID)
{

  /* find the number of fields in the result set */  
  $fCount = odbc_num_fields($resID);

  /* the following for loop stores the field names into the array $fNames */
  for($i = 1; $i <= $fCount; $i++)
  {
    $fNames[$i] = odbc_field_name($resID, $i);
  }

  /* create an associative array $resultSet with the key 'fieldNames' 
     pointing to the $fNames array */
 
  $resultSet = array("fieldNames" => $fNames);
 
  /* store all the rows into the $resultSet array */
  for($i = 1; odbc_fetch_row($resID, $i); $i++)
  {
    /* create an array to store each row */ 
    $record = array();

    /* the following for loop creates an associative array $record with the 
       field names as keys that point to the respective field values in each 
       row */ 
    for($j = 1; $j <= $fCount; $j++)
    {
      /* store the field name into the variable $fName */
      $fName = odbc_field_name($resID, $j);

      $record[$fName] = odbc_result($resID, $j);
    }

    /* add each row to the $resultSet array */ 
    $resultSet[$i] = $record;
  }

  return ($resultSet);
} /* odbc_fetch_resultset */

/**************************************************************************
** Description : This function closes the connection to the database
** Input       : ODBC connection id
** Output      : None
****************************************************************************/
function DbDisconn($dbconn)
{
  /* reference the global version of the $dbname variable */
  global $dbname;

  print "\n  Disconnecting from '$dbname' database...";
   
  /* commit all non-committed transactions to release database locks */
  if (!odbc_commit($dbconn)) 
  {
    print "Error on commit\n";
  }
  
  odbc_close($dbconn);
  print "\n  Disconnected from '$dbname' database.\n";

} /* DbDisconn */
  
/**************************************************************************
** Description : This function rolls back all pending statements on a given
**               ODBC connection
** Input       : ODBC connection_id
** Output      : None 
****************************************************************************/
function TransRollback($dbconn)
{
  print "\n  Rolling back the transaction...\n";

  if (!odbc_rollback($dbconn))
  {
    trigger_error("\n Error in rolling back ", WARNING);
  }
  else
  {
    print "\n  The transaction was rolled back.\n";
  }

} /* TransRollback */

/**************************************************************************
** Description : This function defines the user error constants and sets a 
**               user defined error handler function
** Input       : None
** Output      : None
****************************************************************************/
function Error_handler()
{
  define ("FATAL", E_USER_ERROR);
  define ("ERROR", E_USER_WARNING);
  define ("WARNING", E_USER_NOTICE);
  
  /* set to the user defined error handler */
  $old_error_handler = set_error_handler("Error_Handler_function");

} /* Error_handler */

/**************************************************************************
** Description : This function is the user defined error handler that gets 
**               invoked by the trigger_error statement in the main program  
** Input       : error number, error string, error file and errorline
** Output      : None
****************************************************************************/
function Error_Handler_function($errno, $errstr, $errfile, $errline)
{
  switch ($errno)
  {
    case FATAL:
      print "\n  FATAL Error :$errstr \n";
      print "  Aborting...\n";
      odbc_close_all();
      exit(1);
      break;
    case ERROR:
      print "\n  Error : $errstr \n";
      break;
    case WARNING:
      print "\n  Warning : $errstr\n";
      break;
    default:
      break;
  }

} /* Error_Handler_function */
?>
