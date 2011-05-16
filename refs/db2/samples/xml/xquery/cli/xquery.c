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
** SOURCE FILE NAME: xquery.c
**
** SAMPLE: How to run a nested XQuery 
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
** XQUERY EXPRESSION USED
**           FLWOR Expression
**
**                  
** OUTPUT FILE: xquery.out (available in the online documentation)
*****************************************************************************
**
** For more information on the sample programs, see the README file.
**
** For information on developing CLI applications, see the CLI Guide
** and Reference.
**
** For information on using XQuery statements, see the XQuery Reference
** For information on using SQL statements, see the SQL Reference.
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

/* Functions used in the sample */

/* The PO_orderbycity function restructures the purchaseorders according to the city. */
int PO_orderbycity(SQLHANDLE hdbc);

/* The Customer_orderbyproduct restructures the purchaseorder according to the product */
int Customer_orderbyproduct(SQLHANDLE hdbc);

/* The PO_orderbyProvCityStreet function restructures the purchaseorder data according to provience, city and street */
int PO_orderbyProvCityStreet(SQLHANDLE hdbc);

/* This CustomerPO function combines the data from customer and product table to create a purchaseorder*/ 
int CustomerPO(SQLHANDLE hdbc);

int main(int argc, char *argv[])
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE henv; /* environment handle */
  SQLHANDLE hdbc; /* connection handle */
  char id[10];
  char dbAlias[SQL_MAX_DSN_LENGTH + 1];
  char user[MAX_UID_LENGTH + 1];
  char pswd[MAX_PWD_LENGTH + 1];

  /* check the command line arguments */
  rc = CmdLineArgsCheck1(argc, argv, dbAlias, user, pswd);
  if (rc != 0)
  {
    return rc;
  }

  printf("\nTHIS SAMPLE DEMONSTRATES HOW THE NESTED XQUERIES CAN BE RUN USING CLI");
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
  printf("-------------------------------------------------------------\n");
  printf("RESTRUCTURE THE PURCHASEORDERS ACCORDING TO THE CITY....\n");
  rc=PO_orderbycity(hdbc);
  
  printf("-------------------------------------------------------------\n");
  printf("RESTRUCTURE THE PURCHASEORDER ACCORDING TO THE PRODUCT.....\n");
  rc=Customer_orderbyproduct(hdbc);

  printf("-------------------------------------------------------------\n");
  printf("RESTRUCTURE THE PURCHASEORDER DATA ACCORDING TO PROVIENCE, CITY AND STREET..\n");
  rc=PO_orderbyProvCityStreet(hdbc);
 
  printf("-------------------------------------------------------------\n");
  printf("COMBINE THE DATA FROM PRODUCT AND CUSTOMER TABLE TO CREATE A PURCHASEORDER..\n");
  rc=CustomerPO(hdbc);
} /* main */

int Customer_orderbyproduct(SQLHANDLE hdbc)
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hstmt; /* statement handle */
  SQLVARCHAR xmldata[5000];

  /* XQUERY statement to be executed */
  SQLCHAR *stmt = (SQLCHAR *)"XQUERY for $partid in fn:distinct-values(db2-fn:xmlcolumn('PURCHASEORDER.PORDER')" 
             "/PurchaseOrder/item/partid)"
             " return"
             " <Product name='{$partid}'>"
             " <Customers>"
             "{"
             "let $po:=db2-fn:sqlquery(\"SELECT XMLELEMENT( NAME \"\"pos\"\","
                                                    " (XMLCONCAT( XMLELEMENT(NAME \"\"custid\"\", c.custid),"
                                                            "XMLELEMENT(NAME \"\"order\"\", c.porder)"
                                                        ") ))"
                                    " FROM purchaseorder AS c\")"
            " for $order in $po[order/PurchaseOrder/item/partid=$partid],"
            " $cust in db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo where $cust/@Cid=$order/custid"
            " return"
            " $cust"
          "}"
          "</Customers>"
      "</Product>";
 
  /* allocate a statement handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  printf("\n  Directly execute the statement\n");
  printf("    %s\n\n", stmt);

  /* directly execute the statement */
  cliRC = SQLExecDirect(hstmt, stmt, SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

   /* bind column 1 to variable */
  cliRC = SQLBindCol(hstmt, 1, SQL_C_CHAR, &xmldata, 2000, NULL);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
  
  /* fetch each row and display */
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
} /* Customer_orderbyproduct */

int PO_orderbycity(SQLHANDLE hdbc)
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hstmt; /* statement handle */
  SQLVARCHAR xmldata[3000];
  
  /* XQUERY statement to be executed */
  SQLCHAR *stmt = (SQLCHAR *) "XQUERY "
              " let $po:=db2-fn:sqlquery(\"SELECT XMLELEMENT( NAME \"\"pos\"\","
                                              " (XMLCONCAT( XMLELEMENT(NAME \"\"custid\"\", c.custid),"
                                                           "XMLELEMENT(NAME \"\"order\"\", c.porder)"
                                                               "    ) ))"
                                   " FROM purchaseorder AS c\")"
          " for $city in fn:distinct-values(db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo/addr/city)"
             " return"
               " <city name='{$city}'>"
              "{"
                 " for  $cust in db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo[addr/city=$city]"
         " let $id:=$cust/@Cid,"
             " $order:=$po[custid=$id]/order"
         " return"
         " <customer id='{$id}'>"
          " {$cust/name}"
          " {$cust/addr}"
          " {$order}"
         " </customer>}"
        " </city>";
                       
  /* allocate a statement handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  printf("\n  Directly execute the statement\n");
  printf("    %s\n\n", stmt);

  /* directly execute the statement */
  cliRC = SQLExecDirect(hstmt, stmt, SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* bind column 1 to variable */
  cliRC = SQLBindCol(hstmt, 1, SQL_C_CHAR, &xmldata, 2000, NULL);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);
 
  /* fetch the result and display */
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

} /* PO_orderbycity */

int PO_orderbyProvCityStreet(SQLHANDLE hdbc)
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hstmt; /* statement handle */
  SQLVARCHAR xmldata[5000];

  /* XQUERY statement to be executed */
  SQLCHAR *stmt = (SQLCHAR *)"XQUERY " 
     " let $po:=db2-fn:sqlquery(\"SELECT XMLELEMENT( NAME \"\"pos\"\","
                                          "( XMLCONCAT( XMLELEMENT(NAME \"\"custid\"\", c.custid),"
                                          "XMLELEMENT(NAME \"\"order\"\", c.porder)"
                                                       ") ))"
                                           " FROM PURCHASEORDER as c\"),"
       " $addr:=db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo/addr"
       " for $prov in distinct-values($addr/prov-state)"
       " return"
       " <province name='{$prov}'>"
       " {"
         " for $city in fn:distinct-values($addr[prov-state=$prov]/city)"
         " return"
         " <city name='{$city}'>"
         " {"
           " for $s in fn:distinct-values($addr/street) where $addr/city=$city"
           " return"
           " <street name='{$s}'>"
           " {"
             " for $info in $addr[prov-state=$prov and city=$city and street=$s]/.."
             " return"
             " <customer id='{$info/@Cid}'>"
             " {$info/name}"
             " {"
               " let $id:=$info/@Cid, $order:=$po[custid=$id]/order"
               " return $order"
             " }"
            " </customer>"
           " }"
           " </street>"
         " }"
          " </city>"
       " }"
       " </province>";
 
 
   /* allocate a statement handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  printf("\n  Directly execute the statement\n");
  printf("    %s\n\n", stmt);

  /* directly execute the statement */
  cliRC = SQLExecDirect(hstmt, stmt, SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* bind column 1 to variable */
  cliRC = SQLBindCol(hstmt, 1, SQL_C_CHAR, &xmldata, 5000, NULL);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* fetch the result and display */
  cliRC = SQLFetch(hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  if (cliRC == SQL_NO_DATA_FOUND)
  {
    printf("\n  Data not found.\n");
  }
    printf("%s \n\n",xmldata);

  /* free the statement handle */
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  return rc;
} /* PO_orderbyProvCityStreet */ 


int CustomerPO(SQLHANDLE hdbc)
{
  SQLRETURN cliRC = SQL_SUCCESS;
  int rc = 0;
  SQLHANDLE hstmt; /* statement handle */
  SQLVARCHAR xmldata[3000];

  /* XQUERY statement to be executed */
  SQLCHAR *stmt = (SQLCHAR *)"XQUERY "
                                        "<PurchaseOrder>"
                    "{"
                        " for $ns1_customerinfo0 in db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo"
                        " where ($ns1_customerinfo0/@Cid=1001)"
                        " return"
                        " <customer customerid='{ fn:string( $ns1_customerinfo0/@Cid)}'>"
                        " {$ns1_customerinfo0/name}"
                            " <address>"
                              " {$ns1_customerinfo0/addr/street}"
                              " {$ns1_customerinfo0/addr/city}"
                              " {"
                                 " if($ns1_customerinfo0/addr/@country=\"US\")"
                                 " then"
                                  " $ns1_customerinfo0/addr/prov-state"
                                  " else()"
                              " }"
                               " {"
                   " fn:concat ($ns1_customerinfo0/addr/pcode-zip/text(),\",\",fn:upper-case($ns1_customerinfo0/addr/@country))}"
                           " </address>"
                          " </customer>"
                        " }"
                        " {"
                         " for $ns2_product0 in db2-fn:xmlcolumn('PRODUCT.DESCRIPTION')/product"
                         " where ($ns2_product0/@pid=\"100-100-01\")"
                         " return"
                         " $ns2_product0"
                     " }"
                   " </PurchaseOrder>";

  /* allocate a statement handle */
  cliRC = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
  DBC_HANDLE_CHECK(hdbc, cliRC);

  printf("\n  Directly execute the statement\n");
  printf("    %s\n\n", stmt);

  /* directly execute the statement */
  cliRC = SQLExecDirect(hstmt, stmt, SQL_NTS);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* bind column 1 to variable */
  cliRC = SQLBindCol(hstmt, 1, SQL_C_CHAR, &xmldata, 3000, NULL);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  /* fetch the result and display */
  cliRC = SQLFetch(hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  if (cliRC == SQL_NO_DATA_FOUND)
  {
    printf("\n  Data not found.\n");
  }
    printf("%s \n\n",xmldata);

  /* free the statement handle */
  cliRC = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
  STMT_HANDLE_CHECK(hstmt, hdbc, cliRC);

  return rc;

} /* CustomerPO */


