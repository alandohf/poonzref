//
int main(int argc, char *argv[])
//

  char nodeName[SQL_INSTNAME_SZ + 1];
//

  EXEC SQL BEGIN DECLARE SECTION;
    char dbAlias[15];
    char user[128 + 1];
    char pswd[15];
  EXEC SQL END DECLARE SECTION;
//  
  printf("\n");

//
int DbConnect(char dbAlias[], char user[], char pswd[])
//

  struct sqlca sqlca;
//
  struct db2RestartDbStruct dbRestartParam;
  dbRestartParam.piDatabaseName = dbAlias;
  dbRestartParam.piUserId = user;
  dbRestartParam.piPassword = pswd;
  dbRestartParam.piTablespaceNames = NULL;

//

  db2DatabaseRestart(db2Version900, &dbRestartParam, &sqlca);

//
  db2CfgParam cfgParameters[2]; /* to save the DB Config. */
  db2Cfg cfgStruct;
  /* initialize cfgStruct */
  cfgStruct.numItems = 2;
  cfgStruct.paramArray = cfgParameters;
  cfgStruct.flags = db2CfgDatabase | db2CfgDelayed;
  cfgStruct.dbname = dbAlias;

  /* save DB. Config. */
  rc = LocalOrRemoteDbConfigSave(cfgStruct);


  /* initialize paramArray */
  cfgStruct.paramArray[0].flags = 0;
  cfgStruct.paramArray[0].token = SQLF_DBTN_TSM_OWNER;
  cfgStruct.paramArray[0].ptrvalue = (char *)malloc(sizeof(char) * 65);
  cfgStruct.paramArray[1].flags = 0;
  cfgStruct.paramArray[1].token = SQLF_DBTN_MAXAPPLS;
  cfgStruct.paramArray[1].ptrvalue = (char *)malloc(sizeof(sqluint16));

//

  *(sqluint16 *)(cfgParameters[1].ptrvalue) = 50;

  /* free the memory allocated */
  cfgParameters[0].ptrvalue = (char *)malloc(sizeof(char) * 65);
  cfgParameters[1].ptrvalue = (char *)malloc(sizeof(sqluint16));
...

  free(cfgParameters[0].ptrvalue);
  free(cfgParameters[1].ptrvalue);

//
  switch (argc)
  {
    case 1:
      strcpy(dbAlias, "sample");
      strcpy(user, "");
      strcpy(pswd, "");
      break;
    case 2:
      strcpy(dbAlias, argv[1]);
      strcpy(user, "");
      strcpy(pswd, "");
      break;
    case 4:
      strcpy(dbAlias, argv[1]);
      strcpy(user, argv[2]);
      strcpy(pswd, argv[3]);
      break;
    default:
      printf("\nUSAGE: %s [dbAlias [userid passwd]]\n",
             argv[0]);
      rc = 1;
      break;
  }
  
  

int DbConn(char paramDbAlias[], char paramUser[], char paramPswd[])
{
  struct sqlca sqlca;
  int rc = 0;

  strcpy(dbAlias, paramDbAlias);
  strcpy(user, paramUser);
  strcpy(pswd, paramPswd);

  printf("\n  Connecting to '%s' database...\n", dbAlias);
  if (strlen(user) == 0)
  {
    EXEC SQL CONNECT TO :dbAlias;
    EMB_SQL_CHECK("CONNECT");
  }
  else
  {
    EXEC SQL CONNECT TO :dbAlias USER :user USING :pswd;
    EMB_SQL_CHECK("CONNECT");
  }
  printf("  Connected to '%s' database.\n", dbAlias);

  return 0;
} /* DbConn */

int DbDisconn(char *dbAlias)
{
  struct sqlca sqlca;
  int rc = 0;

  printf("\n  Disconnecting from '%s' database...\n", dbAlias);

  /* Commit all non-committed transactions to release database locks */
  EXEC SQL COMMIT;
  EMB_SQL_CHECK("COMMIT");

  EXEC SQL CONNECT RESET;
  EMB_SQL_CHECK("CONNECT RESET");

  printf("  Disconnected from '%s' database.\n", dbAlias);

  return 0;
} /* DbDisconn */


//
/* macro for embedded SQL checking */
#define EMB_SQL_CHECK(MSG_STR)                     \
SqlInfoPrint(MSG_STR, &sqlca, __LINE__, __FILE__); \
if (sqlca.sqlcode < 0)                             \
{                                                  \
  TransRollback();                                 \
  return 1;                                        \
}

/* function used in EMB_SQL_CHECK macro */
void TransRollback(void);


