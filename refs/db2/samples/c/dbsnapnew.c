/****************************************************************************
** Licensed Materials - Property of IBM
** 
** Governed under the terms of the International
** License Agreement for Non-Warranted Sample Code.
**
** (C) COPYRIGHT International Business Machines Corp. 1995 - 2006
** All Rights Reserved.
**
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
*****************************************************************************
**
** SOURCE FILE NAME: dbsnapnew.c 
**
** SAMPLE: Capture a snapshot at the database level
**          
**         This sample creates an instance attachment, and calls functions  
**         in utilsnap.c to capture a database-level snapshot and print
**         the monitor data. 
**
**         In order to access database-level monitor data, you must
**         connect to the relevant database before you run this sample.
**
** DB2 APIs USED:
**         db2GetSnapshot -- Get Snapshot
**
** STRUCTURES USED:
**         sqlma
**
** OUTPUT FILE: dbsnap.out (available in the online documentation)
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

#include "utilsnap.c"

int GetDatabaseSnapshot(void);

int main(int argc, char *argv[])
{
  int rc = 0;
  char nodeName[SQL_INSTNAME_SZ + 1];
  char user[USERID_SZ + 1];
  char pswd[PSWD_SZ + 1];

  /* check the command line arguments */
  rc = CmdLineArgsCheck2(argc, argv, nodeName, user, pswd);
  if (rc != 0) return rc;

  printf("\nTHIS SAMPLE SHOWS HOW TO GET A DATABASE LEVEL SNAPSHOT.\n");

  /* attach to a local or remote instance */
  rc = InstanceAttach(nodeName, user, pswd);
  if (rc != 0) return rc;

  /* turn on all the monitor switches */
  rc = TurnOnAllMonitorSwitches();
  if (rc != 0) return rc;

  /* capture a snapshot at the database level and print the monitor data */
  rc = GetDatabaseSnapshot();

  /* detach from the local or remote instance */
  rc = InstanceDetach(nodeName);

  return rc;
} /* main */

/***************************************************************************/
/* GetDatabaseSnapshot                                                     */
/* Construct new request stream with values that tell the db2GetSnapshot   */
/* API capture a database-level snapshot. Then pass the sqlma to the       */
/* GetSnapshot function in utilsnap.c, which captures the snapshot (using  */
/* the db2GetSnapshot API) and prints the monitor data.                    */
/***************************************************************************/
int GetDatabaseSnapshot(void)
{
  int rc = 0;                   /* return code */
  db2AddSnapshotRqstData snapReq;
  struct sqlca sqlca;
  char dbname[10];

  strcpy(dbname , "SAMPLE");
  memset(&snapReq, 0, sizeof(snapReq));
  memset(&sqlca  , 0, sizeof(sqlca));

  /* Database Snapshots */
  snapReq.pioRequestData= NULL;
  snapReq.iRequestType  = SQLMA_DBASE_ALL;
  rc = db2AddSnapshotRequest(db2Version900, &snapReq, &sqlca);
  sqlmCheckRC(rc);

  snapReq.iRequestType  = SQLMA_BUFFERPOOLS_ALL;
  rc = db2AddSnapshotRequest(db2Version900, &snapReq, &sqlca);
  sqlmCheckRC(rc);

  snapReq.iRequestType  = SQLMA_DBASE_REMOTE_ALL;
  rc = db2AddSnapshotRequest(db2Version900, &snapReq, &sqlca);
  sqlmCheckRC(rc);

  snapReq.iRequestType  = SQLMA_DBASE;
  snapReq.iQualType     = SQLM_INSTREAM_ELM_DBNAME;
  snapReq.piQualData    = (void *) dbname;
  rc = db2AddSnapshotRequest(db2Version900, &snapReq, &sqlca);
  sqlmCheckRC(rc);

  snapReq.iRequestType  = SQLMA_DBASE_APPLS;
  snapReq.iQualType     = SQLM_INSTREAM_ELM_DBNAME;
  snapReq.piQualData    = (void *) dbname;
  rc = db2AddSnapshotRequest(db2Version900, &snapReq, &sqlca);
  sqlmCheckRC(rc);

  snapReq.iRequestType  = SQLMA_DBASE_TABLESPACES;
  snapReq.iQualType     = SQLM_INSTREAM_ELM_DBNAME;
  snapReq.piQualData    = (void *) dbname;
  rc = db2AddSnapshotRequest(db2Version900, &snapReq, &sqlca);
  sqlmCheckRC(rc);

  snapReq.iRequestType  = SQLMA_DBASE_LOCKS;
  snapReq.iQualType     = SQLM_INSTREAM_ELM_DBNAME;
  snapReq.piQualData    = (void *) dbname;
  rc = db2AddSnapshotRequest(db2Version900, &snapReq, &sqlca);
  sqlmCheckRC(rc);

  snapReq.iRequestType  = SQLMA_DBASE_BUFFERPOOLS;
  snapReq.iQualType     = SQLM_INSTREAM_ELM_DBNAME;
  snapReq.piQualData    = (void *) dbname;
  rc = db2AddSnapshotRequest(db2Version900, &snapReq, &sqlca);
  sqlmCheckRC(rc);

  snapReq.iRequestType  = SQLMA_DBASE_TABLES;
  snapReq.iQualType     = SQLM_INSTREAM_ELM_DBNAME;
  snapReq.piQualData    = (void *) dbname;
  rc = db2AddSnapshotRequest(db2Version900, &snapReq, &sqlca);
  sqlmCheckRC(rc);

  snapReq.iRequestType  = SQLMA_DYNAMIC_SQL;
  snapReq.iQualType     = SQLM_INSTREAM_ELM_DBNAME;
  snapReq.piQualData    = (void *) dbname;
  rc = db2AddSnapshotRequest(db2Version900, &snapReq, &sqlca);
  sqlmCheckRC(rc);

  rc = GetSnapshotNew(&snapReq);

  return rc;
} /* GetDatabaseSnapshot */
