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
**  SOURCE FILE NAME: tbinfo.php
**
**  SAMPLE: How to get information at the table level
**
**  SQL STATEMENTS USED :
**          SELECT
**
**  OUTPUT FILE: tbinfo.out (available in the online documentation)
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
  
printf("\nTHIS SAMPLE SHOWS HOW TO GET INFORMATION AT THE TABLE LEVEL\n\n");
  
/* connect to the database with specified username and password */
$dbconn = DbConn($dbname, $username, $password);
  
if ($dbconn != 0)
{
  /* call the function TbSchemaNameGet */
  $tab_schema = TbSchemaNameGet($dbconn);
  
  /* call the function TbColumnInfoGet */
  TbColumnInfoGet($dbconn, $tab_schema);
}

/* disconnect from the database */
DbDisconn($dbconn);
  
/**************************************************************************
** Description : This function shows how to get the schema name for a table
** Input       : ODBC connection id
** Output      : Returns the table schema name
***************************************************************************/
function TbSchemaNameGet($dbconn)
{
  printf("\n---------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENT:\n");
  printf("  SELECT \n");
  printf("TO GET A TABLE SCHEMA NAME.\n");

  /* the select statement to be executed */
  $statement = "SELECT tabschema ".
               "  FROM syscat.tables ".
               "  WHERE tabname = 'STAFF' for read only";
  
  printf(" \n  Execute sql statement:\n  ");
  printf("   SELECT tabschema\n");
  printf("      FROM syscat.tables \n");
  printf("      WHERE tabname = 'STAFF' for read only\n\n");
  
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);
    
    /* call the error handler on util_funcs.php */
    trigger_error("  Select statement Failed   $sqlerror", FATAL);
  }
  else
  {
    print "  Table schema name is: " ;
    print odbc_result($result, 1);
    print "\n";
    return (odbc_result($result, 1));
  }

} /* TbSchemaNameGet */
  
/**************************************************************************
** Description : This function shows how to get information about the 
**               columns in a table
** Input       : ODBC connection id and table schema name
** Output      : None 
***************************************************************************/
function TbColumnInfoGet($dbconn, $tab_schema)
{
  printf("\n---------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  SELECT \n");
  printf("TO GET TABLE COLUMN INFO.\n");

  /* the select statement to be executed */
  $statement =    "SELECT colname, typename, length, scale ".
                  "  FROM syscat.columns ".
                  "  WHERE tabschema = '$tab_schema' ".
                  "  AND tabname = 'STAFF' for read only ";

  /* remove the spaces from tab_schema */
  $tab_schema = strtok($tab_schema," ");

  printf("\n  Execute sql statement:\n");
  printf("     SELECT colname, typename, length, scale \n");
  printf("       FROM syscat.columns \n");
  printf("       WHERE tabname = 'STAFF' AND tabschema = '$tab_schema'");
  printf(" for readonly\n\n");

  printf("  Get info for '$tab_schema.STAFF' table columns\n");

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  /* function defined in util_funcs.php which fetches
     the rows and put it into a array */
  $array = odbc_fetch_resultset($result);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Select statement Failed $sqlerror", ERROR);
  }
  else
  {
    printf("\n   column name          data type      data size\n");
    printf("   -------------------- -------------- ----------\n");

    for($i=1; odbc_fetch_row($result, $i); $i++)
    {
      printf("   %-20.20s %-14.14s %d",
  	            $array[$i]["COLNAME"], $array[$i]["TYPENAME"],
	            $array[$i]["LENGTH"]);
	  if ( $array[$i]["SCALE"] != 0)
      {
        printf(",%d\n", $array[$i]["SCALE"]);
      }
      else
      {
        printf("\n");
      }

    }
    
  }
  
} /* TbColumnInfoGet */
?>
