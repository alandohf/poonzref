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
**  SOURCE FILE NAME: udfcli.php
**
**  SAMPLE: Call a variety of types of user-defined functions
**
**  SQL STATEMENTS USED:
**         CREATE DISTINCT TYPE
**         CREATE FUNCTION
**         CREATE TABLE
**         DROP DISTINCT TYPE
**         DROP FUNCTION
**         DROP TABLE
**
** OUTPUT FILE: udfcli.out (available in the online documentation)
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

/* call the error handler in util_funcs.php*/
Error_handler();

/* check and parse the command line arguments*/
CmdLineArgChk($argc, $argv, $dbname, $username, $password);

printf("\n  THIS SAMPLE SHOWS HOW TO WORK WITH UDFs.\n\n");

/* connect to the database with specified username and password */
$dbconn = DbConn($dbname, $username, $password);

/* override the auto commit option */
odbc_autocommit($dbconn, FALSE);

/* check the connection to the database */
if ($dbconn != 0)
{
  /* scalar UDFs */
  ExternalScalarUDFUse($dbconn);
  ExternalScratchpadScalarUDFUse($dbconn);
  ExternalClobScalarUDFUse($dbconn);

  /* column UDFs */
  SourcedColumnUDFUse($dbconn);

  /* table UDFs */
  ExternalTableUDFUse($dbconn);

}

/* disconnect from the database */
DbDisconn($dbconn);

/**************************************************************************
** Description :  This function shows how to use External Scalar User 
**                Defined Function
** Input       :  ODBC connection id
** Output      :  None
***************************************************************************/
function ExternalScalarUDFUse($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS\n");
  printf("  CREATE FUNCTION\n");
  printf("  SELECT\n");
  printf("  DROP FUNCTION\n");
  printf("TO WORK WITH SCALAR UDF:\n");

  /* drop scalar UDF, if exists */
  printf("\n  DROP the scalar UDF, if exists.\n");

  $statement = "DROP FUNCTION ScalarUDF";

  /* prepare and execute a SQL statement*/
  odbc_exec($dbconn, $statement);

  /* register scalar UDF */
  printf("\n  Register the scalar UDF.\n\n");

  $statement = "CREATE FUNCTION ScalarUDF(CHAR(5), DOUBLE)".
               "  RETURNS DOUBLE ".
               "  EXTERNAL NAME 'udfsrv!ScalarUDF'".
               "  FENCED " .
               "  CALLED ON NULL INPUT ".
               "  NOT VARIANT".
               "  NO SQL ".
               "  PARAMETER STYLE SQL ".
               "  LANGUAGE C ".
               "  NO EXTERNAL ACTION ";

   /* prepare and execute a SQL statement */
  $result = odbc_exec($dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* calling the error handler in util_funcs.php */
    trigger_error("  CREATE FUNCTION statement Failed  $sqlerror", ERROR);
  }
  else
  {
    printf("  Commit.\n");
    odbc_commit($dbconn);

    /* use scalar UDF */
    printf("\n  Use the scalar UDF:\n");
    printf("    SELECT name, job, salary, ScalarUDF(job, salary)\n");
    printf("      FROM staff\n");
    printf("      WHERE name LIKE 'S%%' FOR READ ONLY\n");
    $strStmt = "SELECT name, job, salary, ScalarUDF(job, salary) ".
               "  FROM staff ".
               "  WHERE name LIKE 'S%' FOR READ ONLY";
    
    /* prepare and execute a SQL statement */
    $result = odbc_exec($dbconn, $strStmt);
    
    if ($result == 0)
    {
      $sqlerror = odbc_errormsg($dbconn);

      /* calling the error handler on util_funcs.php */
      trigger_error("  SELECT statement Failed   $sqlerror", ERROR);
    }
    else
    {
      /* fetch the result set into an array */
      $array = odbc_fetch_resultset($result);
      
      printf("\n  Fetch each row and display.\n");
      printf("    NAME       JOB     SALARY   NEW_SALARY\n");
      printf("    ---------- ------- -------- ----------\n");

      for ($i = 1; odbc_fetch_row($result, $i); $i++)
      {
        printf("    %-10s %-7s %-7.2f %-7.2f", 
                    $array[$i]['NAME'], $array[$i]['JOB'],
                    $array[$i]['SALARY'], $array[$i][4]);
        printf("\n");

      }
      
    }
    
  }

  /* drop scalar UDF */
  printf("\n  DROP the scalar UDF.\n\n");

  $statement = "DROP FUNCTION ScalarUDF";

  /* prepare and execute a SQL statement*/
  odbc_exec($dbconn, $statement);

  printf("  Commit.\n");
  odbc_commit($dbconn);

} /* ExternalScalarUDFUse */

/**************************************************************************
** Description : This function shows how to use scratchpad scalar
**               User Defined Function
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function   ExternalScratchpadScalarUDFUse($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS\n");
  printf("  CREATE FUNCTION\n");
  printf("  SELECT\n");
  printf("  DROP FUNCTION\n");
  printf("TO WORK WITH SCRATCHPAD SCALAR UDF:\n");
  
  /* drop SCRATCHPAD scalar UDF, if exists */
  printf("\n  DROP the SCRATCHPAD scalar UDF, if exists.\n");
  
  $statement = "DROP FUNCTION ScratchpadScUDF\n";

  /* prepare and execute a SQL statement */
  odbc_exec($dbconn, $statement);
  
  /* register SCRATCHPAD scalar UDF */
  printf("\n  Register the SCRATCHPAD scalar UDF.\n");
  
  $statement = "CREATE FUNCTION ScratchpadScUDF() ".
               "  RETURNS INTEGER ".
               "  EXTERNAL NAME 'udfsrv!ScratchpadScUDF' ".
               "  FENCED ".
               "  SCRATCHPAD 10 ".
               "  FINAL CALL ".
               "  VARIANT ".
               "  NO SQL ".
               "  PARAMETER STYLE SQL ".
               "  LANGUAGE C ".
               "  NO EXTERNAL ACTION ";
  
  
  /* use SCRATCHPAD scalar UDF */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* calling the error handler in util_funcs.php */
    trigger_error("  CREATE FUNCTION statement Failed $sqlerror", ERROR);
  }
  else
  {
    printf("\n  Commit.\n");
    odbc_commit($dbconn);

    printf("\n  Use the SCRATCHPAD scalar UDF:\n");
    printf("    SELECT ScratchpadScUDF(), name, job\n");
    printf("      FROM staff\n");
    printf("      WHERE name LIKE 'S%%' FOR READ ONLY\n");
    
    $strStmt = "SELECT ScratchpadScUDF(), name, job ".
               "  FROM staff ".
               "  WHERE name LIKE 'S%' FOR READ ONLY";
    
    /* prepare and execute a SQL statement */
    $result = odbc_exec($dbconn, $strStmt);
    
    if ($result == 0)
    {
      $sqlerror = odbc_errormsg($dbconn);

      /* calling the error handler on util_funcs.php */
      trigger_error("  SELECT statement Failed $sqlerror", ERROR);
    }
    else
    {
      
      $array = odbc_fetch_resultset($result);
      printf("\n  Fetch each row and display.\n");
      printf("    COUNTER NAME       JOB    \n");
      printf("    ------- ---------- -------\n");
      for ($i = 1; odbc_fetch_row($result, $i); $i++)
      {
        printf("    %7d %-10s %-7s", $array[$i][1], 
                         $array[$i]['NAME'], $array[$i]['JOB']);
        printf("\n");
      }
      
    }

    /* drop scalar UDF */
    printf("\n  DROP the SCRATCHPAD scalar UDF.\n");
    
    $statement = "DROP FUNCTION ScratchpadScUDF";

    /* prepare and execute a SQL statement */
    odbc_exec($dbconn, $statement);
    
    printf("\n  Commit.\n");
    odbc_commit($dbconn);
  }

} /* ExternalScratchpadScalarUDFUse */ 

/**************************************************************************
** Description : This function shows how to use external clob scalar
**               User Defined Function
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function ExternalClobScalarUDFUse($dbconn)
{
  
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS\n");
  printf("  CREATE FUNCTION\n");
  printf("  SELECT\n");
  printf("TO WORK WITH CLOB SCALAR UDF:\n");

  /* drop CLOB scalar UDF, if exists */
  printf("\n  DROP the CLOB scalar UDF, if exists.\n");
  
  $statement = "DROP FUNCTION ClobScalarUDF";

  /* prepare and execute a SQL statement */
  odbc_exec($dbconn, $statement);

  $statement = "CREATE FUNCTION ClobScalarUDF(CLOB(5 K)) ".
               "  RETURNS INTEGER".
               "  EXTERNAL NAME 'udfsrv!ClobScalarUDF'".
               "  FENCED".
               "  NOT VARIANT".
               "  NO SQL".
               "  PARAMETER STYLE SQL".
               "  LANGUAGE C ".
               "  NO EXTERNAL ACTION ";
  
   printf("\n  Register the CLOB scalar UDF\n"); 
                
  /* prepare and execute a SQL statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* calling the error handler in util_funcs.php */
    trigger_error("  CREATE FUNCTION statement Failed   $sqlerror", ERROR);
  }
  else
  {
    printf("\n  Commit.\n");
    odbc_commit($dbconn);

    /* use CLOB scalar UDF */
    printf("\n  Use the CLOB scalar UDF:\n");
    printf("    SELECT empno, resume_format, ClobScalarUDF(resume)\n");
    printf("      FROM emp_resume\n");
    printf("      WHERE resume_format = 'ascii' FOR READ ONLY\n");

    $strStmt = "SELECT empno, resume_format, ClobScalarUDF(resume) ".
               "  FROM emp_resume ".
               "  WHERE resume_format = 'ascii' FOR READ ONLY";
                  
    /* prepare and execute a SQL statement */
    $result = odbc_exec($dbconn, $strStmt);

    if ($result == 0)
    {
      $sqlerror = odbc_errormsg($dbconn);

      /* calling the error handler from util_funcs.php */
      trigger_error("  SELECT statement Failed   $sqlerror", ERROR);
    }
    else
    {

      $array = odbc_fetch_resultset($result);
      printf("\n  Fetch each row and display.\n");
      printf("    EMPNO   RESUME_FORMAT NUM.WORDS\n");
      printf("    ------- ------------- ---------\n");
      for ($i = 1; odbc_fetch_row($result, $i); $i++)
      {
        printf("    %-7s %-13s %ld", $array[$i]['EMPNO'],
                        $array[$i]['RESUME_FORMAT'], $array[$i][3]);
        printf("\n");
      }
      
    }

    /* drop CLOB scalar UDF */
    printf("\n  DROP the CLOB scalar UDF.\n");
    $statement = "DROP FUNCTION ClobScalarUDF";

    /* prepare and execute a SQL statement */
    odbc_exec($dbconn, $statement);

    printf("\n  Commit.\n");
    odbc_commit($dbconn);
  }
  
} /* ExternalClobScalarUDFUse */

/**************************************************************************
** Description : This function shows how to use sourced column User Defined
**               Function
** Input       : ODBC connection id
** Output      : None
***************************************************************************/
function SourcedColumnUDFUse($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS\n");
  printf("  CREATE DISTINCT TYPE\n");
  printf("  CREATE FUNCTION\n");
  printf("  CREATE TABLE\n");
  printf("  SELECT \n");
  printf("  DROP TABLE\n");
  printf("  DROP FUNCTION\n");
  printf("  DROP DISTINCT TYPE\n");
  printf("TO WORK WITH SOURCED COLUMN UDF:\n");

  printf("\n  DROP the table 'customer', if exists.\n");
  $statement = "DROP TABLE customer";

  /* prepare and execute a SQL statement */
  odbc_exec($dbconn, $statement);
  
  $strStmt = "DROP FUNCTION MAX(cnum)";
  odbc_exec($dbconn, $strStmt);

  printf("\n  DROP DISTINCT TYPE cnum, if exists.\n");
  $strStmt = "DROP DISTINCT TYPE cnum";
  odbc_exec($dbconn, $strStmt);
  
  printf("\n  Commit.\n");
  odbc_commit($dbconn);

  /* create distinct type */
  printf("\n  CREATE DISTINCT TYPE cnum AS INTEGER  WITH COMPARISONS\n");
  $strStmt = "CREATE DISTINCT TYPE cnum AS INTEGER WITH COMPARISONS";
  
  /* prepare and execute the statement */
  odbc_exec($dbconn, $strStmt);

  /* create sourced column UDF */
  printf("\n  CREATE FUNCTION MAX(cnum) RETURNS cnum");
  printf(" SOURCE SYSIBM.MAX(INTEGER)\n");
  $strStmt = "CREATE FUNCTION MAX(cnum) RETURNS cnum ".
             "  SOURCE SYSIBM.MAX(INTEGER)";
  
  /* prepare and execute the statement */
  odbc_exec($dbconn, $strStmt);

  /* create table that uses the distinct type */
  printf("\n  CREATE TABLE customer(custNum CNUM NOT NULL,");
  printf("\n                        custName CHAR(30) NOT NULL)\n");

  $strStmt = "CREATE TABLE customer(custNum CNUM NOT NULL,".
              "                   custName CHAR(30) NOT NULL)" ;
  
  /* prepare and execute the statement */
  odbc_exec($dbconn, $strStmt);

  /* populate customer table */
  printf("\n  INSERT INTO CUSTOMER VALUES ");
  printf("(CAST(1 AS CNUM), 'JOHN WALKER')\n    ");
  printf("                          (CAST(2 AS CNUM), 'BRUCE ADAMSON'),\n");
  printf("                              (CAST(3 AS CNUM), 'SALLY KWAN')\n");

  $strStmt = "INSERT INTO CUSTOMER VALUES(CAST(1 AS CNUM), 'JOHN WALKER'),".
             "                           (CAST(2 AS CNUM), 'BRUCE ADAMSON')".
             "                         , (CAST(3 AS CNUM), 'SALLY KWAN') "; 

  /* prepare and execute the statement */
  $result = odbc_exec($dbconn, $strStmt);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* calling the error handler from util_funcs.php */
    trigger_error("  INSERT statement Failed   $sqlerror ", ERROR);
  }

  printf("\n  Commit.\n");
  odbc_commit($dbconn);
  
  /* use sourced column UDF */
  printf("\n  Use the sourced column UDF:");
  printf("\n    SELECT CAST(MAX(custNum) AS INTEGER) FROM customer FOR READ ONLY\n");

  $strStmt = "SELECT CAST(MAX(custNum) AS INTEGER) FROM customer FOR READ ONLY";

  $result = odbc_exec($dbconn, $strStmt);
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* calling the error handler from util_funcs.php */
    trigger_error("  SELECT statement Failed   $sqlerror ", ERROR);
  }
  else
  {
      
    printf("\n  MAX(custNum) is: %d\n", odbc_result($result,1));
  }
  
  /* drop customer table */
  printf("\n  DROP TABLE customer.\n");
  $statement = "DROP TABLE customer";
  
  /* prepare and execute the statement */
  odbc_exec($dbconn, $statement);

  /* drop sourced column UDF */
  printf("\n  DROP FUNCTION MAX(cnum)\n");
  $strStmt = "DROP FUNCTION MAX(cnum)";
  
  /* prepare and execute the statement */
  odbc_exec($dbconn, $strStmt);
  
  /* drop cnum distinct type */
  printf("\n  DROP DISTINCT TYPE cnum\n");
  $strStmt = " DROP DISTINCT TYPE cnum";
  odbc_exec($dbconn, $strStmt);

  /* commit the transaction */
  printf("\n  Commit.\n");
  odbc_commit($dbconn);
  
} /* SourcedColumnUDFUse */

/**************************************************************************
** Description : This function shows how to use User Defined Function
**               returning tables
** Input       : Database connection id
** Output      : None
***************************************************************************/
function ExternalTableUDFUse($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS\n");
  printf("  CREATE FUNCTION\n");
  printf("  SELECT\n");
  printf("  DROP FUNCTION\n");
  printf("TO WORK WITH TABLE UDF:\n");
  
  /* drop table UDF, if exists */
  printf("\n  DROP FUNCTION TableUDF, if exists.\n");
  $statement = "DROP FUNCTION TableUDF";

  /* prepare and execute a SQL statement */
  odbc_exec($dbconn, $statement);

  /* register table UDF */
  printf("\n  Register the table UDF.\n");
  $statement = " CREATE FUNCTION TableUDF(DOUBLE) ".
                " RETURNS TABLE(name VARCHAR(20),".
                "               job VARCHAR(20),".
                "                salary DOUBLE) ".
                " EXTERNAL NAME 'udfsrv!TableUDF'".
                " LANGUAGE C ".
                " PARAMETER STYLE SQL ".
                " NOT DETERMINISTIC ".
                " FENCED ".
                " NO SQL".
                " NO EXTERNAL ACTION".
                " SCRATCHPAD 10".
                " FINAL CALL DISALLOW ".
                " PARALLEL NO DBINFO " ;

  /* prepare and execute the statement */
  $result = odbc_exec($dbconn, $statement);

  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* calling the error handler from util_funcs.php */
    trigger_error("  CREATE FUNCTION statement Failed   $sqlerror ", ERROR);
  }

  /* commit the transaction */
  printf("\n  Commit.\n");
  odbc_commit($dbconn);

  /* use table UDF */
  printf("\n  Use the table UDF:");
  printf("\n    SELECT udfTable.name, udfTable.job, udfTable.salary");
  printf("\n      FROM TABLE(TableUDF(1.5))");
  printf("\n      AS udfTable FOR READ ONLY\n");
  $statement =  "SELECT udfTable.name, udfTable.job, udfTable.salary " .
                  "  FROM TABLE(TableUDF(1.5)) ".
                  "  AS udfTable FOR READ ONLY";
 
  /* prepare and execute the statement */
  $result = odbc_exec( $dbconn, $statement);
  
  if ($result == 0)
  {
    $sqlerror = odbc_errormsg($dbconn);

    /* calling the error handler from util_funcs.php */
    trigger_error("  SELECT statement Failed   $sqlerror ", ERROR);
  }
  else
  {
    $array = odbc_fetch_resultset($result);
    printf("\n  Fetch each row and display.\n");
    printf("    NAME       JOB     SALARY   \n");
    printf("    ---------- ------- ---------\n");
    for ($i = 1; odbc_fetch_row($result, $i); $i++)
    {
      printf("    %-10s %-7s", $array[$i][NAME], $array[$i]['JOB']);
      
      if (salaryInd >= 0)
      {
        printf(" %7.2f", $array[$i]['SALARY']);
      }
      else
      {
        printf(" %8s", "-");
      }

      printf("\n");
    }
  
  /* drop table UDF */
  printf("\n  DROP FUNCTION TableUDF.\n");
  $statement = " DROP FUNCTION TableUDF";
  /* prepare and execute the statement */
  odbc_exec($dbconn, $statement);

  /* commit the transaction */
  printf("\n  Commit.\n");
  odbc_commit($dbconn);
  
  }
} /* ExternalTableUDFUse */

?>
