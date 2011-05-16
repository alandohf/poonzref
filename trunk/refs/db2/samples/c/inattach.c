/****************************************************************************
** Licensed Materials - Property of IBM
** 
** Governed under the terms of the International
** License Agreement for Non-Warranted Sample Code.
**
** (C) COPYRIGHT International Business Machines Corp. 1996 - 2002
** All Rights Reserved.
**
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
*****************************************************************************
**
** SOURCE FILE NAME: inattach.c
**
** SAMPLE: Attach to and detach from an instance
**          
** DB2 APIs USED:
**         sqleatcp -- ATTACH AND CHANGE PASSWORD
**         sqleatin -- ATTACH TO INSTANCE
**         sqledtin -- DETACH FROM INSTANCE         
**         
** STRUCTURES USED:
**         sqlca 
**
** OUTPUT FILE: inattach.out (available in the online documentation)
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

int InstAttach(char *, char *, char *);
int InstPasswordChange(char *, char *, char *);
int InstDetach(char *);

int main(int argc, char *argv[])
{
  int rc = 0;
  struct sqlca sqlca;
  char nodeName[SQL_INSTNAME_SZ + 1];
  char user[USERID_SZ + 1];
  char pswd[PSWD_SZ + 1];

  /* check the command line arguments */
  if (argc != 4)
  {
    printf(
      "\nUSAGE: %s nodeName(or currentLocalInstanceName) user password\n",
      argv[0]);
    return 1;
  }
  strcpy(nodeName, argv[1]);
  strcpy(user, argv[2]);
  strcpy(pswd, argv[3]);

  printf("\nTHIS SAMPLE SHOWS HOW TO ATTACH TO/DETACH FROM AN INSTANCE.\n");

  rc = InstAttach(nodeName, user, pswd);
  rc = InstPasswordChange(nodeName, user, pswd);
  rc = InstDetach(nodeName);

  return 0;
} /* main */

int InstAttach(char *nodeName, char *user, char *pswd)
{
  struct sqlca sqlca;

  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE DB2 API:\n");
  printf("  sqleatin -- ATTACH TO INSTANCE\n");
  printf("TO ATTACH TO AN INSTANCE:\n");

  /* attach instance */
  printf("    instance alias or name: %s\n", nodeName);
  printf("      - name is specified for current local instance\n");
  printf("    user ID               : %s\n", user);
  printf("    password              : %s\n", pswd);

  /* attach to an instance */
  sqleatin(nodeName, user, pswd, &sqlca);
  DB2_API_CHECK("Instance -- Attach");

  return 0;
} /* InstAttach */

int InstPasswordChange(char *nodeName, char *user, char *pswd)
{
  struct sqlca sqlca;
  char *newPassword = NULL;

  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE DB2 API:\n");
  printf("  sqleatcp -- ATTACH AND CHANGE PASSWORD\n");
  printf("TO CHANGE THE PASSWORD USED TO ATTACH TO AN INSTANCE:\n");

  /* change password in attach to instance */
  printf("\n  Change the password and attach to the instance.\n");
  printf("    instance alias or name: %s\n", nodeName);
  printf("      - name is specified for current local instance\n");
  printf("    user ID               : %s\n", user);
  printf("    password              : %s\n", pswd);
  printf("    new password          : keep the same password\n");

  /* attach and change password */
  sqleatcp(nodeName, user, pswd, newPassword, &sqlca);
  DB2_API_CHECK("Instance Password -- Change");

  return 0;
} /* InstPasswordChange */

int InstDetach(char *nodeName)
{
  struct sqlca sqlca;

  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE DB2 API:\n");
  printf("  sqledtin -- DETACH FROM INSTANCE\n");
  printf("TO DETACH FROM AN INSTANCE:\n");

  /* detach instance */
  printf("\n  Detach from the instance.\n");
  printf("    instance alias or name: %s\n", nodeName);
  printf("      - name is specified for current local instance\n");

  /* detach from an instance */
  sqledtin(&sqlca);
  DB2_API_CHECK("Instance -- Detach");

  return 0;
} /* InstDetach */

