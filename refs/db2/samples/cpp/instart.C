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
** SOURCE FILE NAME: instart.C
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
** For information on developing C++ applications, see the Application
** Development Guide.
**
** For information on DB2 APIs, see the Administrative API Reference.
**
** For the latest information on programming, compiling, and running DB2
** applications, visit the DB2 application development website at
**     http://www.software.ibm.com/data/db2/udb/ad
****************************************************************************/

#include <sqlenv.h>
#include <db2ApiDf.h>
#include "utilapi.h"
#if ((__cplusplus >= 199711L) && !defined DB2HP && !defined DB2AIX) || \
    (DB2LINUX && (__LP64__ || (__GNUC__ >= 3)) )
   #include <iostream>
   using namespace std; 
#else
   #include <iostream.h>
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

class InStart
{
  public:
    int CurrentLocalServerInstanceStop();
    int CurrentLocalServerInstanceStart();
};

int InStart::CurrentLocalServerInstanceStop()
{
  struct sqlca sqlca;
  struct db2InstanceStopStruct instanceStopStruct;

  cout << "\n-----------------------------------------------------------";
  cout << "\nUSE THE DB2 APIs:" << endl;
  cout << "  sqlefrce -- FORCE APPLICATION" << endl;
  cout << "  db2InstanceStop -- STOP INSTANCE" << endl;
  cout << "TO STOP THE CURRENT LOCAL SERVER INSTANCE:" << endl;

  cout << "\n  Force off all applications";
  cout << " connected to all databases." << endl;

  // force off all applications connected to all databases
  sqlefrce(SQL_ALL_USERS, NULL, SQL_ASYNCH, &sqlca);
  DB2_API_CHECK("all applications -- force off");

  cout << "  Stop the current local server instance." << endl;

  instanceStopStruct.iIsRemote = FALSE;        /* is it a remote Stop?         */
  instanceStopStruct.piRemoteInstName = NULL; /* The name of the remote       */
                                             /* instance to be Stopped.       */
  instanceStopStruct.piCommData = NULL ;    /* Remote Stop structure for    */
                                             /* DAS                           */
  instanceStopStruct.piStopOpts = NULL; /* db2StopOptions          */
                                             /* structure                     */

  // stop database manager
  db2InstanceStop(db2Version900, &instanceStopStruct, &sqlca);
  DB2_API_CHECK("Current Local Server Instance -- Stop");

  return 0;
} //InStart::CurrentLocalServerInstanceStop

int InStart::CurrentLocalServerInstanceStart()
{
  struct sqlca sqlca;
  struct db2InstanceStartStruct instanceStartStruct;

  cout << "\n-----------------------------------------------------------";
  cout << "\nUSE THE DB2 API:" << endl;
  cout << "  db2InstanceStart -- START INSTANCE" << endl;
  cout << "TO START THE CURRENT LOCAL SERVER INSTANCE:" << endl;

  cout << "\n  Start the current local server instance." << endl;

  instanceStartStruct.iIsRemote = FALSE;        /* is it a remote start?         */
  instanceStartStruct.piRemoteInstName = NULL; /* The name of the remote       */
                                             /* instance to be started.       */
  instanceStartStruct.piCommData = NULL ;    /* Remote start structure for    */
                                             /* DAS                           */
  instanceStartStruct.piStartOpts = NULL; /* db2StartOptions          */
                                             /* structure                     */

  // start database manager
  db2InstanceStart(db2Version900, &instanceStartStruct, &sqlca);
  DB2_API_CHECK("Current Local Server Instance -- Start");

  return 0;
} //InStart::CurrentLocalServerInstanceStart

int main(int argc, char *argv[])
{
  int rc = 0;
  InStart start;

  // check the command line arguments
  if (argc != 1)
  {
    cout << "\nUSAGE: " << argv[0] << endl;
    return 1;
  }

  cout << "\nTHIS SAMPLE SHOWS HOW TO STOP/START THE CURRENT LOCAL INSTANCE."
       << endl;

  rc = start.CurrentLocalServerInstanceStop();
  rc = start.CurrentLocalServerInstanceStart();

  return 0;
} //main

