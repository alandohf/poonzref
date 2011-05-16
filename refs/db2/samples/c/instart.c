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
** SOURCE FILE NAME: instart.c
**
** SAMPLE: Stop and start the current local instance
**
** DB2 APIs USED:
**         sqlefrce -- FORCE APPLICATION
**         db2InstanceStart -- INSTANCE START
**         db2InstanceStop -- INSTANCE STOP
**
** STRUCTURES USED:
**         sqlca
**         db2InstanceStopStruct
**         db2InstanceStartStruct
**
** OUTPUT FILE: instart.out (available in the online documentation)
*****************************************************************************
**
** For more information on the sample programs, see the README file.
**
** For information on developing C applications, see the Application
** Development Guide.
**
** For information on using SQL statements, see the SQL Reference.
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
#include <db2ApiDf.h>
#include "utilapi.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

int CurrentLocalServerInstanceStop(void);
int CurrentLocalServerInstanceStart(void);

int main(int argc, char *argv[])
{
  int rc = 0;

  /* check the command line arguments */
  if (argc != 1)
  {
    printf("\nUSAGE: %s \n", argv[0]);
    return 1;
  }

  printf("\nTHIS SAMPLE SHOWS ");
  printf("HOW TO STOP/START THE CURRENT LOCAL INSTANCE.\n");

  rc = CurrentLocalServerInstanceStop();
  rc = CurrentLocalServerInstanceStart();

  return 0;
} /* main */

int CurrentLocalServerInstanceStop(void)
{
  struct sqlca sqlca;
  struct db2InstanceStopStruct instanceStopStruct;

  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE DB2 APIs:\n");
  printf("  sqlefrce -- FORCE APPLICATION\n");
  printf("  db2InstanceStop -- STOP INSTANCE\n");
  printf("TO STOP THE CURRENT LOCAL SERVER INSTANCE:\n");

  printf("\n  Force off all applications connected to all databases.\n");

  /* force off all the appl. connected to all databases */
  sqlefrce(SQL_ALL_USERS, NULL, SQL_ASYNCH, &sqlca);
  DB2_API_CHECK("all applications -- force off");

  printf("  Stop the current local server instance.\n");

  instanceStopStruct.iIsRemote = FALSE;        /* is it a remote Stop?         */
  instanceStopStruct.piRemoteInstName = NULL; /* The name of the remote       */
                                             /* instance to be Stopped.       */
  instanceStopStruct.piCommData = NULL ;    /* Remote Stop structure for    */
                                             /* DAS                           */
  instanceStopStruct.piStopOpts = NULL; /* db2StopOptions          */
                                             /* structure                     */

  /* stop database manager */
  db2InstanceStop(db2Version900, &instanceStopStruct, &sqlca);
  DB2_API_CHECK("Current Local Server Instance -- Stop");

  return 0;
} /* CurrentLocalServerInstanceStop */

int CurrentLocalServerInstanceStart(void)
{
  struct sqlca sqlca;
  struct db2InstanceStartStruct instanceStartStruct;

  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE DB2 API:\n");
  printf("  db2InstanceStart -- START INSTANCE\n");
  printf("TO START THE CURRENT LOCAL SERVER INSTANCE:\n");

  printf("\n  Start the current local server instance.\n");

  instanceStartStruct.iIsRemote = FALSE;        /* is it a remote start?         */
  instanceStartStruct.piRemoteInstName = NULL; /* The name of the remote       */
                                             /* instance to be started.       */
  instanceStartStruct.piCommData = NULL ;    /* Remote start structure for    */
                                             /* DAS                           */
  instanceStartStruct.piStartOpts = NULL; /* db2StartOptions          */
                                             /* structure                     */

  /* start database manager */
  db2InstanceStart(db2Version900, &instanceStartStruct, &sqlca);
  DB2_API_CHECK("Current Local Server Instance -- Start");

  return 0;
} /* CurrentLocalServerInstanceStart */

