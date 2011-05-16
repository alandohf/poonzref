<?php
/****************************************************************************
** Licensed Materials - Property of IBM
**
** Governed under the terms of the International
** License Agreement for Non-Warranted Sample Code.
**
** (C) COPYRIGHT International Business Machines Corp. 1996 - 2003
** All Rights Reserved.
**
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
*****************************************************************************
**
** SOURCE FILE NAME: tbconstr.php
**
** SAMPLE: How to create, use, and drop constraints
**
** SQL STATEMENTS USED:
**         CREATE TABLE
**         DROP TABLE
**         ALTER TABLE
**         INSERT
**         DELETE
**         SELECT
**
** OUTPUT FILE: tbconstr.out (available in the online documentation)
*****************************************************************************
**
** For more information on the sample programs, see the README file.
**
** For information on developing PHP applications, see the Application
** Development Guide.
**
** For information on using SQL statements, see the SQL Reference.
**
** For the latest information on programming, building, and running DB2
** applications, visit the DB2 application development website:
**     http://www.software.ibm.com/data/db2/udb/ad
****************************************************************************/

// include the util_funcs.php file that contains the common functions
include_once("util_funcs.php");

// call the Error handling function defined in util_funcs.php
Error_handler();

// check and parse the command line arguments
CmdLineArgChk($argc, $argv, $dbname, $username, $password);

printf("\nTHIS SAMPLE SHOWS HOW TO CREATE/USE/DROP CONSTRAINTS.\n");

// connect to the database
$dbconn = DbConn($dbname, $username, $password);

// override the auto commit option
odbc_autocommit($dbconn, FALSE);

if ($dbconn != 0)
{
  // call the Cn_NOT_NULL_Show function
  Cn_NOT_NULL_Show($dbconn);
  
  // call the Cn_UNIQUE_Show function
  Cn_UNIQUE_Show($dbconn);

  //call the Cn_PRIMARY_KEY_Show function
  Cn_PRIMARY_KEY_Show($dbconn);

  // call the Cn_CHECK_Show function
  Cn_CHECK_Show($dbconn);
 
  // call the Cn_CHECK_INFO_Show function
  Cn_CHECK_INFO_Show($dbconn);

  // call the Cn_WITH_DEFAULT_Show function 
  Cn_WITH_DEFAULT_Show($dbconn);

  // call the Cn_TableDrop function
  Cn_TableDrop($dbconn);

  printf("\n#####################################################\n".
         "#    Create tables for FOREIGN KEY sample functions #\n".
         "#####################################################\n");
 
  /* call the FK_TwoTablesCreate function to create tables 
     for FOREIGN KEY sample functions */
  FK_TwoTablesCreate($dbconn);
 
  // call the Cn_FK_OnInsertShow function 
  Cn_FK_OnInsertShow($dbconn);
   
  // call the Cn_FK_ON_UPDATE_NO_ACTION_Show function
  Cn_FK_ON_UPDATE_NO_ACTION_Show($dbconn);
  
  // call the Cn_FK_ON_UPDATE_RESTRICT_Show function
  Cn_FK_ON_UPDATE_RESTRICT_Show($dbconn);
  
  // call the Cn_FK_ON_DELETE_CASCADE_Show function
  Cn_FK_ON_DELETE_CASCADE_Show($dbconn);
  
  // call the Cn_FK_ON_DELETE_SET_NULL_Show function
  Cn_FK_ON_DELETE_SET_NULL_Show($dbconn);
  
  // call the Cn_FK_ON_DELETE_NO_ACTION_Show function
  Cn_FK_ON_DELETE_NO_ACTION_Show($dbconn);

  printf("\n########################################################\n".
         "# Drop tables created for FOREIGN KEY sample functions #\n".
         "########################################################\n");

  /*  call the FK_TwoTablesDrop function to drop the tables created 
      for FOREIGN KEY sample functions */
  FK_TwoTablesDrop($dbconn);

}

// disconnect from the database
DbDisconn($dbconn);

/****************************************************************************
* Description : The Cn_TableDrop function drops the EMP_SAL table.
* Input       : ODBC Connection id
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_TableDrop($dbconn)
{
  printf("\n  DROP TABLE emp_sal\n");

  $sql = "DROP TABLE emp_sal";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  return 0;
} // Cn_TableDrop

/****************************************************************************
* Description : The FK_TwoTablesCreate function creates two tables 'dept' and
*               'emp', for illustrating the FOREIGN KEY relationship.
* Input       : ODBC connection id
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function FK_TwoTablesCreate($dbconn)
{
  printf("\n  CREATE TABLE dept(deptno CHAR(3) NOT NULL,\n".
         "                    deptname VARCHAR(20),\n".
         "                    CONSTRAINT pk_dept PRIMARY KEY(deptno))\n");

  $sql = "CREATE TABLE dept(deptno CHAR(3) NOT NULL,".
         "                    deptname VARCHAR(20),".
         "                    CONSTRAINT pk_dept PRIMARY KEY(deptno))";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  printf("\n  INSERT INTO dept VALUES('A00', 'ADMINISTRATION'),\n".
         "                         ('B00', 'DEVELOPMENT'),\n".
         "                         ('C00', 'SUPPORT')\n");

  $sql = "INSERT INTO dept VALUES('A00', 'ADMINISTRATION'),".
         "                       ('B00', 'DEVELOPMENT'),".
         "                       ('C00', 'SUPPORT')";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  printf("\n  CREATE TABLE emp(empno CHAR(4),\n".
         "                   empname VARCHAR(10),\n".
         "                   dept_no CHAR(3))\n");

  $sql = "CREATE TABLE emp(empno CHAR(4),".
         "                   empname VARCHAR(10),".
         "                   dept_no CHAR(3))";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  printf("\n  INSERT INTO emp VALUES('0010', 'Smith', 'A00'),\n".
         "                        ('0020', 'Ngan', 'B00'),\n".
         "                        ('0030', 'Lu', 'B00'),\n".
         "                        ('0040', 'Wheeler', 'B00'),\n".
         "                        ('0050', 'Burke', 'C00'),\n".
         "                        ('0060', 'Edwards', 'C00'),\n".
         "                        ('0070', 'Lea', 'C00')\n");
   
  $sql = "INSERT INTO emp VALUES('0010', 'Smith', 'A00'),".
         "                      ('0020', 'Ngan', 'B00'),".
         "                      ('0030', 'Lu', 'B00'),".
         "                      ('0040', 'Wheeler', 'B00'),".
         "                      ('0050', 'Burke', 'C00'),".
         "                      ('0060', 'Edwards', 'C00'),".
         "                      ('0070', 'Lea', 'C00')";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // commit the transaction
  odbc_commit($dbconn);

  return 0;
} // FK_TwoTablesCreate

/****************************************************************************
* Description : The FK_TwoTablesDisplay function displays the contents of the
*               'dept' and 'emp' tables.
* Input       : ODBC connection id
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function FK_TwoTablesDisplay($dbconn)
{
  printf("\n  SELECT * FROM dept\n");

  printf("    DEPTNO  DEPTNAME      \n");
  printf("    ------- --------------\n");

  $sql = "SELECT * FROM dept";

  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);

  while (odbc_fetch_row($res))
  {
    $deptno = odbc_result($res, "DEPTNO");
    $deptname = odbc_result($res, "DEPTNAME");

    printf("    %-7s %-20s\n", $deptno, $deptname);
  }

  printf("\n  SELECT * FROM emp\n");

  printf("    EMPNO EMPNAME    DEPT_NO\n");
  printf("    ----- ---------- -------\n");

  $sql = "SELECT * FROM emp";
    
  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);

  while (odbc_fetch_row($res))
  {
    $empno = odbc_result($res, "EMPNO");
    $empname = odbc_result($res, "EMPNAME");
    $dept_no = odbc_result($res, "DEPT_NO");

    printf("    %-5s %-10s", $empno, $empname);
 
    if (is_null($dept_no))
    {
      printf(" -\n");
    }
    else
    {
      printf(" %-3s\n", $dept_no);
    }
  }
 
  return 0;
} // FK_TwoTablesDisplay

/****************************************************************************
* Description : The FK_TwoTablesDrop function drops the tables 'dept' and 
*               'emp' created for illustrating the FOREIGN KEY relationship.
* Input       : ODBC connection id
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function FK_TwoTablesDrop($dbconn)
{
  printf("\n  DROP TABLE dept\n");

  $sql = "DROP TABLE dept";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  printf("  DROP TABLE emp\n");

  $sql = "DROP TABLE emp";
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // commit the transaction
  odbc_commit($dbconn);
  
  return 0;
} // FK_TwoTablesDrop

/****************************************************************************
* Description : The FK_Create function creates FOREIGN KEY relationship 
*               between the tables 'dept' and 'emp'.
* Input       : ODBC connection id and RULE CLAUSE.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function FK_Create(&$ruleClause, $dbconn)
{
  printf("\n  ALTER TABLE emp ADD CONSTRAINT fk_dept\n".
         "    FOREIGN KEY(dept_no)\n".
         "    REFERENCES dept(deptno)\n".
         "    %s\n", $ruleClause);

  $sql = "ALTER TABLE emp ADD CONSTRAINT fk_dept".
         "  FOREIGN KEY(dept_no)".
         "  REFERENCES dept(deptno)".
         "  $ruleClause";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  printf("  COMMIT\n");
 
  // commit the transaction
  odbc_commit($dbconn);

  return 0;
} // FK_Create

/****************************************************************************
* Description : The function FK_Drop drops the FOREIGN KEY constraint on the 
*               'emp' table.
* Input       : ODBC connection id
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function FK_Drop($dbconn)
{
  printf("\n  ALTER TABLE emp DROP CONSTRAINT fk_dept\n");

  $sql = "ALTER TABLE emp DROP CONSTRAINT fk_dept";
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);
  
  printf("  COMMIT\n");

  // commit the transaction
  odbc_commit($dbconn);
  
  return 0;
} // FK_Drop

/****************************************************************************
* Description : The function Cn_NOT_NULL_Show illustrates the 'NOT NULL'
*               constraint.
* Input       : ODBC connection id.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_NOT_NULL_Show($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  CREATE TABLE\n");
  printf("  INSERT\n");
  printf("  DROP TABLE\n");
  printf("TO SHOW A 'NOT NULL' CONSTRAINT.\n");

  // create table
  printf("\n  CREATE TABLE emp_sal(lastname VARCHAR(10) NOT NULL,\n".
         "                       firstname VARCHAR(10),\n".
         "                       salary DECIMAL(7, 2))\n");
  
  $sql = "CREATE TABLE emp_sal(lastname VARCHAR(10) NOT NULL,".
         "                       firstname VARCHAR(10),".
         "                       salary DECIMAL(7, 2))";
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  printf("  COMMIT\n");

  // commit the transaction
  odbc_commit($dbconn);

  // insert table
  printf("\n  INSERT INTO emp_sal VALUES(NULL, 'PHILIP', 17000.00)\n\n");
  
  $sql = "INSERT INTO emp_sal VALUES(NULL, 'PHILIP', 17000.00)";

  printf("\n**************** Expected Error ******************\n");

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");

  printf("\n  DROP TABLE emp_sal\n");
  
  $sql = "DROP TABLE emp_sal";
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  return 0;
} // Cn_NOT_NULL_Show

/****************************************************************************
* Description : The function Cn_UNIQUE_Show illustrates 'UNIQUE' constraint.
* Input       : ODBC connection id.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_UNIQUE_Show($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  CREATE TABLE\n");
  printf("  INSERT\n");
  printf("  ALTER TABLE\n");
  printf("  DROP TABLE\n");
  printf("TO SHOW A 'UNIQUE' CONSTRAINT.\n");

  // create table 
  printf("\n  CREATE TABLE emp_sal(lastname VARCHAR(10) NOT NULL,\n".
         "                       firstname VARCHAR(10) NOT NULL,\n".
         "                       salary DECIMAL(7, 2),\n".
         "  CONSTRAINT unique_cn UNIQUE(lastname, firstname))\n");
 
  $sql = "CREATE TABLE emp_sal(lastname VARCHAR(10) NOT NULL,".
         "                       firstname VARCHAR(10) NOT NULL,".
         "                       salary DECIMAL(7, 2),".
         "  CONSTRAINT unique_cn UNIQUE(lastname, firstname))";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  printf("  COMMIT\n");

  // commit the transaction
  odbc_commit($dbconn);

  // insert table 
  printf("\n  INSERT INTO emp_sal VALUES('SMITH', 'PHILIP', 17000.00),".
         "\n                            ('SMITH', 'PHILIP', 21000.00) \n");

  $sql = "INSERT INTO emp_sal VALUES('SMITH', 'PHILIP', 17000.00),".
         "                          ('SMITH', 'PHILIP', 21000.00)";

  printf("\n**************** Expected Error ******************\n");
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");

  // drop the constraint
  printf("\n  ALTER TABLE emp_sal DROP CONSTRAINT unique_cn\n");

  $sql = "ALTER TABLE emp_sal DROP CONSTRAINT unique_cn";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // drop table 
  printf("\n  DROP TABLE emp_sal\n");
  
  $sql = "DROP TABLE emp_sal";
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  return 0;
} // Cn_UNIQUE_Show

/****************************************************************************
* Description : The function Cn_PRIMARY_KEY_Show illustrates 'PRIMARY KEY'
*               constraint.
* Input       : ODBC connection id.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_PRIMARY_KEY_Show($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  CREATE TABLE\n");
  printf("  INSERT\n");
  printf("  ALTER TABLE\n");
  printf("  DROP TABLE\n");
  printf("TO SHOW A 'PRIMARY KEY' CONSTRAINT.\n");

  // create table
  printf("\n  CREATE TABLE emp_sal(lastname VARCHAR(10) NOT NULL,\n".
         "                       firstname VARCHAR(10) NOT NULL,\n".
         "                       salary DECIMAL(7, 2),\n".
         "  CONSTRAINT pk_cn PRIMARY KEY(lastname, firstname))\n");

  $sql = "CREATE TABLE emp_sal(lastname VARCHAR(10) NOT NULL,".
         "                       firstname VARCHAR(10) NOT NULL,".
         "                       salary DECIMAL(7, 2),".
         "  CONSTRAINT pk_cn PRIMARY KEY(lastname, firstname))";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  printf("  COMMIT\n");

  // commit the transaction
  odbc_commit($dbconn);

  // insert table  
  printf("\n  INSERT INTO emp_sal VALUES('SMITH', 'PHILIP', 17000.00),".
         "\n                            ('SMITH', 'PHILIP', 21000.00) \n");
 
  $sql = "INSERT INTO emp_sal VALUES('SMITH', 'PHILIP', 17000.00),".
         "                          ('SMITH', 'PHILIP', 21000.00)";

  printf("\n**************** Expected Error ******************\n");
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");

  // drop constraint
  printf("\n  ALTER TABLE emp_sal DROP CONSTRAINT pk_cn\n");
 
  $sql = "ALTER TABLE emp_sal DROP CONSTRAINT pk_cn";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // drop table
  printf("\n  DROP TABLE emp_sal\n");
   
  $sql = "DROP TABLE emp_sal";
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);
  
  return 0;
} // Cn_PRIMARY_KEY_Show

/****************************************************************************
* Description : The function Cn_CHECK_Show illustrates 'CHECK' constraint.
* Input       : ODBC connection id.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_CHECK_Show($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  CREATE TABLE\n");
  printf("  INSERT\n");
  printf("  ALTER TABLE\n");
  printf("  DROP TABLE\n");
  printf("TO SHOW A 'CHECK' CONSTRAINT.\n");

  // create table
  printf("\n  CREATE TABLE emp_sal(lastname VARCHAR(10),\n".
         "                       firstname VARCHAR(10),\n".
         "                       salary DECIMAL(7, 2),\n".
         "    CONSTRAINT check_cn CHECK(salary < 25000.00))\n");

  $sql = "CREATE TABLE emp_sal(lastname VARCHAR(10),".
         "                       firstname VARCHAR(10),".
         "                       salary DECIMAL(7, 2),".
         "  CONSTRAINT check_cn CHECK(salary < 25000.00))";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  printf("  COMMIT\n");

  // commit the transaction
  odbc_commit($dbconn);
  
  // insert table
  printf("\n  INSERT INTO emp_sal VALUES('SMITH', 'PHILIP', 27000.00)\n");
  
  $sql = "INSERT INTO emp_sal VALUES('SMITH', 'PHILIP', 27000.00)";

  printf("\n**************** Expected Error ******************\n");
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");

  // drop constraint
  printf("\n  ALTER TABLE emp_sal DROP CONSTRAINT check_cn\n");

  $sql = "ALTER TABLE emp_sal DROP CONSTRAINT check_cn";
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // drop table
  printf("\n  DROP TABLE emp_sal\n");

  $sql = "DROP TABLE emp_sal";
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  return 0;
} // Cn_CHECK_Show

/****************************************************************************
* Description : The function Cn_CHECK_INFO_Show illustrates 'INFORMATIONAL'
*               constraint.
* Input       : ODBC connection id.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_CHECK_INFO_Show($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  CREATE TABLE\n");
  printf("  INSERT\n");
  printf("  ALTER TABLE\n");
  printf("  DROP TABLE\n");
  printf("TO SHOW AN 'INFORMATIONAL' CONSTRAINT.\n");

  // create table 
  printf("\n  CREATE TABLE emp(empno INTEGER NOT NULL PRIMARY KEY,\n".
         "                   name VARCHAR(10),\n".
         "                   firstname VARCHAR(20),\n".
         "                   salary INTEGER CONSTRAINT minsalary\n".
         "                          CHECK (salary >= 25000)\n".
         "                          NOT ENFORCED\n".
         "                          ENABLE QUERY OPTIMIZATION)\n");
  
  $sql = "CREATE TABLE emp(empno INTEGER NOT NULL PRIMARY KEY,".
         "                   name VARCHAR(10),".
         "                   firstname VARCHAR(20),".
         "                   salary INTEGER CONSTRAINT minsalary".
         "                          CHECK (salary >= 25000)".
         "                          NOT ENFORCED".
         "                          ENABLE QUERY OPTIMIZATION)";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  printf("  COMMIT\n");

  //commit the transaction
  odbc_commit($dbconn);
 
  /* Insert data that doesn't satisfy the constraint 'minsalary'.
     Database manager does not enforce the constraint for IUD operations */
  printf("\n\nTO SHOW NOT ENFORCED OPTION\n");
  printf("\n  INSERT INTO emp VALUES(1, 'SMITH', 'PHILIP', 1000)\n\n");
 
  $sql = "INSERT INTO emp VALUES(1, 'SMITH', 'PHILIP', 1000)";
 
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // Alter the constraint to make it ENFORCED by database manager
  printf("Alter the constraint to make it ENFORCED by database manager\n");
  printf("\n  ALTER TABLE emp ALTER CHECK minsalary ENFORCED\n");

  $sql = "ALTER TABLE emp ALTER CHECK minsalary ENFORCED";

  printf("\n**************** Expected Error ******************\n");
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");
  
  // Delete entries from EMP Table 
  printf("\n  DELETE FROM emp\n");
 
  $sql = "DELETE FROM emp";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // Alter the constraint to make it ENFORCED by database manager
  printf("\n\nTO SHOW ENFORCED OPTION\n");
  printf("\n  ALTER TABLE emp ALTER CHECK minsalary ENFORCED\n");

  $sql = "ALTER TABLE emp ALTER CHECK minsalary ENFORCED";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  /* Insert table with data not conforming to the constraint 'minsalary'
     Database manager does not enforce the constraint for IUD operations */
  printf("\n  INSERT INTO emp VALUES(1, 'SMITH', 'PHILIP', 1000)\n");

  $sql = "INSERT INTO emp VALUES(1, 'SMITH', 'PHILIP', 1000)";

  printf("\n**************** Expected Error ******************\n");
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");

  // drop table
  printf("\n  DROP TABLE emp\n");

  $sql = "DROP TABLE emp";
   
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  return 0;
} // Cn_CHECK_INFO_Show

/****************************************************************************
* Description : The function Cn_WITH_DEFAULT_Show illustrates 'WITH DEFAULT'
*               constraint.
* Input       : ODBC connection id.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_WITH_DEFAULT_Show($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  CREATE TABLE\n");
  printf("  INSERT\n");
  printf("  DROP TABLE\n");
  printf("TO SHOW A 'WITH DEFAULT' CONSTRAINT.\n");

  // create table
  printf("\n  CREATE TABLE emp_sal(lastname VARCHAR(10),\n".
         "                       firstname VARCHAR(10),\n".
         "                       ".
         "salary DECIMAL(7, 2) WITH DEFAULT 17000.00)\n");

  $sql = "CREATE TABLE emp_sal(lastname VARCHAR(10),".
         "                       firstname VARCHAR(10),".
         "                       salary DECIMAL(7, 2)".
         "                         WITH DEFAULT 17000.00)";
 
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  printf("  COMMIT\n");

  //commit the transaction
  odbc_commit($dbconn);

  // insert table
  printf("\n  INSERT INTO emp_sal(lastname, firstname)\n".
         "    VALUES('SMITH', 'PHILIP'),\n".
         "          ('PARKER', 'JOHN'),\n".
         "          ('PEREZ', 'MARIA')\n");

  $sql = "INSERT INTO emp_sal(lastname, firstname)".
         "  VALUES('SMITH' , 'PHILIP'),".
         "        ('PARKER', 'JOHN'),".
         "        ('PEREZ' , 'MARIA')";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);
 
  // display table
  printf("\n  SELECT * FROM emp_sal\n");

  printf("    LASTNAME   FIRSTNAME     SALARY  \n");
  printf("    ---------- ---------- --------\n");

  $sql = "SELECT * FROM emp_sal";
 
  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);

  while (odbc_fetch_row($res))
  {
    $lastname  = odbc_result($res, "LASTNAME");
    $firstname = odbc_result($res, "FIRSTNAME");
    $salary    = odbc_result($res, "SALARY");
 
    printf("    %-10s %-10s %-5.2f\n", $lastname,  $firstname, $salary);
  }

  return 0;
} // Cn_WITH_DEFAULT_Show

/****************************************************************************
* Description : The function Cn_FK_OnInsertShow illustrates how a 
*               'FOREIGN KEY' constraint works on INSERT.
* Input       : ODBC connection id.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_FK_OnInsertShow($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  ALTER TABLE\n");
  printf("  INSERT\n");
  printf("TO SHOW HOW A FOREIGN KEY WORKS ON INSERT.\n");

  // display initial tables content
  FK_TwoTablesDisplay($dbconn);

  // store the rule clause in a variable
  $ruleclause = " ";

  // create foreign key
  FK_Create($ruleclause, $dbconn);

  // insert parent table
  printf("\n  INSERT INTO dept VALUES('D00', 'SALES')\n");
  
  $sql = "INSERT INTO dept VALUES('D00', 'SALES')";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // insert child table
  printf("\n  INSERT INTO emp VALUES('0080', 'Pearce', 'E03')\n");

  $sql = "INSERT INTO emp VALUES('0080', 'Pearce', 'E03')";

  printf("\n**************** Expected Error ******************\n");
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");

  // display final tables content
  FK_TwoTablesDisplay($dbconn);

  // rollback transaction
  printf("\n  ROLLBACK\n");

  odbc_rollback($dbconn);
 
  // drop foreign key
  FK_Drop($dbconn);

  return 0;
} // Cn_FK_OnInsertShow

/****************************************************************************
* Description : The function Cn_FK_ON_UPDATE_NO_ACTION_Show illustrates an 
*               'ON UPDATE NO ACTION' FOREIGN KEY constraint.
* Input       : ODBC connection id.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_FK_ON_UPDATE_NO_ACTION_Show($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  ALTER TABLE\n");
  printf("  UPDATE\n");
  printf("TO SHOW AN 'ON UPDATE NO ACTION' FOREIGN KEY.\n");

  // display initial tables content
  FK_TwoTablesDisplay($dbconn);

  // store the rule clause in a variable
  $ruleclause = "ON UPDATE NO ACTION ";

  // create foreign key
  FK_Create($ruleclause, $dbconn);

  // update parent table
  printf("\n  UPDATE dept SET deptno = 'E01' WHERE deptno = 'A00'\n");
  
  $sql = "UPDATE dept SET deptno = 'E01' WHERE deptno = 'A00'";

  printf("\n**************** Expected Error ******************\n");
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");

  printf("\n  UPDATE dept SET deptno =\n".
         "    CASE\n".
         "      WHEN deptno = 'A00' THEN 'B00'\n".
         "      WHEN deptno = 'B00' THEN 'A00'\n".
         "    END\n".
         "    WHERE deptno = 'A00' OR deptno = 'B00'\n");

  $sql = "UPDATE dept SET deptno = ".
         "  CASE".
         "    WHEN deptno = 'A00' THEN 'B00'".
         "    WHEN deptno = 'B00' THEN 'A00'".
         "  END".
         "  WHERE deptno = 'A00' OR deptno = 'B00'";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // update child table
  printf("\n  UPDATE emp SET dept_no = 'G11' WHERE empname = 'Wheeler'\n");
  
  $sql = "UPDATE emp SET dept_no = 'G11' WHERE empname = 'Wheeler'";
 
  printf("\n**************** Expected Error ******************\n");
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");
 
  // display final tables content
  FK_TwoTablesDisplay($dbconn);

  // rollback transaction
  printf("\n  ROLLBACK\n");

  odbc_rollback($dbconn);

  // drop foreign key
  FK_Drop($dbconn);

  return 0;
} // Cn_FK_ON_UPDATE_NO_ACTION_Show

/****************************************************************************
* Description : The function Cn_FK_ON_UPDATE_RESTRICT_Show illustrates an 
*               'ON UPDATE RESTRICT' FOREIGN KEY constraint.
* Input       : ODBC connection id.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_FK_ON_UPDATE_RESTRICT_Show($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  ALTER TABLE\n");
  printf("  UPDATE\n");
  printf("TO SHOW AN 'ON UPDATE RESTRICT' FOREIGN KEY.\n");

  // display initial tables content 
  FK_TwoTablesDisplay($dbconn);

  // store the rule clause in a variable
  $ruleclause = "ON UPDATE RESTRICT";

  // create foreign key
  FK_Create($ruleclause, $dbconn);

  // update parent table
  printf("\n  UPDATE dept SET deptno = 'E01' WHERE deptno = 'A00'\n");

  $sql = "UPDATE dept SET deptno = 'E01' WHERE deptno = 'A00'";
   
  printf("\n**************** Expected Error ******************\n");
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");

  printf("\n  UPDATE dept SET deptno =\n".
         "    CASE\n".
         "      WHEN deptno = 'A00' THEN 'B00'\n".
         "      WHEN deptno = 'B00' THEN 'A00'\n".
         "    END\n".
         "    WHERE deptno = 'A00' OR deptno = 'B00'\n");

  $sql = "UPDATE dept SET deptno = ".
         "  CASE".
         "    WHEN deptno = 'A00' THEN 'B00'".
         "    WHEN deptno = 'B00' THEN 'A00'".
         "  END".
         "  WHERE deptno = 'A00' OR deptno = 'B00'";

  printf("\n**************** Expected Error ******************\n");
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");

  // update child table
  printf("\n  UPDATE emp SET dept_no = 'G11' WHERE empname = 'Wheeler'\n");
 
  $sql = "UPDATE emp SET dept_no = 'G11' WHERE empname = 'Wheeler'";

  printf("\n**************** Expected Error ******************\n");
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");

  // display final tables content
  FK_TwoTablesDisplay($dbconn);

  // rollback transaction
  printf("\n  ROLLBACK\n");

  odbc_rollback($dbconn);

  // drop foreign key
  FK_Drop($dbconn);

  return 0;
} // Cn_FK_ON_UPDATE_RESTRICT_Show

/****************************************************************************
* Description : The function Cn_FK_ON_DELETE_CASCADE_Show illustrates an
*               'ON DELETE CASCADE' FOREIGN KEY constraint.
* Input       : ODBC connection id.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_FK_ON_DELETE_CASCADE_Show($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  ALTER TABLE\n");
  printf("  DELETE\n");
  printf("TO SHOW AN 'ON DELETE CASCADE' FOREIGN KEY.\n");

  // display initial tables content
  FK_TwoTablesDisplay($dbconn);

  // store the rule clause in a variable
  $ruleclause = "ON DELETE CASCADE";
   
  // create foreign key
  FK_Create($ruleclause, $dbconn);

  // delete parent table
  printf("\n  DELETE FROM dept WHERE deptno = 'C00'\n");
  
  $sql = "DELETE FROM dept WHERE deptno = 'C00'";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // display tables content
  FK_TwoTablesDisplay($dbconn);

  // delete child table
  printf("\n  DELETE FROM emp WHERE empname = 'Wheeler'\n");

  $sql = "DELETE FROM emp WHERE empname = 'Wheeler'";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // display final tables content
  FK_TwoTablesDisplay($dbconn);

  // rollback transaction
  printf("\n  ROLLBACK\n");
  
  odbc_rollback($dbconn);

  // drop foreign key
  FK_Drop($dbconn);

  return 0;
} // Cn_FK_ON_DELETE_CASCADE_Show

/****************************************************************************
* Description : The function Cn_FK_ON_DELETE_SET_NULL_Show illustrates an
*               'ON DELETE SET NULL' FOREIGN KEY constraint.
* Input       : ODBC connection id.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_FK_ON_DELETE_SET_NULL_Show($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  ALTER TABLE\n");
  printf("  DELETE\n");
  printf("TO SHOW AN 'ON DELETE SET NULL' FOREIGN KEY.\n");

  // display initial tables content
  FK_TwoTablesDisplay($dbconn);

  // store the rule clause in a variable
  $ruleclause = "ON DELETE SET NULL";
 
  // create foreign key
  FK_Create($ruleclause, $dbconn);
 
  // delete parent table
  printf("\n  DELETE FROM dept WHERE deptno = 'C00'\n");

  $sql = "DELETE FROM dept WHERE deptno = 'C00'";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // display tables content
  FK_TwoTablesDisplay($dbconn);

  // delete child table
  printf("\n  DELETE FROM emp WHERE empname = 'Wheeler'\n");
  
  $sql = "DELETE FROM emp WHERE empname = 'Wheeler'";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // display final tables content
  FK_TwoTablesDisplay($dbconn);

  // rollback transaction
  printf("\n  ROLLBACK\n");

  odbc_rollback($dbconn);

  // drop foreign key
  FK_Drop($dbconn);

  return 0;
} // Cn_FK_ON_DELETE_SET_NULL_Show

/****************************************************************************
* Description : The function Cn_FK_ON_DELETE_NO_ACTION_Show illustrates an
*               'ON DELETE NO ACTION' FOREIGN KEY constraint.
* Input       : ODBC connection id.
* Output      : Returns 0 on success, exits otherwise.
****************************************************************************/
function Cn_FK_ON_DELETE_NO_ACTION_Show($dbconn)
{
  printf("\n-----------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENTS:\n");
  printf("  ALTER TABLE\n");
  printf("  DELETE\n");
  printf("TO SHOW AN 'ON DELETE NO ACTION' FOREIGN KEY.\n");

  // display initial tables content
  FK_TwoTablesDisplay($dbconn);

  // store the rule clause in a variable
  $ruleclause = "ON DELETE NO ACTION";

  // create foreign key
  FK_Create($ruleclause, $dbconn);

  // delete parent table
  printf("\n  DELETE FROM dept WHERE deptno = 'C00'\n");

  $sql = "DELETE FROM dept WHERE deptno = 'C00'";

  printf("\n**************** Expected Error ******************\n");
  
  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // handle the expected error
  $sqlerror = odbc_errormsg($dbconn);
  trigger_error("$sqlerror", ERROR);

  printf("**************************************************\n\n");
  
  // delete child table
  printf("\n  DELETE FROM emp WHERE empname = 'Wheeler'\n");

  $sql = "DELETE FROM emp WHERE empname = 'Wheeler'";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // display final tables content
  FK_TwoTablesDisplay($dbconn);

  // rollback transaction
  printf("\n  ROLLBACK\n");

  odbc_rollback($dbconn);

  // drop foreign key
  FK_Drop($dbconn);
  
  return 0;
} // Cn_FK_ON_DELETE_NO_ACTION_Show

?>
