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
**  SOURCE FILE NAME: tbpriv.php
**
**  SAMPLE: How to grant, display, and revoke privileges on a table
**
** SQL STATEMENTS USED:
**         GRANT  (Table, View, or Nickname Privileges)
**         SELECT
**         REVOKE (Table, View, or Nickname Privileges)
**
**  OUTPUT FILE: tbpriv.out (available in the online documentation)
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
****************************************************************************/

/* include the common functions */
include_once("util_funcs.php");
  
/* call the error handler in util_funcs.php */
Error_handler();
  
/* check the command line arguments */
CmdLineArgChk($argc, $argv, $dbname, $username, $password);
  
printf("\nTHIS SAMPLE SHOWS HOW TO GRANT/DISPLAY/REVOKE");
printf(" TABLE PRIVILEGES.\n\n");
  
/* connect to the database with specified username and password */
$dbconn = DbConn($dbname, $username, $password);
  
if ($dbconn != 0)
{	
  /* grant privileges to table */
  TbPrivGrant($dbconn);
  
  /* display the privileges */
  TbPrivDisplay($dbconn);

  /* revoke privileges */
  TbPrivRevoke($dbconn);
}

/* disconnect from the database */
DbDisconn($dbconn);
  
/**************************************************************************
** Description : This function shows how to grant privileges at the table
**               level
** Input       : ODBC connection id 
** Output      : None
***************************************************************************/
function TbPrivGrant($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  GRANT (Table, View, or Nickname Privileges)\n");
  printf("TO GRANT PRIVILEGES AT TABLE LEVEL.\n");

  $statement = "GRANT SELECT, INSERT, UPDATE(salary, comm) ".
               "  ON TABLE staff ".
               "  TO USER user1 ";
  
  printf("\n  GRANT SELECT, INSERT, UPDATE(salary, comm)\n");
  printf("      ON TABLE staff\n");
  printf("      TO USER user1\n");

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);
    
    /* call the error handler on util_funcs.php */
    trigger_error("  Grant statement Failed   $sqlerror", ERROR);
  }
  
  /* commit the transaction */
  printf("\n  Commit\n");
  odbc_commit($dbconn);

} /* TbPrivGrant */

/**************************************************************************
** Description : This function shows how to display the privilege 
**               information
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function TbPrivDisplay($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENT:\n");
  printf("  SELECT \n");
  printf("TO DISPLAY PRIVILEGES AT TABLE LEVEL.\n");

  printf("\n  SELECT granteetype, controlauth, alterauth, deleteauth,\n");
  printf("         indexauth, insertauth,");
  printf(" selectauth, refauth, updateauth\n");
  printf("    FROM syscat.tabauth\n");
  printf("    WHERE grantee = 'USER1' AND tabname = 'STAFF'\n");

  $statement = "SELECT granteetype, controlauth, alterauth, ".
               "       deleteauth,indexauth, insertauth, ".
               "       selectauth, refauth, updateauth " .
               "  FROM syscat.tabauth ".
               "  WHERE grantee = 'USER1' AND ".
               "        tabname = 'STAFF' for read only ";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn,$statement);

  /* call the function defined in util_funcs.php which fetches
     the rows and put it into an array */
  $array = odbc_fetch_resultset($result);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Select statement Failed   $sqlerror", ERROR);
  }
  else
  {
    printf("\n  Grantee Type     = %s", $array[1]["GRANTEETYPE"]);
    printf("\n  CONTROL priv.    = %s", $array[1]["CONTROLAUTH"]);
    printf("\n  ALTER priv.      = %s", $array[1]["ALTERAUTH"]);
    printf("\n  DELETE priv.     = %s", $array[1]["DELETEAUTH"]);
    printf("\n  INDEX priv.      = %s", $array[1]["INDEXAUTH"]);
    printf("\n  INSERT priv.     = %s", $array[1]["INSERTAUTH"]);
    printf("\n  SELECT priv.     = %s", $array[1]["SELECTAUTH"]);
    printf("\n  REFERENCES priv. = %s", $array[1]["REFAUTH"]);
    printf("\n  UPDATE priv.     = %s", $array[1]["UPDATEAUTH"]);
    print "\n";
  }

} /* TbPrivDisplay */

/**************************************************************************
** Description : This function shows how to revoke privileges at the table
**               level
** Input       : ODBC connection id  
** Output      : None
***************************************************************************/
function TbPrivRevoke($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  REVOKE (Table, View, or Nickname Privileges)\n");
  printf("TO REVOKE PRIVILEGES AT TABLE LEVEL.\n");

  printf("\n  REVOKE SELECT, INSERT, UPDATE ON TABLE staff FROM USER user1");
  printf("\n");

  $statement = "REVOKE SELECT, INSERT, UPDATE ON TABLE staff ".
               "  FROM USER user1";
  
  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);
	
    /* call the error handler on util_funcs.php */
    trigger_error("  Revoke statement Failed   $sqlerror", ERROR);
  }
  
  /* commit the transaction */
  printf("\n  Commit\n");
  odbc_commit($dbconn);

} /* TbPrivRevoke */
?>
