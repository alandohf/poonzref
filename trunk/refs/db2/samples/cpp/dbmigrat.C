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
** SOURCE FILE NAME: dbmigrat.C
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
#include <sqlutil.h>
#include "utilapi.h"
#if ((__cplusplus >= 199711L) && !defined DB2HP && !defined DB2AIX) || \
    (DB2LINUX && (__LP64__ || (__GNUC__ >= 3)) )
   #include <iostream>
   using namespace std; 
#else
   #include <iostream.h>
#endif

class DbMigrat
{
  public:
    int Migrate(Db &);
  private:
    struct sqlca sqlca;
};

int DbMigrat::Migrate(Db & db)
{

  cout << "\n-----------------------------------------------------------";
  cout << "\nUSE THE DB2 API:" << endl;
  cout << "  sqlemgdb -- MIGRATE DATABASE" << endl;
  cout << "TO MIGRATE A DATABASE TO CURRENT FORMATS." << endl;

  cout << "\n  Migrate the \"" << db.getAlias() << "\" database." << endl;

  // migrate the database
  sqlemgdb(db.getAlias(), db.getUser(), db.getPswd(), &sqlca);
  if (sqlca.sqlcode != SQLE_RC_MIG_OK)
  {
    DB2_API_CHECK("Database -- Migrate");
  }

  return 0;
} //DbMigrat::Migrate

int main(int argc, char *argv[])
{
  int rc = 0;
  CmdLineArgs check;
  DbMigrat dbMigrat;
  Db db;

  // check the command line arguments
  rc = check.CmdLineArgsCheck1(argc, argv, db);
  if (rc != 0)
  {
    return rc;
  }

  cout << "\nTHIS SAMPLE SHOWS HOW TO MIGRATE A DATABASE." << endl;

  dbMigrat.Migrate(db);

  return 0;
} // main

