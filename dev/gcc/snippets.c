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
          