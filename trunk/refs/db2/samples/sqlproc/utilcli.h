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
** SOURCE FILE NAME: utilcli.h
**
** SAMPLE: Declaration of utility functions used by CLI samples
**
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

#ifndef UTILCLI_H
#define UTILCLI_H

#define MAX_UID_LENGTH 18
#define MAX_PWD_LENGTH 30
#define MAX_STMT_LEN 255
#define MAX_COLUMNS 255
#ifdef DB2WIN
#define MAX_TABLES 50
#else
#define MAX_TABLES 255
#endif

#ifndef max
#define max(a,b) (a > b ? a : b)
#endif

/* macro for environment handle checking */
#define ENV_HANDLE_CHECK(henv, cliRC)              \
if (cliRC != SQL_SUCCESS)                          \
{                                                  \
  rc = HandleInfoPrint(SQL_HANDLE_ENV, henv,       \
                       cliRC, __LINE__, __FILE__); \
  if (rc != 0) return rc;                          \
}

/* macro for connection handle checking */
#define DBC_HANDLE_CHECK(hdbc, cliRC)              \
if (cliRC != SQL_SUCCESS)                          \
{                                                  \
  rc = HandleInfoPrint(SQL_HANDLE_DBC, hdbc,       \
                       cliRC, __LINE__, __FILE__); \
  if (rc != 0) return rc;                          \
}

/* macro for statement handle checking */
#define STMT_HANDLE_CHECK(hstmt, hdbc, cliRC)      \
if (cliRC != SQL_SUCCESS)                          \
{                                                  \
  rc = HandleInfoPrint(SQL_HANDLE_STMT, hstmt,     \
                       cliRC, __LINE__, __FILE__); \
  if (rc == 2) StmtResourcesFree(hstmt);           \
  if (rc != 0) TransRollback(hdbc);                \
  if (rc != 0) return rc;                          \
}

/* macro for statement handle checking in
   applications with multiple connections */
#define MC_STMT_HANDLE_CHECK(hstmt, henv, cliRC)   \
if (cliRC != SQL_SUCCESS)                          \
{                                                  \
  rc = HandleInfoPrint(SQL_HANDLE_STMT, hstmt,     \
                       cliRC, __LINE__, __FILE__); \
  if (rc == 2) StmtResourcesFree(hstmt);           \
  if (rc != 0) MultiConnTransRollback(henv);       \
  if (rc != 0) return rc;                          \
}

/* functions used in ...CHECK_HANDLE macros */
int HandleInfoPrint(SQLSMALLINT, SQLHANDLE, SQLRETURN, int, char *);
void CLIAppCleanUp(SQLHANDLE *, SQLHANDLE a_hdbc[], int);
int StmtResourcesFree(SQLHANDLE);
void TransRollback(SQLHANDLE);
void MultiConnTransRollback(SQLHANDLE);

/* functions to check the number of command line arguments */
int CmdLineArgsCheck1(int, char *argv[], char *, char *, char *);
int CmdLineArgsCheck2(int, char *argv[], char *, char *, char *, char *);
int CmdLineArgsCheck3(int, char *argv[], char *, char *,
                      char *, char *, char *, char *);

/* other utility functions */
int CLIAppInit(char *, char *, char *, SQLHANDLE *, SQLHANDLE *, SQLPOINTER);
int CLIAppTerm(SQLHANDLE *, SQLHANDLE *, char *);
int StmtResultPrint(SQLHANDLE, SQLHANDLE);

#endif

