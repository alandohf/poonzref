/******************************************************************************/
/**                                                                          **/
/** Source File Name = utility.c  1.8                                        **/
/**                                                                          **/
/** Licensed Materials - Property of IBM                                     **/
/**                                                                          **/
/** (C) COPYRIGHT International Business Machines Corp. 1996 - 2002          **/
/** All Rights Reserved.                                                     **/
/**                                                                          **/
/** US Government Users Restricted Rights - Use, duplication or              **/
/** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.        **/
/**                                                                          **/
/**                                                                          **/
/** PURPOSE : Utility procedures for API implemented programs.  Procedures   **/
/**           include the checking of error, and a procedure that retreives  **/
/**           data                                                           **/
/**                                                                          **/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

#define MAXCOLS        255

#ifndef max
#define  max(a,b) (a > b ? a : b)
#endif

/*******************************************************************
**  - cliPrintError   - call SQLError(), display SQLSTATE and message
*******************************************************************/
#undef __FUNCTION_NAME__
#define __FUNCTION_NAME__ "cliPrintError"
void
cliPrintError(
                  SQLHENV henv,
                  SQLHDBC hdbc,
                  SQLHSTMT hstmt
                  )
{
                  SQLCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];
                  SQLCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
                  SQLINTEGER sqlcode;
                  SQLSMALLINT length;

                  while (SQLError(henv, hdbc, hstmt, sqlstate, &sqlcode, buffer,
                                                                SQL_MAX_MESSAGE_LENGTH + 1, &length) == SQL_SUCCESS) {
                                         printf("\n **** CLI ERROR *****\n");
                                         printf("         SQLSTATE: %s\n", sqlstate);
                                         printf("Native Error Code: %ld\n", sqlcode);
                                         printf("%s \n", buffer);
                  }
                  return;

} /* cliPrintError() */


/*******************************************************************
**  - check_error     - call cliPrintError().
**                    - check severity of Return Code
**                    - rollback & exit if error, continue if warning
*******************************************************************/
#undef __FUNCTION_NAME__
#define __FUNCTION_NAME__ "cliCheckError"
void
cliCheckError(
                  SQLHENV henv,
                  SQLHDBC hdbc,
                  SQLHSTMT hstmt,
                  SQLRETURN frc)
{
                  SQLRETURN rc;

                  if (frc == SQL_SUCCESS)
                                         return;

                  switch (frc){
                  case SQL_ERROR :
                  case SQL_INVALID_HANDLE:
                        cliPrintError(henv, hdbc, hstmt);
                                         printf("\n ** FATAL ERROR, Attempting to rollback transaction **\n");
                                         rc = SQLTransact(henv, hdbc, SQL_ROLLBACK);
                                         if (rc != SQL_SUCCESS)
                                                                printf("Rollback Failed, Exiting application\n");
                                         else
                                                                printf("Rollback Successful, Exiting application\n");
                                         cliTerminate(henv, hdbc);
                                         exit(frc);
                                         break;

                  case SQL_SUCCESS_WITH_INFO :
                                         break;

                  case SQL_NO_DATA_FOUND :
                        cliPrintError(henv, hdbc, hstmt);
                                         printf("\n ** No Data Found ** \n");
                                         break;

                  default:
                        cliPrintError(henv, hdbc, hstmt);
                                         printf("\n ** Invalid Return Code ** \n");
                                         printf(" ** Attempting to rollback transaction **\n");
                                         SQLTransact(henv, hdbc, SQL_ROLLBACK);
                                         cliTerminate(henv, hdbc);
                                         exit(frc);
                                         break;
                  }
                  return;

} /* cliCheckError() */


/*******************************************************************
** cliInitialize
**  - allocate environment handle
**  - allocate connection handle
**  - connect to server
*******************************************************************/
#undef __FUNCTION_NAME__
#define __FUNCTION_NAME__ "cliInitialize"
SQLRETURN
cliInitialize(
                  SQLHENV *henv,
                  SQLHDBC *hdbc,
                  SQLCHAR *server,
                  SQLCHAR *uid,
                  SQLCHAR *pwd
                  )
{
                  SQLRETURN rc;

                  rc = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,henv); /* allocate an environment handle */
                  cliCheckError(*henv, *hdbc, SQL_NULL_HSTMT, rc);

                  rc = SQLAllocHandle(SQL_HANDLE_DBC,*henv, hdbc); /* allocate a connection handle */
                  cliCheckError(*henv, *hdbc, SQL_NULL_HSTMT, rc);

                  if (uid[0] == '\0')
                                         rc = SQLConnect(*hdbc, server, SQL_NTS,
                                                                                                         NULL, SQL_NTS, NULL, SQL_NTS);
                  else
                                         rc = SQLConnect(*hdbc, server, SQL_NTS,
                                                                                                         uid, SQL_NTS, pwd, SQL_NTS);
                  cliCheckError(*henv, *hdbc, SQL_NULL_HSTMT, rc);

                  return rc;

} /* cliCheckError() */


/*******************************************************************
** cliTerminate
**  - disconnect
**  - free connection handle
**  - free environment handle
*******************************************************************/
#undef __FUNCTION_NAME__
#define __FUNCTION_NAME__ "cliTerminate"
SQLRETURN
cliTerminate(
                  SQLHENV henv,
                  SQLHDBC hdbc
                  )
{
                  SQLRETURN rc;

                  rc = SQLDisconnect(hdbc);       /* disconnect from database */
                  if (rc != SQL_SUCCESS)
                                         cliPrintError(henv, hdbc, SQL_NULL_HSTMT);

                  rc = SQLFreeHandle(SQL_HANDLE_DBC,hdbc); /* free connection handle */
                  if (rc != SQL_SUCCESS)
                                         cliPrintError(henv, hdbc, SQL_NULL_HSTMT);

                  rc = SQLFreeHandle(SQL_HANDLE_ENV,henv); /* free environment handle */
                  if (rc != SQL_SUCCESS )
                                         cliPrintError(henv, SQL_NULL_HDBC, SQL_NULL_HSTMT);

                  return rc;

} /* cliTerminate() */

/*--------------------------------------------------------------------------*/
/* Function:         printMsg                                               */
/*                                                                          */
/* Purpose:          print meaningful text for MMDB return code             */
/*--------------------------------------------------------------------------*/
void printMsg(SQLRETURN rc)
{
                  char *rcMsgText='\0';
#if 0
/* create meaningful text for rc */
switch (rc) {

         /* warnings */
         case MMDB_WARN_ALREADY_ENABLED:
                  rcMsgText = "MMDB_WARN_ALREADY_ENABLED";
                  break;
         case MMDB_WARN_FILE_NOT_REFERENCED:
                  rcMsgText = "MMDB_WARN_FILE_NOT_REFERENCED";
                  break;
         case MMDB_WARN_REENABLED_TABLESPACE:
                  rcMsgText = "MMDB_WARN_REENABLED_TABLESPACE";
                  break;

         /* errors */
         case MMDB_RC_INVALID_INPUT:
                  rcMsgText = "MMDB_RC_INVALID_INPUT";
                  break;
         case MMDB_RC_MALLOC:
                  rcMsgText = "MMDB_RC_MALLOC, malloc failed";
                  break;
         case MMDB_RC_OPEN_FILE_FAIL:
                  rcMsgText = "MMDB_RC_OPEN_FILE_FAIL, malloc failed";
                  break;
         case MMDB_RC_READ_FILE_FAIL:
                  rcMsgText = "MMDB_RC_READ_FILE_FAIL, malloc failed";
                  break;
         case MMDB_RC_WRITE_FILE_FAIL:
                  rcMsgText = "MMDB_RC_WRITE_FILE_FAIL, malloc failed";
                  break;
         case MMDB_RC_INVALID_HANDLE:
                  rcMsgText = "MMDB_RC_INVALID_HANDLE, the handle content is invalid";
                  break;
         case MMDB_RC_NO_AUTH:
                  rcMsgText = "MMDB_RC_NO_AUTH, user has no auth to call the api";
                  break;
         case MMDB_RC_BIND_FAIL:
                  rcMsgText = "MMDB_RC_BIND_FAIL";
                  break;
         case MMDB_RC_UNKNOWN_FORMAT:
                  rcMsgText = "MMDB_RC_UNKNOWN_FORMAT";
                  break;
         case MMDB_RC_FORMAT_CONVERSION_FAIL:
                  rcMsgText = "MMDB_RC_FORMAT_CONVERSION_FAIL";
                  break;
         case MMDB_RC_ENV_NOT_SETUP:
                  rcMsgText = "MMDB_RC_ENV_NOT_SETUP";
                  break;
         case MMDB_RC_IMPORT_ENV_NOT_SETUP:
                  rcMsgText = "MMDB_RC_IMPORT_ENV_NOT_SETUP";
                  break;
         case MMDB_RC_STORE_ENV_NOT_SETUP:
                  rcMsgText = "MMDB_RC_STORE_ENV_NOT_SETUP";
                  break;
         case MMDB_RC_EXPORT_ENV_NOT_SETUP:
                  rcMsgText = "MMDB_RC_EXPORT_ENV_NOT_SETUP";
                  break;
         case MMDB_RC_TEMP_ENV_NOT_SETUP:
                  rcMsgText = "MMDB_RC_TEMP_ENV_NOT_SETUP";
                  break;
         /* MMDB_RC_BROWSER_ENV_NOT_SET_UP and MMDB_RC_PLAYER_ENV_NOT_SET_UP
                 return the same number */
         case MMDB_RC_BROWSER_ENV_NOT_SET_UP:
                  rcMsgText = "MMDB_RC_BROWSER_ENV_NOT_SET_UP or MMDB_RC_PLAYER_ENV_NOT_SET_UP";
                  break;
         case MMDB_RC_CANT_RESOLVE_FILENAME:
                  rcMsgText = "MMDB_RC_CANT_RESOLVE_FILENAME";
                  break;
         case MMDB_RC_CANT_RESOLVE_IMPORT_FILE:
                  rcMsgText = "MMDB_RC_CANT_RESOLVE_IMPORT_FILE";
                  break;
         case MMDB_RC_CANT_RESOLVE_STORE_FILE:
                  rcMsgText = "MMDB_RC_CANT_RESOLVE_STORE_FILE";
                  break;
         case MMDB_RC_CANT_RESOLVE_EXPORT_FILE:
                  rcMsgText = "MMDB_RC_CANT_RESOLVE_EXPORT_FILE";
                  break;
         case MMDB_RC_CANT_CREATE_TMP_FILE:
                  rcMsgText = "MMDB_RC_CANT_CREATE_TMP_FILE";
                  break;
         case MMDB_RC_CANT_OPEN_IMPORT_FILE:
                  rcMsgText = "MMDB_RC_CANT_OPEN_IMPORT_FILE, can't open import file";
                  break;
         case MMDB_RC_CANT_OPEN_STORE_FILE:
                  rcMsgText = "MMDB_RC_CANT_OPEN_STORE_FILE";
                  break;
         case MMDB_RC_CANT_OPEN_EXPORT_FILE:
                  rcMsgText = "MMDB_RC_CANT_OPEN_EXPORT_FILE";
                  break;
         case MMDB_RC_CANT_OPEN_TMP_FILE:
                  rcMsgText = "MMDB_RC_CANT_OPEN_TMP_FILE";
                  break;
         case MMDB_RC_WRONG_SIGNATURE:
                  rcMsgText = "MMDB_RC_WRONG_SIGNATURE, extender defined with another UDT";
                  break;
         case MMDB_RC_NOT_ENABLED:
                  rcMsgText = "MMDB_RC_NOT_ENABLED, db or table not enabled yet";
                  break;
         case MMDB_RC_GEN_TRIGGER_NAME:
                  rcMsgText = "MMDB_RC_GEN_TRIGGER_NAME, can't generate unique trigger name";
                  break;
         case MMDB_RC_NOTHING_TO_IMPORT:
                  rcMsgText = "MMDB_RC_NOTHING_TO_IMPORT, both filename and blob are null";
                  break;
         case MMDB_RC_CANT_COPY_BLOB_2_FILE:
                  rcMsgText = "MMDB_RC_CANT_COPY_BLOB_2_FILE";
                  break;
         case MMDB_RC_ALREADY_ENABLED_NO_METATABLE:
                  rcMsgText = "MMDB_RC_ALREADY_ENABLED_NO_METATABLE, table was enable. but metatable missing";
                  break;
         case MMDB_RC_CREATE_UNIQUE_TRIGGER:
                  rcMsgText = "MMDB_RC_CREATE_UNIQUE_TRIGGER";
                  break;
         case MMDB_RC_COLUMN_DOESNOT_EXIST:
                  rcMsgText = "MMDB_RC_COLUMN_DOESNOT_EXIST";
                  break;
         case MMDB_RC_INCOMPATIBLE_COLUMN_TYPE:
                  rcMsgText = "MMDB_RC_INCOMPATIBLE_COLUMN_TYPE";
                  break;
         case MMDB_RC_EXEC_RPC:
                  rcMsgText = "MMDB_RC_EXEC_RPC";
                  break;
         case MMDB_RC_TABLE_DOESNOT_EXIST:
                  rcMsgText = "MMDB_RC_TABLE_DOESNOT_EXIST";
                  break;
         case MMDB_RC_COLUMN_NOT_ENABLED:
                  rcMsgText = "MMDB_RC_COLUMN_NOT_ENABLED";
                  break;
         default:
                  rcMsgText = "not known";
                  break;
         }
#endif

/* print rc, rcMsgText */
printf("rc=%d, rcMsgText=%s\n", rc, rcMsgText);

}

SQLRETURN
print_results(SQLHSTMT hstmt)
{
         SQLCHAR         colname[32];
         SQLSMALLINT     coltype;
         SQLSMALLINT     colnamelen;
         SQLSMALLINT     nullable;
         SQLUINTEGER     collen[MAXCOLS];
         SQLSMALLINT     scale;
         SQLINTEGER      outlen[MAXCOLS];
         SQLCHAR        *data[MAXCOLS];
         SQLCHAR         errmsg[256];
         SQLRETURN       rc;
         SQLSMALLINT     nresultcols;
         SQLUSMALLINT    j;
         int             i;   
         SQLINTEGER      displaysize;

         SQLSMALLINT     buflen=sizeof(colname);

         rc = SQLNumResultCols(hstmt, &nresultcols);
         cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);

         for (i = 0; i < nresultcols; i++) {
                  j = i+1;
                  SQLDescribeCol(hstmt, j, colname, buflen,
                                &colnamelen, &coltype, 
                                &collen[i], &scale, &nullable);

                  /* get display length for column */
                  SQLColAttributes(hstmt, j, SQL_DESC_DISPLAY_SIZE, (SQLPOINTER) NULL, 0,
                                (SQLSMALLINT *) NULL, (sqlint32 *)&displaysize);

                  /* limit displaysize to 78, since Comment UDF returns size of 32700 */
                  if (displaysize > 78)
                                displaysize = 78;

                  /*
                        * set column length to max of display length, and column name
                        * length.  Plus one byte for null terminator
                        */
                  collen[i] = max(displaysize, strlen((char *) colname)) + 1;

                  printf("%-*.*s", (int)collen[i], (int)collen[i], colname);

                  /* allocate memory to bind column                             */
                  data[i] = (SQLCHAR *) malloc((int)collen[i]);

                  /* bind columns to program vars, converting all types to CHAR */
                  rc = SQLBindCol(hstmt, j, SQL_C_CHAR, data[i], collen[i], &outlen[i]
);
         }
         printf("\n");
         /* display result rows                                            */
         while ((rc = SQLFetch(hstmt)) == SQL_SUCCESS) {
                  errmsg[0] = '\0';
                  for (i = 0; i < nresultcols; i++) {
                                /* Check for NULL data */
                                if (outlen[i] == SQL_NULL_DATA)
                                         printf("%-*.*s", (int)collen[i], (int)collen[i], "NULL");
                                else
                                {   /* Build a truncation message for any columns truncated */
                                         if (outlen[i] >= collen[i]) {
                                                  sprintf((char *) errmsg + strlen((char *) errmsg),
                                                                         "%d chars truncated, col %d\n",
                                                                         (int)outlen[i] - collen[i] + 1, i + 1);
                                         }
                                         /* Print column */
                                         printf("%-*.*s", (int)collen[i], (int)collen[i], data[i]);
                                 }
                  }                       /* for all columns in this row  */

                  printf("\n%s", errmsg); /* print any truncation messages    */
         }                           /* while rows to fetch */

         if ((rc != SQL_NO_DATA_FOUND) && (rc != SQL_SUCCESS)) {
                 cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
         }

         /* free data buffers                                              */
         for (i = 0; i < nresultcols; i++) {
                  free(data[i]);
         }

         return(SQL_SUCCESS);

}                               /* end print_results */
