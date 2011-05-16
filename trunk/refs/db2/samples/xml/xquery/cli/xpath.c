/****************************************************************************
** Licensed Materials - Property of IBM
**
** Governed under the terms of the International
** License Agreement for Non-Warranted Sample Code.
**
** (C) COPYRIGHT International Business Machines Corp. 2006
** All Rights Reserved.
**
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
*****************************************************************************
**
** SOURCE FILE NAME: xpath.c
**
** SAMPLE: How to run queries with a simple path expression 
**
** CLI FUNCTIONS USED: 
**                SQLAllocHandle
**                SQLExecDirect
**                SQLBindCol
**                SQLFetch
**                SQLFreeHandle
**
** SQL/XML FUNCTIONS USED:
**                xmlcolumn 
**
** XQuery functions used:
**                distinct-values
**                starts-with
**                avg
**                count 
**
** OUTPUT FILE: xpath.out (available in the online documentation)
*****************************************************************************
**
** For more information on the sample programs, see the README file.
**
** For information on developing CLI applications, see the CLI Guide
** and Reference.
**
** For information on using SQL statements, see the SQL Reference.
**
** For information on using XQuery statements, see the XQuery Reference
**
** For the latest information on programming, building, and running DB2
** applications, visit the DB2 application development website:
**     http://www.software.ibm.com/data/db2/udb/ad
****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlcli1.h>
#include "utilcli.h" /* Header file for CLI sample code */

/* Functions used in the samples */
/* The CustomerDetails method returns all of the XML data in the INFO column of the CUSTOMER table */
int CustomerDetails(SQLHANDLE hdbc);

/* The CustomerFromToronto method returns information about customers from Toronto */
int CustomerFromToronto(SQLHANDLE hdbc);

/* The CitiesInCanada method returns a list of cities that are in Canada */
int CitiesInCanada(SQLHANDLE hdbc);

/* The CustMobileNum method returns the names of customers whose mobile number starts with 905 */
int CustMobileNum(SQLHANDLE hdbc);

/* The AvgPRice method determines the average prive of the products in the 100 series */
int AvgPrice(SQLHANDLE hdbc);

/* The NumOfCustInToronto method returns the number of customer from Toronto city */
int NumOfCustInToronto( SQLHANDLE hdbc);

int main(int argc, char *argv[])
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE henv; /* environment handle */
  SQLHANDLE hdbc; /* connection handle */

  char dbAlias[SQL_MAX_DSN_LENGTH + 1];
  char user[MAX_UID_LENGTH + 1];
  char pswd[MAX_PWD_LENGTH + 1];

  /* check the command line arguments */
  rc = CmdLineArgsCheck1(argc, argv, dbAlias, user, pswd);
  if (rc != 0)
  {
    return rc;
  }

  printf("\nTHIS SAMPLE DEMONSTRATES HOW THE QUERIES WITH SIMPLE PATH EXPRESSION CAN BE RUN USING CLI");
   /* initialize the CLI application by calling a helper
     utility function defined in utilcli.c */
  rc = CLIAppInit(dbAlias,
                  user,
                  pswd,
                  &henv,
                  &hdbc,
                  (SQLPOINTER)SQL_AUTOCOMMIT_ON);
  if (rc != 0)
  {
    return rc;
  }
  printf("**********************************\n"); 
  printf("Select the customer details.....");
  rc=CustomerDetails(hdbc);
  
  printf("**********************************\n");
  printf("Select the customer's cities from Canada .....\n");
  rc=CitiesInCanada(hdbc);
  
  printf("**********************************\n");
  printf("Select the Average price for all the product in 100 series.....\n");
  rc=AvgPrice(hdbc);

  printf("*********************************\n");
  printf("Select the customer details from Toronto city.......\n");
  rc=CustomerFromToronto(hdbc);
 
  printf("*********************************\n");
  printf("Select the number of customer from Toronto city.......\n");
  rc= NumOfCustInToronto(hdbc);
  
  printf("*********************************\n");
  printf("Select the name of the customer with mobile number start from 905.......\n");
  rc=CustMobileNum(hdbc);
} /* main */


/* This function will find out the customer details from CUSTOMER.INFO column */
int CustomerDetails(SQLHANDLE hdbc)
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hstmt; /* statement handle */
  SQLVARCHAR xmldata[3000];
  
  /* XPATH statement to be executed */
  SQLCHAR *stmt = (SQLCHAR *)"XQUERY " 
                  "db2-fn:xmlcolumn('CUSTOMER.INFO')";
  
  /* Allocate a statement handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);
  printf("\n Directly execute the statement\n");
  printf(" %s\n", stmt);

  /* Directly execute the statement */
  cliRC = SQLExecDirect(hstmt, stmt, SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
 
  /* Bind column 1 to variable */
  cliRC = SQLBindCol(hstmt, 1, SQL_C_CHAR, &xmldata, 1000, NULL);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
 
  /* Fetch each row and display */
  cliRC = SQLFetch(hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  if (cliRC == SQL_NO_DATA_FOUND)
  {
    printf("\n  Data not found.\n");
  }
  while (cliRC != SQL_NO_DATA_FOUND)
  {
    /* Print the data */
    printf("----------------------------------------------------------------------------\n");
    printf("%s \n",xmldata);

    /* Fetch next row */
    cliRC = SQLFetch(hstmt);
    STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  }

  /* Free the statement handle */
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  return rc;
} /* CustomerDetails */

/* This function will find out the customer's cities from Toronto */
int CitiesInCanada(SQLHANDLE hdbc)
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hstmt; /* statement handle */
  SQLVARCHAR xmldata[3000];

  /* XPATH statement to be executed */
  SQLCHAR *stmt = (SQLCHAR *)"XQUERY fn:distinct-values(db2-fn:xmlcolumn('CUSTOMER.INFO')"
                          "/customerinfo/addr[@country=\"Canada\"]/city)";

  /* Allocate a statement handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  printf("\n  Directly execute the statement\n");
  printf("    %s\n", stmt);

  /* Directly execute the statement */
  cliRC = SQLExecDirect(hstmt, stmt, SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* Bind column 1 to variable */
  cliRC = SQLBindCol(hstmt, 1, SQL_C_CHAR, &xmldata, 1000, NULL);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  
  /* Fetch each row and display */
  cliRC = SQLFetch(hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  if (cliRC == SQL_NO_DATA_FOUND)
  {
    printf("\n  Data not found.\n");
  }
  while (cliRC != SQL_NO_DATA_FOUND)
  {
    /* Print the data */ 
    printf("%s \n\n",xmldata);

    /* Fetch next row */
    cliRC = SQLFetch(hstmt);
    STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  }

  /* free the statement handle */
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  return rc;
} /* CitiesInCanada */

/* This function will find out the average price of all the product in 100 series */
int AvgPrice(SQLHANDLE hdbc)
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hstmt; /* statement handle */
  SQLVARCHAR xmldata[1000]; 

  /* XPATH statement to be executed */
  SQLCHAR *stmt = (SQLCHAR *)"XQUERY let $prod_price := db2-fn:xmlcolumn('PRODUCT.DESCRIPTION')"
                             "/product[fn:starts-with(@pid,\"100\")]/description/price"
                              " return avg($prod_price)";

  /* Allocate a statement handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  printf("\n  Directly execute the statement\n");
  printf("    %s\n", stmt);

  /* Directly execute the statement */
  cliRC = SQLExecDirect(hstmt, stmt, SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

   /* Bind column 1 to variable */
  cliRC = SQLBindCol(hstmt, 1, SQL_C_CHAR, &xmldata, 1000, NULL);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  
  /* Fetch each row and display */
  cliRC = SQLFetch(hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  if (cliRC == SQL_NO_DATA_FOUND)
  {
    printf("\n  Data not found.\n");
  }
  else
  printf("%s \n\n",xmldata);

  /* free the statement handle */
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  return rc;
} /* AvgPrice */

/* This function will find out the customer details from Toronto city */
int CustomerFromToronto(SQLHANDLE hdbc)
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hstmt; /* statement handle */
  SQLVARCHAR xmldata[3000];
  
  /* XPATH statement to be executed */
  SQLCHAR *stmt = (SQLCHAR *)"XQUERY db2-fn:xmlcolumn (\"CUSTOMER.INFO\") "
                             " /customerinfo[addr/city=\"Toronto\"]";
  
  /* Allocate a statement handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  printf("\n  Directly execute the statement\n");
  printf("    %s\n", stmt);

  /* Directly execute the statement */
  cliRC = SQLExecDirect(hstmt, stmt, SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* Bind column 1 to variable */
  cliRC = SQLBindCol(hstmt, 1, SQL_C_CHAR, &xmldata, 1000, NULL);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  
  /* Fetch each row and display */
  cliRC = SQLFetch(hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  if (cliRC == SQL_NO_DATA_FOUND)
  {
    printf("\n  Data not found.\n");
  }
  while (cliRC != SQL_NO_DATA_FOUND)
  {
    /* Print the data */
    printf("%s \n\n",xmldata);

    /* Fetch next row */
    cliRC = SQLFetch(hstmt);
    STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  }

  /* Free the statement handle */
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  return rc;
} /* CustomerFromToronto */

int NumOfCustInToronto(SQLHANDLE hdbc)
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hstmt; /* statement handle */
  SQLVARCHAR xmldata[3000];
 
  /* XPATH statement to be executed */
  SQLCHAR *stmt = (SQLCHAR *)"XQUERY fn:count(db2-fn:xmlcolumn(\"CUSTOMER.INFO\") "
                             " /customerinfo[addr/city=\"Toronto\"])";
  
  /* Allocate a statement handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  printf("\n  Directly execute the statement\n");
  printf("    %s\n", stmt);

  /* Directly execute the statement */
  cliRC = SQLExecDirect(hstmt, stmt, SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* Bind column 1 to variable */
  cliRC = SQLBindCol(hstmt, 1, SQL_C_CHAR, xmldata, 1000, NULL);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  
  /* Fetch each row and display */
  cliRC = SQLFetch(hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  if (cliRC == SQL_NO_DATA_FOUND)
  {
    printf("\n  Data not found.\n");
  }
  else
  printf("%s \n\n",xmldata);

  /* free the statement handle */
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  return rc;
} /* NumOfCustInToronto */

/* This function will find out the customer names with mobile number start with 905 */
int CustMobileNum(SQLHANDLE hdbc)
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hstmt; /* statement handle */
  SQLVARCHAR xmldata[3000];
  
  /* XPATH statement to be executed */
  SQLCHAR *stmt = (SQLCHAR *)"XQUERY db2-fn:xmlcolumn(\"CUSTOMER.INFO\")"
                           "/customerinfo[phone[@type=\"cell\" and fn:starts-with(text(),\"905\")]]";   
  /* Allocate a statement handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  printf("\n  Directly execute the statement\n");
  printf("    %s\n", stmt);

  /* Directly execute the statement */
  cliRC = SQLExecDirect(hstmt, stmt, SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

   /* Bind column 1 to variable */
  cliRC = SQLBindCol(hstmt, 1, SQL_C_CHAR, &xmldata, 1000, NULL);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  
  /* Fetch each row and display */
  cliRC = SQLFetch(hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  if (cliRC == SQL_NO_DATA_FOUND)
  {
    printf("\n  Data not found.\n");
  }
  while (cliRC != SQL_NO_DATA_FOUND)
  {
    printf("%s \n\n",xmldata);

    /* fetch next row */
    cliRC = SQLFetch(hstmt);
    STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  }

  /* free the statement handle */
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  return rc;
} /* CustMobileNum */
