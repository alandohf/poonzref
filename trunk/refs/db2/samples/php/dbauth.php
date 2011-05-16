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
**  SOURCE FILE NAME: dbauth.php
**
**  SAMPLE: How to grant, display, and revoke authorities at database level
**
**  SQL Statements USED :
**         GRANT (Database Authorities)
**         SELECT
**         REVOKE (Database Authorities)
**
**  OUTPUT FILE: dbauth.out (available in the online documentation)
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

/* call error handler from util_funcs.php */
Error_handler();

/* check and parse the command line arguments */
CmdLineArgChk($argc, $argv, $dbname, $username, $password);

print("\nTHIS SAMPLE SHOWS ");
Print("HOW TO GRANT/DISPLAY/REVOKE AUTHORITIES AT DATABASE LEVEL.\n\n");

/* connect to the database with specified username and password */
$dbconn = DbConn($dbname, $username, $password);

/* reset the autocommit option as autocommit is set by default */
odbc_autocommit($dbconn, FALSE);

/* connection to database is successful */ 
if ($dbconn != 0)
{
  /* call the function DbAuthGrant */
  DbAuthGrant($dbconn);
  
  /* call the function DbAuthForAnyUserOrGroupDisplay */
  DbAuthForAnyUserOrGroupDisplay($dbconn);

  /* call the function DbAuthForCurrentUserDisplay */
  DbAuthForCurrentUserDisplay($dbconn);

   /* call the function DbAuthRevoke */
  DbAuthRevoke($dbconn);
}

/* disconnect from the database */
DbDisconn($dbconn);

/**************************************************************************
** Description : This function shows how to grant user authorities at 
**               database level
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function DbAuthGrant($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  GRANT (Database Authorities)\n");
  printf("  COMMIT\n");
  printf("TO GRANT AUTHORITIES AT DATABASE LEVEL.\n");

  /* grant user authorities at database level */
  printf("\n  GRANT CONNECT, CREATETAB, BINDADD ON DATABASE");
  printf(" TO USER user1\n");

  $statement = "GRANT CONNECT, CREATETAB, BINDADD ON DATABASE ".
               "TO USER user1";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Grant statement Failed   $sqlerror", ERROR);
  }
  else
  {
    printf("  COMMIT\n");
    odbc_commit($dbconn);
  }
  
} /* DbAuthGrant */

/**************************************************************************
** Description : This function shows how to display authorities for 
**               any user at database level
** Input       : ODBC connection id 
** Output      : None
***************************************************************************/
function DbAuthForAnyUserOrGroupDisplay($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENT:\n");
  printf("  SELECT INTO\n");
  printf("TO DISPLAY AUTHORITIES FOR ANY USER AT DATABASE LEVEL.\n");

  printf("\n  SELECT granteetype, dbadmauth, createtabauth, bindaddauth,");
  printf("\n         connectauth, nofenceauth, implschemaauth, loadauth ");
  printf("\n    FROM syscat.dbauth ");
  printf("\n    WHERE grantee = 'USER1'\n");

  $statement =
         "  SELECT granteetype, dbadmauth, createtabauth, bindaddauth, ".
         "         connectauth, nofenceauth, implschemaauth, loadauth ".
         "    FROM syscat.dbauth ".
         "    WHERE grantee = 'USER1' for read only";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler in util_funcs.php */
    trigger_error("  Select statement Failed   $sqlerror", ERROR);
  }
  else
  {
    /* call function from util_funcs.php which fetches
       the rows and put it into an array */
    $array = odbc_fetch_resultset($result);

    printf("\n  Grantee Type      = %s\n", $array[1]["GRANTEETYPE"]);
    printf("  DBADM auth.       = %s\n", $array[1]["DBADMAUTH"]);
    printf("  CREATETAB auth.   = %s\n", $array[1]["CREATETABAUTH"]);
    printf("  BINDADD auth.     = %s\n", $array[1]["BINDADDAUTH"]);
    printf("  CONNECT auth.     = %s\n", $array[1]["CONNECTAUTH"]);
    printf("  NO_FENCE auth.    = %s\n", $array[1]["NOFENCEAUTH"]);
    printf("  IMPL_SCHEMA auth. = %s\n", $array[1]["IMPLSCHEMAAUTH"]);
    printf("  LOAD auth.        = %s\n", $array[1]["LOADAUTH"]);
  }
  
} /* DbAuthForAnyUserOrGroupDisplay */

/**************************************************************************
** Description : This is a support function for changing Y to YES 
**               and N to NO
** Input       : Y/N
** Output      : YES/NO
***************************************************************************/
function displayfull($alpha)
{
  $output = "NO";
  if ($alpha == "Y")
  {
	$output = "YES";
	return($output);
  }
  
  return ($output);
} /* displayfull */

/**************************************************************************
** Description : This function shows how to display authorities for 
**               current user at database level
** Input       : ODBC connection id 
** Output      : None
***************************************************************************/
function DbAuthForCurrentUserDisplay($dbconn)
{
  printf("\n-----------------------------------------------------------\n");
  printf("TO DISPLAY CURRENT USER AUTHORITIES AT DATABASE LEVEL \n");
  $getuser = "SELECT user FROM sysibm.sysdummy1" ;

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $getuser);
  $user = odbc_result($result, 1);

  /* current user authorities */
  $statement =
         "  SELECT  dbadmauth, createtabauth, bindaddauth, ".
         "         connectauth, nofenceauth, implschemaauth, loadauth ".
         "    FROM syscat.dbauth ".
         "    WHERE grantee = '$user' for read only";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler on util_funcs.php */
    trigger_error("  Select statement Failed   $sqlerror", ERROR);
  }
  else
  {
    /* call function from util_funcs.php which fetches
       the rows and put it into an array */
    $array = odbc_fetch_resultset($result);

    printf("\n  User DBADM authority            : %s\n",
              displayfull($array[1]["DBADMAUTH"]));
    printf("  User CREATETAB authority        : %s\n",
              displayfull($array[1]["CREATETABAUTH"]));
    printf("  User BINDADD authority          : %s\n",
              displayfull($array[1]["BINDADDAUTH"]));
    printf("  User CONNECT authority          : %s\n",
             displayfull($array[1]["CONNECTAUTH"]));
    printf("  User CREATE_NOT_FENC authority  : %s\n",
             displayfull($array[1]["NOFENCEAUTH"]));
    printf("  User IMPLICIT_SCHEMA authority  : %s\n",
              displayfull($array[1]["IMPLSCHEMAAUTH"]));
    printf("  User LOAD authority             : %s\n",
              displayfull($array[1]["LOADAUTH"]));
  }

  /* current group authorities */
  $statement =
         "  SELECT  dbadmauth, createtabauth, bindaddauth, ".
         "         connectauth, nofenceauth, implschemaauth, loadauth ".
         "    FROM syscat.dbauth ".
         "    WHERE  GRANTEETYPE = 'G' AND GRANTOR = '$user' for read only";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler on util_funcs.php */
    trigger_error("  Select statement Failed   $sqlerror", ERROR);
  }
  else
  {
    /* call function from util_funcs.php which fetches
       the rows and put it into an array */
    $array = odbc_fetch_resultset($result);
    
    printf("\n  Group DBADM authority           : %s\n",
              displayfull($array[1]["DBADMAUTH"]));
    printf("  Group CREATETAB authority       : %s\n",
              displayfull($array[1]["CREATETABAUTH"]));
    printf("  Group BINDADD authority         : %s\n",
              displayfull($array[1]["BINDADDAUTH"]));
    printf("  Group CONNECT authority         : %s\n",
              displayfull($array[1]["CONNECTAUTH"]));
    printf("  Group CREATE_NOT_FENC authority : %s\n",
             displayfull($array[1]["NOFENCEAUTH"]));
    printf("  Group IMPLICIT_SCHEMA authority : %s\n",
              displayfull($array[1]["IMPLSCHEMAAUTH"]));
    printf("  Group LOAD authority            : %s\n",
              displayfull($array[1]["LOADAUTH"]));
  }
  
} /* DbAuthForCurrentUserDisplay */

/**************************************************************************
** Description : This function shows how to revoke the user authorities 
**               at database level
** Input       : ODBC connection id 
** Output      : None
***************************************************************************/
function DbAuthRevoke($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  REVOKE (Database Authorities)\n");
  printf("  COMMIT\n");
  printf("TO REVOKE AUTHORITIES AT DATABASE LEVEL.\n");

  /* revoke user authorities at database level */
  printf("\n  REVOKE CONNECT, CREATETAB, BINDADD ON DATABASE" .
         " FROM USER user1\n");

  $statement =  "REVOKE CONNECT, CREATETAB, BINDADD ON DATABASE ".
         " FROM USER user1";

  /* prepare and execute the SQL statement */
  $result = odbc_exec($dbconn,$statement);
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* call the error handler on util_funcs.php */
    trigger_error("  Revoke statement Failed   $sqlerror", ERROR);
  }
  else
  {
    printf("  COMMIT\n");
    odbc_commit($dbconn);
  }
  
} /* DbAuthRevoke */
?>
