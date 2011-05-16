/******************************************************************************/
/** Source File Name = sql2xml.c                                             **/
/**                                                                          **/
/** Licensed Materials - Property of IBM                                     **/
/**                                                                          **/
/** (C) COPYRIGHT International Business Machines Corp. 2001 - 2002          **/
/** All Rights Reserved.                                                     **/
/**                                                                          **/
/** US Government Users Restricted Rights - Use, duplication or              **/
/** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.        **/
/**                                                                          **/
/**                                                                          **/
/** PURPOSE:          Compose XML document from database tables using SQL    **/
/**                   mapping.                                               **/
/**                                                                          **/
/** STEPS:            Assumes database has been created                      **/
/**                   Assumes db2 bind to @dxxbind.lst and @db2cli.lst to    **/
/**                   the database.                                          **/
/**                   Assumes database is enabled with XML Extender via the  **/
/**                   "dxxamd enable_db dbname".                             **/
/**                                                                          **/
/** FUNCTIONS USED:   dxxGenXML stored procedure                             **/
/**                                                                          **/
/** CONFIGURATION:    Database already created                               **/
/**                                                                          **/
/** USAGE:            sql2xml dbname uid pwd                                 **/
/**                     the program will prompt for the database name,       **/
/**                     userid, and password if parameters are not passed in.**/
/**                     Use the userid and password that created the         **/
/**                     database.                                            **/
/**                                                                          **/
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "sqlsystm.h"
#include "sqludf.h"
#include "dxx.h"
#include "utility.h"    /* utility functions */

int
main(int argc, char* argv[])
{
        SQLHENV henv = SQL_NULL_HENV;
        SQLHDBC hdbc = SQL_NULL_HDBC;
        SQLHSTMT hstmt = SQL_NULL_HSTMT;
        SQLCHAR uid[18+1];
        SQLCHAR pwd[30+1];
        SQLCHAR dbName[SQL_MAX_DSN_LENGTH+1];
        SQLCHAR buffer[500];
        SQLCHAR szColName[33];
        SQLRETURN rc = SQL_SUCCESS;
        SQLINTEGER sqlcode = 0, cbColDef;
        char orderTable[10] = "order_tab";
        char partTable[9] = "part_tab";
        char shipTable[9] = "ship_tab";
        char resultTable[11] = "RESULT_TAB";
        char program[8] = "sql2xml";
        char *step;
        sqlint32 maxRows=50, returnedRows=0, i, len=0;
        sqlint32 overrideType = NO_OVERRIDE;
        char overRide[1024];
        sqlint32 returnCode;
        SQLCHAR  data[2000];
        SQLINTEGER outlen;
        SQLUINTEGER collen=1999;
        FILE *dadFileHandle, *handle;
        sqlint32 n6, n7=5, n8=499;
        char DADbuf[100000];
        char errText[100];
        char selectString[100];
        char dadFile[100] = "/opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/order_sql.dad";


/*---- table schema ----*/

SQLCHAR szCreate1[] =
"CREATE TABLE order_tab ( \
order_key integer, customer_name varchar(16), customer_email varchar(16), \
customer_phone varchar(16))";

SQLCHAR szCreate2[] =
"CREATE TABLE part_tab ( \
part_key integer, color char(6), qty integer, price decimal(10,2), tax real, \
order_key integer)";

SQLCHAR szCreate3[] =
"CREATE TABLE ship_tab ( \
date date, mode char(6), comment varchar(128), part_key integer)";

SQLCHAR szCreate4[] =
"CREATE TABLE RESULT_TAB ( doc varchar(2000) )";

/*---- end of tables ----*/

/*---- data for rows in the table ----*/

SQLCHAR szInsertOrder1[] =
"INSERT INTO order_tab VALUES ( \
1, 'American Motors', 'parts@am.com', '800-AM-PARTS')";

SQLCHAR szInsertPart1[] =
"INSERT INTO part_tab VALUES ( \
156, 'red', 17, 17954.55, 0.02, 1)";

SQLCHAR szInsertPart2[] =
"INSERT INTO part_tab VALUES ( \
68, 'black', 36, 34850.16, 0.06, 1)";

SQLCHAR szInsertPart3[] =
"INSERT INTO part_tab VALUES ( \
128, 'red', 28, 38000.00, 0.07, 1)";

SQLCHAR szInsertShip1[] =
"INSERT INTO ship_tab VALUES ( \
'1998-03-13', 'TRUCK', 'This is the first shipment to service of AM.', 156)";

SQLCHAR szInsertShip2[] =
"INSERT INTO ship_tab VALUES ( \
'1999-01-16', 'FEDEX', 'This the second shipment to service of AM.', 156)";

SQLCHAR szInsertShip3[] =
"INSERT INTO ship_tab VALUES ( \
'1998-08-19', 'BOAT', \
'This shipment is requested by a call. from AM marketing.', 68)";

SQLCHAR szInsertShip4[] =
"INSERT INTO ship_tab VALUES ( \
'1998-08-19', 'AIR', 'This shipment is ordered by an email.', 68)";

SQLCHAR szInsertShip5[] =
"INSERT INTO ship_tab VALUES ( \
'1998-12-30', 'TRUCK', NULL, 128)";

/*---- end of data ----*/

/*---- begin table cleanup ----*/

SQLCHAR szDrop[] =
"DROP TABLE %s";

/*---- end of table cleanup ----*/

SQLCHAR szDxxGenXML[] =
"CALL db2xml.dxxGenXML (?, ?, ?, ?, ?, ?, ?, ?)";

/*---- begin xml document retrieve -----*/

SQLCHAR szSelectXML[] =
"SELECT doc FROM RESULT_TAB";

/*---- end of xml document retrieve ----*/


SQLCHAR xmlFile[257];

/*---- prompt for database name ----*/
       if (argc > 4 || (argc >=2 && strcmp(argv[1],"?")== 0))
         {
           printf("Syntax for sq12xml - composing xml document using SQL mapping: \n"
                  "   sql2xml database_name userid password\n");
           exit(0);
         }

       if (argc == 4) {
         strcpy((char *)dbName, argv[1]);
         strcpy((char *)uid   , argv[2]);
         strcpy((char *)pwd   , argv[3]);
         }
       else {
         printf("Enter database name:\n");
         gets((char *) dbName);

        printf("Enter userid:\n");
         gets((char *) uid);
         printf("Enter password:\n");
         gets((char *) pwd);
         }

/*---- connect to the database ----*/
        rc = cliInitialize(&henv, &hdbc, dbName, uid, pwd);
        cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);
        if (rc < 0) goto SERROR;

/*---- allocate SQL statement ----*/
        rc = SQLAllocHandle(SQL_HANDLE_STMT,hdbc, &hstmt);
        cliCheckError(SQL_NULL_HENV, hdbc, SQL_NULL_HSTMT, rc);

/*---- create tables ----*/
        rc = SQLExecDirect(hstmt, szCreate1, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Order table created\n");

        rc = SQLExecDirect(hstmt, szCreate2, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Part table created\n");

        rc = SQLExecDirect(hstmt, szCreate3, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);     
        printf("Ship table created\n");

        rc = SQLExecDirect(hstmt, szCreate4, SQL_NTS); 
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Result table created\n");
/*---- end of table create ----*/

/*---- import data into database ----*/
        rc = SQLExecDirect(hstmt, szInsertOrder1, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Row 1 inserted into order table\n");

        rc = SQLExecDirect(hstmt, szInsertPart1, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Row 1 inserted into part table\n");

        rc = SQLExecDirect(hstmt, szInsertPart2, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Row 2 inserted into part table\n");

        rc = SQLExecDirect(hstmt, szInsertPart3, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Row 3 inserted into part table\n");

        rc = SQLExecDirect(hstmt, szInsertShip1, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Row 1 inserted into ship table\n");

        rc = SQLExecDirect(hstmt, szInsertShip2, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Row 2 inserted into ship table\n");

        rc = SQLExecDirect(hstmt, szInsertShip3, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Row 3 inserted into ship table\n");

        rc = SQLExecDirect(hstmt, szInsertShip4, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Row 4 inserted into ship table\n");

        rc = SQLExecDirect(hstmt, szInsertShip5, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Row 5 inserted into ship table\n");

        /* commit changes to database */
        rc = SQLTransact(henv, hdbc, SQL_COMMIT);
        cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);
/*---- end of data import ----*/

/*---- call dxxGenXML stored procedure to compose XML document ----*/
        dadFileHandle = fopen (dadFile,"r");
        if (dadFileHandle == (FILE *) NULL) {
           printf("***** ERROR: Can't access DAD file *****\n");
           goto DROPTB;
        }

        len = fread(DADbuf, sizeof(char),100000,dadFileHandle);
        fclose(dadFileHandle);
        if (len < 100000) {
	   DADbuf[len]='\0';
           }
        else {
           printf("***** ERROR: DAD file too big *****\n");
           goto DROPTB;
           }


        overRide[0] ='\0';
        errText[0] = '\0';

        rc = SQLPrepare(hstmt, szDxxGenXML, SQL_NTS);
        cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);

        rc = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CLOB,
                100000, 0, DADbuf, 100000-1, NULL);
        cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);

        rc = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
                18, 0, resultTable, 18, NULL);
        cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);

        rc = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                4, 0, &overrideType, sizeof(overrideType), NULL);
        cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);

        rc = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                1023, 0, overRide, 1024, NULL);
        cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);

        rc = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                4, 0, &maxRows, sizeof(maxRows), NULL);
        cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);

        rc = SQLBindParameter(hstmt, 6, SQL_PARAM_OUTPUT, SQL_C_LONG, SQL_INTEGER,
                4, 0, &returnedRows, sizeof(returnedRows),&n6);
        cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);

        rc = SQLBindParameter(hstmt, 7, SQL_PARAM_OUTPUT, SQL_C_LONG, SQL_INTEGER,
                4, 0, &returnCode, sizeof(returnCode), &n7);
        cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);

        rc = SQLBindParameter(hstmt, 8, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_CHAR,
                99, 0, &errText, 100, &n8);
        cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);

        rc = SQLExecute(hstmt);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        if (returnedRows == 0)
          printf("No XML document is composed\n");
        else {
          printf("%d XML documents composed successfully\n", returnedRows);


/*---- end of dxxGenXML ----*/

/*---- retrieve composed XML document from result table ----*/

		rc = SQLExecDirect(hstmt, szSelectXML, SQL_NTS);
		cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);

        rc = SQLBindCol(hstmt, 1, SQL_C_CHAR, data, collen, &outlen);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);

        rc = SQLFetch(hstmt);
        i=1;
        while (rc == SQL_SUCCESS) {
            sprintf((char*) xmlFile, "s2xfile%d.doc", i);
            if ((handle = fopen((char*)xmlFile, "w")) == (FILE *) NULL) {
              printf("***** ERROR: Can't create file %s in the current directory *****\n", xmlFile);
              goto SERROR;
            }
            fwrite (data, 1, outlen, handle);
            printf("Retrieving composed XML document into %s\n", xmlFile);
            i++;
            rc = SQLFetch(hstmt);
        };

        if (rc != SQL_NO_DATA_FOUND)
          cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);
        }

/*---- close cursor ----*/
        rc = SQLCloseCursor(hstmt);
        cliCheckError(henv, hdbc, SQL_NULL_HSTMT, rc);

/*---- drop tables ----*/
DROPTB:
        sprintf((char*) buffer, (char*) szDrop, orderTable);
        rc = SQLExecDirect(hstmt, buffer, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Order table dropped\n");

        sprintf((char*) buffer, (char*) szDrop, partTable);
        rc = SQLExecDirect(hstmt, buffer, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Part table dropped\n");

        sprintf((char*) buffer, (char*) szDrop, shipTable);
        rc = SQLExecDirect(hstmt, buffer, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Ship table dropped\n");

        sprintf((char*) buffer, (char*) szDrop, resultTable);
        rc = SQLExecDirect(hstmt, buffer, SQL_NTS);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        printf("Result table dropped\n");
/*---- end of table drop ----*/

/*---- disconnect from database ----*/


        /* free SQL statement */
        rc = SQLFreeStmt(hstmt, SQL_DROP);
        cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);

        /* Disconnect from the database */
        rc = cliTerminate(henv, hdbc);

        printf("%s: composing XML document with SQL mapping completed successfully\n", program);
        return rc;

SERROR:
/*---- disconnect from database ----*/

        /* free SQL statement */
        if (hstmt != SQL_NULL_HSTMT) {
                rc = SQLFreeStmt(hstmt, SQL_DROP);
                cliCheckError(SQL_NULL_HENV, SQL_NULL_HDBC, hstmt, rc);
        }

        /* Disconnect from the database */
        rc = cliTerminate(henv, hdbc);

        printf("%s: composition of XML document from database tables failed\n", program);
        return rc;

} /* main() */

