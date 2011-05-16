/****************************************************************************
** Licensed Materials - Property of IBM
** 
** Governed under the terms of the International
** License Agreement for Non-Warranted Sample Code.
**
** (C) COPYRIGHT International Business Machines Corp. 1998 - 2002
** All Rights Reserved.
**
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
*****************************************************************************
**
** SOURCE FILE NAME: dbmigrat.c
**
** SAMPLE: Migrate a database
**
** DB2 APIs USED:
**         sqlemgdb -- MIGRATE DATABASE
**
** STRUCTURES USED:
**         sqlca
**
** OUTPUT FILE: dbmigrat.out (available in the online documentation)
*****************************************************************************
**
** For more information on the sample programs, see the README file.
**
** For information on developing C applications, see the Application
** Development Guide.
**
** For information on DB2 APIs, see the Administrative API Reference.
**
** For the latest information on programming, building, and running DB2 
** applications, visit the DB2 application development website: 
**     http://www.software.ibm.com/data/db2/udb/ad
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlutil.h>
#include <sqlenv.h>
#include "utilapi.h"

int DbMigrate(char *, char *, char *);

int main(int argc, char *argv[])
{
  int rc = 0;

  char dbAlias[SQL_ALIAS_SZ + 1];
  char user[USERID_SZ + 1];
  char pswd[PSWD_SZ + 1];

  /* check the command line arguments */
  rc = CmdLineArgsCheck1(argc, argv, dbAlias, user, pswd);
  if (rc != 0)
  {
    return rc;
  }

  printf("\nTHIS SAMPLE SHOWS HOW TO MIGRATE A DATABASE.\n");

  rc = DbMigrate(dbAlias, user, pswd);

  return 0;
} /* main */

int DbMigrate(char *dbAlias, char *user, char *pswd)
{
  struct sqlca sqlca;

  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE DB2 API:\n");
  printf("  sqlemgdb -- MIGRATE DATABASE\n");
  printf("TO MIGRATE A DATABASE TO CURRENT FORMATS.\n");

  printf("\n  Migrate the \"%s\" database.\n", dbAlias);

  /* migrate the database */
  sqlemgdb(dbAlias, user, pswd, &sqlca);
  if (sqlca.sqlcode != SQLE_RC_MIG_OK)
  {
    DB2_API_CHECK("Database -- Migrate");
  }

  return 0;
} /* DbMigrate */

