/****************************************************************************
** Licensed Materials - Property of IBM
** 
** Governed under the terms of the International
** License Agreement for Non-Warranted Sample Code.
**
** (C) COPYRIGHT International Business Machines Corp. 1995 - 2002        
** All Rights Reserved.
**
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
*****************************************************************************
**
** SOURCE FILE NAME: rsultset.c 
**
** SAMPLE: To call the MEDIAN_RESULT_SET SQL procedure
**
**         The program demonstrates how to return a result set from a stored
**         procedure.           
**
** CLI FUNCTIONS USED:
**         SQLAllocHandle -- Allocate Handle
**         SQLPrepare -- Prepare a Statement
**         SQLBindParameter -- Bind a Parameter Marker to a Buffer or
**                             LOB locator
**         SQLExecute -- Execute a Statement
**         SQLMoreResults -- Determine if There Are More Result Sets
**         SQLFreeHandle -- Free Handle Resources
**         SQLEndTran -- End Transactions of a Connection
**         SQLDisconnect -- Disconnect from a Data Source
**
** OUTPUT FILE: rsultset.out (available in the online documentation)
*****************************************************************************
**
** For more information on the sample programs, see the README file.
**
** For information on creating SQL procedures, see the Application
** Development Guide.
**
** For information on developing CLI applications, see the CLI Guide
** and Reference.
**
** For the latest information on programming, building, and running DB2 
** applications, visit the DB2 application development website: 
**     http://www.software.ibm.com/data/db2/udb/ad
****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlcli1.h>
#include "utilcli.h"  /* Header file for CLI sample code */

int main( int argc, char * argv[] )
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  int count = 1;
  SQLHANDLE henv; /* environment handle */
  SQLHANDLE hdbc; /* connection handle */
  SQLHANDLE hstmt; /* statement handle */
  SQLINTEGER outSqlrc;
  SQLDOUBLE medianSalary = 0;
  SQLSMALLINT numCols;
  SQLCHAR outName[40];
  SQLCHAR outJob[10];
  char procName[] = "MEDIAN_RESULT_SET";
  SQLCHAR *stmt = (SQLCHAR *) "CALL MEDIAN_RESULT_SET (?)";

  char dbAlias[SQL_MAX_DSN_LENGTH + 1];
  char user[MAX_UID_LENGTH + 1];
  char pswd[MAX_PWD_LENGTH + 1];

  char language[9];

  /* check the command line arguments */
  rc = CmdLineArgsCheck1(argc, argv, dbAlias, user, pswd);
  if (rc != 0)
  {
    return rc;
  }

  /* initialize the CLI application by calling a helper
     utility function defined in utilcli.c */
  rc = CLIAppInit(dbAlias,
                  user,
                  pswd,
                  &henv,
                  &hdbc,
                  (SQLPOINTER)SQL_AUTOCOMMIT_OFF);
  if (rc != 0)
  {
    return rc;
  }

  printf("\nHOW TO CALL AN SQL STORED PROCEDURE.");
  
  /* allocate a statement handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  /* prepare the statement */
  cliRC = SQLPrepare(hstmt, stmt, SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* bind parameter 1 to the statement */
  cliRC = SQLBindParameter(hstmt,
                           1,
                           SQL_PARAM_OUTPUT,
                           SQL_C_DOUBLE,
                           SQL_DOUBLE,
                           0,
                           0,
                           &medianSalary,
                           0,
                           NULL);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* execute the statement */
  cliRC = SQLExecute(hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  printf("\n\nMedian salary: %.2f", medianSalary);

  do
  {
    printf("\n\nReturning result set #%d:\n", count);
    cliRC = StmtResultPrint(hstmt, hdbc);
    DBC_HANDLE_CHECK( hdbc, cliRC );
    count++;
  }

  while (SQLMoreResults(hstmt) == SQL_SUCCESS);


  /* free the statement handles */
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* end transactions on the connection */
  cliRC = SQLEndTran(SQL_HANDLE_DBC, hdbc, SQL_ROLLBACK);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  /* terminate the CLI application by calling a helper
     utility function defined in utilcli.c */
  rc = CLIAppTerm(&henv, &hdbc, dbAlias);

  return rc;
}  /* end main */
