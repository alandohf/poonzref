static char sqla_program_id[292] = 
{
 172,0,65,69,65,77,65,73,66,65,102,81,76,88,69,98,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,13,0,65,68,77,73,78,73,
 83,84,82,65,84,79,82,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,8,0,83,81,67,32,32,32,32,32,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0
};

#include "sqladef.h"

static struct sqla_runtime_info sqla_rtinfo = 
{{'S','Q','L','A','R','T','I','N'}, sizeof(wchar_t), 0, {' ',' ',' ',' '}};


static const short sqlIsLiteral   = SQL_IS_LITERAL;
static const short sqlIsInputHvar = SQL_IS_INPUT_HVAR;


#line 1 "sqc.sqc"
       #include <stdio.h>                                                  //1
       #include <stdlib.h>
       #include <string.h>
       #include <sqlenv.h>
       #include <sqlutil.h>                                               

      
/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 7 "sqc.sqc"
                                      //2
        short id;
        char name[10];
        short dept;
        double salary;
        char hostVarStmtDyn[50];
      
/*
EXEC SQL END DECLARE SECTION;
*/

#line 13 "sqc.sqc"
                                        

      int main()                                                           
       { 
         int rc = 0;                                                       //3
         
/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 18 "sqc.sqc"
                                           //4

         /* 连接到数据库 */
         printf("\n Connecting to database...");
         
/*
EXEC SQL CONNECT TO "sample";
*/

{
#line 22 "sqc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 22 "sqc.sqc"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 22 "sqc.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 7;
#line 22 "sqc.sqc"
      sql_setdlist[0].sqldata = (void*)"sample";
#line 22 "sqc.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 22 "sqc.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 22 "sqc.sqc"
  sqlacall((unsigned short)29,4,2,0,0L);
#line 22 "sqc.sqc"
  sqlastop(0L);
}

#line 22 "sqc.sqc"
                                    // 5
         if (SQLCODE  <0)                                                  //6
         {
            printf("\nConnect Error:  SQLCODE = d%\n",SQLCODE);
            goto connect_reset;
         }
         else
         {
            printf("\n Connected to database.\n");
         }
         
         /* 使用静态 SQL 来执行 SQL 语句（查询）；将单一结果行的值复制到主变量 */

/*
EXEC SQL SELECT id, name, dept, salary
                 INTO :id, :name, :dept, :salary
                 FROM staff WHERE id = 310;
*/

{
#line 36 "sqc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 36 "sqc.sqc"
  sqlaaloc(3,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 36 "sqc.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 36 "sqc.sqc"
      sql_setdlist[0].sqldata = (void*)&id;
#line 36 "sqc.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 36 "sqc.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 10;
#line 36 "sqc.sqc"
      sql_setdlist[1].sqldata = (void*)name;
#line 36 "sqc.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 36 "sqc.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 36 "sqc.sqc"
      sql_setdlist[2].sqldata = (void*)&dept;
#line 36 "sqc.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 36 "sqc.sqc"
      sql_setdlist[3].sqltype = 480; sql_setdlist[3].sqllen = 8;
#line 36 "sqc.sqc"
      sql_setdlist[3].sqldata = (void*)&salary;
#line 36 "sqc.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 36 "sqc.sqc"
      sqlasetdata(3,0,4,sql_setdlist,0L,0L);
    }
#line 36 "sqc.sqc"
  sqlacall((unsigned short)24,1,0,3,0L);
#line 36 "sqc.sqc"
  sqlastop(0L);
}

#line 36 "sqc.sqc"

         if (SQLCODE  <0)                                                //  6 
         {
            printf("Select Error:  SQLCODE = %d\n",SQLCODE);
         }
         else
         {
            /* 将主变量值打印到标准输出 */
            printf("\n Executing a static SQL query statement, searching for\n the id value equal to 310\n");
            printf("\n ID   Name        DEPT       Salary\n");
            printf("%d   %s %d       %f\n",id,name,dept,salary);
         }
         
         strcpy(hostVarStmtDyn, "UPDATE staff  SET salary = salary + 1000 WHERE dept = 66");
         /* 使用主变量和动态 SQL 来执行 SQL 语句（操作）*/

/*
EXEC SQL PREPARE StmtDyn FROM :hostVarStmtDyn;
*/

{
#line 51 "sqc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 51 "sqc.sqc"
  sqlastls(0,hostVarStmtDyn,0L);
#line 51 "sqc.sqc"
  sqlacall((unsigned short)27,2,0,0,0L);
#line 51 "sqc.sqc"
  sqlastop(0L);
}

#line 51 "sqc.sqc"

         if (SQLCODE  <0)                                                 // 6
         {
            printf("Prepare Error:  SQLCODE = %d\n",SQLCODE);
         }
         else
         {
            
/*
EXEC SQL EXECUTE StmtDyn USING :dept;
*/

{
#line 58 "sqc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 58 "sqc.sqc"
  sqlaaloc(2,1,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 58 "sqc.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 58 "sqc.sqc"
      sql_setdlist[0].sqldata = (void*)&dept;
#line 58 "sqc.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 58 "sqc.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 58 "sqc.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 58 "sqc.sqc"
  sqlastop(0L);
}

#line 58 "sqc.sqc"
                         // 8
         }
         if (SQLCODE  <0)                                                 // 6
         {
            printf("Execute Error: SQLCODE = %d\n",SQLCODE);
         }
     
         /* 使用静态 SQL 和游标来读取已更新的行 */
         
/*
EXEC SQL DECLARE posCur1 CURSOR FOR 
            SELECT id, name, dept, salary 
            FROM staff WHERE id = 310;
*/

#line 68 "sqc.sqc"

         if (SQLCODE  <0)                                                 //6
         {
            printf("Declare Error: SQLCODE = %d\n",SQLCODE);
         }
         
/*
EXEC SQL OPEN posCur1;
*/

{
#line 73 "sqc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 73 "sqc.sqc"
  sqlacall((unsigned short)26,3,0,0,0L);
#line 73 "sqc.sqc"
  sqlastop(0L);
}

#line 73 "sqc.sqc"

         
/*
EXEC SQL FETCH posCur1 INTO :id, :name, :dept, :salary ;
*/

{
#line 74 "sqc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 74 "sqc.sqc"
  sqlaaloc(3,4,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 74 "sqc.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 74 "sqc.sqc"
      sql_setdlist[0].sqldata = (void*)&id;
#line 74 "sqc.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 74 "sqc.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 10;
#line 74 "sqc.sqc"
      sql_setdlist[1].sqldata = (void*)name;
#line 74 "sqc.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 74 "sqc.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 74 "sqc.sqc"
      sql_setdlist[2].sqldata = (void*)&dept;
#line 74 "sqc.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 74 "sqc.sqc"
      sql_setdlist[3].sqltype = 480; sql_setdlist[3].sqllen = 8;
#line 74 "sqc.sqc"
      sql_setdlist[3].sqldata = (void*)&salary;
#line 74 "sqc.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 74 "sqc.sqc"
      sqlasetdata(3,0,4,sql_setdlist,0L,0L);
    }
#line 74 "sqc.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 74 "sqc.sqc"
  sqlastop(0L);
}

#line 74 "sqc.sqc"
        // 9
         if (SQLCODE  <0)                                                // 6
         {
            printf("Fetch Error:  SQLCODE = %d\n",SQLCODE);
         }
         else
         {
            printf(" Executing an dynamic SQL statement, updating the \n salary value for the id equal to 310\n");
            printf("\n ID   Name        DEPT       Salary\n");
            printf("%d   %s %d       %f\n",id,name,dept,salary);
         }
         
         
/*
EXEC SQL CLOSE posCur1;
*/

{
#line 86 "sqc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 86 "sqc.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 86 "sqc.sqc"
  sqlastop(0L);
}

#line 86 "sqc.sqc"

         
         /* 落实事务 */
         printf("\n  Commit the transaction.\n");
         
/*
EXEC SQL COMMIT;
*/

{
#line 90 "sqc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 90 "sqc.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 90 "sqc.sqc"
  sqlastop(0L);
}

#line 90 "sqc.sqc"
                                                 //10
         if (SQLCODE  <0)                                                 //6
         {
            printf("Error:  SQLCODE =  SQLCODE = d%\n",SQLCODE);
         }
         
         /* 与数据库断开连接 */
         connect_reset :
            
/*
EXEC SQL CONNECT RESET;
*/

{
#line 98 "sqc.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 98 "sqc.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 98 "sqc.sqc"
  sqlastop(0L);
}

#line 98 "sqc.sqc"
                                       //11
            if (SQLCODE  <0)                                             // 6
            {
               printf("Connection Error:  SQLCODE = %d",SQLCODE);
            }
         return 0;
        } /* 结束 main */
//     有关样本程序
