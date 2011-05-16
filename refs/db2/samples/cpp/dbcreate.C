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
** SOURCE FILE NAME: dbcreate.C
**
** SAMPLE: Create and drop databases
**
** DB2 APIs USED:
**         sqlecrea -- CREATE DATABASE
**         sqledrpd -- DROP DATABASE
**      
** STRUCTURES USED:
**         sqlca
**         SQLEDBTERRITORYINFO
**         sqledbdesc
**
** OUTPUT FILE: dbcreate.out (available in the online documentation)
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

#include <string.h>
#include <sqle819a.h>
#include <sqlutil.h>
#include <sqlenv.h>
#include "utilapi.h"
#if ((__cplusplus >= 199711L) && !defined DB2HP && !defined DB2AIX) || \
    (DB2LINUX && (__LP64__ || (__GNUC__ >= 3)) )
   #include <iostream>
   using namespace std; 
#else
   #include <iostream.h>
#endif

class DbCreate
{
  public:
    static int Create();
    static int Drop();
};

int DbCreate::Create()
{
  struct sqlca sqlca;
  char dbName[SQL_DBNAME_SZ + 1];
  char dbLocalAlias[SQL_ALIAS_SZ + 1];
  char dbPath[SQL_PATH_SZ + 1];
  struct sqledbdesc dbDescriptor;
  SQLEDBTERRITORYINFO territoryInfo;

  cout << "\n-----------------------------------------------------------";
  cout << "\nUSE THE DB2 API:" << endl;
  cout << "  sqlecrea -- CREATE DATABASE" << endl;
  cout << "TO CREATE A NEW DATABASE:" << endl;

  // set new database parameters
  strcpy(dbName, "dbcreate");
  strcpy(dbLocalAlias, "dbcreate");
  strcpy(dbPath, "");

  strcpy(dbDescriptor.sqldbdid, SQLE_DBDESC_2);
  dbDescriptor.sqldbccp = 0;
  dbDescriptor.sqldbcss = SQL_CS_USER;
  memcpy(dbDescriptor.sqldbudc, sqle_819_500, SQL_CS_SZ);
  strcpy(dbDescriptor.sqldbcmt, "comment for database");
  dbDescriptor.sqldbsgp = 0;
  dbDescriptor.sqldbnsg = 10;
  dbDescriptor.sqltsext = -1;
  dbDescriptor.sqlcatts = NULL;
  dbDescriptor.sqlusrts = NULL;
  dbDescriptor.sqltmpts = NULL;

  strcpy(territoryInfo.sqldbcodeset, "ISO8859-1");
  strcpy(territoryInfo.sqldblocale, "C");

  cout << "\n  Create a [remote] database and catalog it locally:" << endl;
  cout << "    database name       : " << dbName << endl;
  cout << "    local database alias: " << dbLocalAlias << endl;

  // create a new database
  sqlecrea(dbName,
           dbLocalAlias,
           dbPath,
           &dbDescriptor,
           &territoryInfo,
           '\0',
           NULL,
           &sqlca);
  DB2_API_CHECK("Database -- Create");

  return 0;
} //DbCreate::Create

int DbCreate::Drop()
{
  struct sqlca sqlca;
  char dbLocalAlias[SQL_ALIAS_SZ + 1];

  cout << "\n-----------------------------------------------------------";
  cout << "\nUSE THE DB2 API:" << endl;
  cout << "  sqledrpd -- DROP DATABASE" << endl;
  cout << "TO DROP A DATABASE:" << endl;

  strcpy(dbLocalAlias, "dbcreate");
  cout << "\n  Drop a [remote] database and uncatalog it locally.";
  cout << "\n    local database alias: " << dbLocalAlias << endl;

  // drop a database
  sqledrpd(dbLocalAlias, &sqlca);
  DB2_API_CHECK("Database -- Drop");

  return 0;
} //DbCreate::Drop

int main(int argc, char *argv[])
{
  int rc = 0;
  CmdLineArgs check;
  DbCreate create;
  Instance inst;

  // check the command line arguments
  rc = check.CmdLineArgsCheck2(argc, argv, inst);
  if (rc != 0)
  {
    return rc;
  }

  cout << "\nTHIS SAMPLE SHOWS HOW TO CREATE/DROP A DATABASE." << endl;

  // attach to a local or remote instance
  rc = inst.Attach();
  if (rc != 0)
  {
    return rc;
  }

  rc = create.Create();
  rc = create.Drop();

  // detach from a local or remote instance
  rc = inst.Detach();
  if (rc != 0)
  {
    return rc;
  }

  return 0;
} //main

