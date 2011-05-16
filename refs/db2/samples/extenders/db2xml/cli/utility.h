/******************************************************************************/
/**                                                                          **/
/** Source File Name = utility.h  1.3                                        **/
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
/******************************************************************************/
#ifndef _H_UTILCLI
#define _H_UTILCLI
/*
 * Filename = utilcli.h
 *
 * Header file for utility routines.
 *
 */
#include "sqlcli1.h"
/* #include "sqlenv.h" */
/* #include "sqlcodes.h" */

/*
 *----------------------------------------------------------------------
 * Function prototypes
 *----------------------------------------------------------------------
 */

/*
 * Functions defined in utilcli.c
 */
void
cliPrintError(
        SQLHENV henv,
        SQLHDBC hdbc,
        SQLHSTMT hstmt
        );

void
cliCheckError(
        SQLHENV henv,
        SQLHDBC hdbc,
        SQLHSTMT hstmt,
        SQLRETURN frc
	);

SQLRETURN
cliInitialize(
        SQLHENV *henv,
        SQLHDBC *hdbc,
        SQLCHAR *server,
        SQLCHAR *uid,
        SQLCHAR *pwd
        );

SQLRETURN
cliTerminate(
        SQLHENV henv,
        SQLHDBC hdbc
        );

void
printMsg(
	SQLRETURN rc
	);

SQLRETURN
print_results(
	SQLHSTMT hstmt
	);

#endif /* _H_UTILCLI */
