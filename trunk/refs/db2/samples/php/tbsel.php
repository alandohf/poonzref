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
** SOURCE FILE NAME: tbsel.php
**
** SAMPLE: How to select from each of: insert, update, delete.
**
** CREATING TABLES FOR THIS SAMPLE (Must be done prior to compiling/running
** the sample):
** Enter "tbselinit" while in the samples/php directory to create the
** tables used by this sample.  The tbselinit script (UNIX and Linux)
** or tbselinit.bat batch file (Windows) connects to the database,
** runs tbseldrop.db2 to drop the tables if they previously existed, runs
** tbselcreate.db2 which creates the sample tables, then disconnects from
** the database.
**
** SQL STATEMENTS USED:
**         INCLUDE
**         INSERT
**         SELECT FROM INSERT
**         SELECT FROM UPDATE
**         SELECT FROM DELETE
**         DROP TABLE
**
** OUTPUT FILE: tbsel.out (available in the online documentation)
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

printf("\nTHIS SAMPLE SHOWS HOW TO SELECT FROM EACH OF: INSERT, UPDATE,".
       " DELETE.\n\n");

// connect to the database
$dbconn = DbConn($dbname, $username, $password);

// override the auto commit option 
odbc_autocommit($dbconn, FALSE);

if ($dbconn != 0)
{
  // call the Insert function
  Insert($dbconn);

  // call the Print function
  TbPrint($dbconn);

  // call the Buy_company function
  Buy_company($dbconn);

  // call the Print function again
  TbPrint($dbconn);

  // call the Drop function
  Drop($dbconn);
}

// disconnect from the database
DbDisconn($dbconn);

/****************************************************************************
* Description: The Insert function populates the tables used by this
*              sample.
* Input      : ODBC connection id 
* Output     : Returns 0 on success, exits otherwise.
****************************************************************************/
function Insert($dbconn)
{
  /* please see tbselcreate.db2 for the table definitions.
     The context for this sample is that of a Company B taking over
     a Company A.  This sample illustrates how company B incorporates
     data from table company_b into table company_a. */

  printf("\nINSERT INTO company_a VALUES".
         "\n (5275, 'Sanders', 20, 'Mgr', 15, 18357.50),".
         "\n (5265, 'Pernal', 20, 'Sales', 1, 18171.25),".
         "\n (5791, 'O''Brien', 38, 'Sales', 10, 18006.00)\n");

  // populate table company_a with data.
  $sql = "INSERT INTO company_a".
         "  VALUES(5275, 'Sanders', 20, 'Mgr', 15, 18357.50),".
         "        (5265, 'Pernal', 20, 'Sales', 1, 18171.25),".
         "        (5791, 'O''Brien', 38, 'Sales', 10, 18006.00)";  

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  print "\nINSERT INTO company_b VALUES\n".
        " (default, 'Naughton', 38, 'Clerk', 0,".
        " 12954.75, 'No Benefits', 0), \n".
        " (default, 'Yamaguchi', 42, 'Clerk', 6,".
        " 10505.90, 'Basic Health Coverage', 0),\n".
        " (default, 'Fraye', 51, 'Mgr', 6,".
        " 21150.00, 'Basic Health Coverage', 0), \n".
        " (default, 'Williams', 51, 'Sales', 6,".
        " 19456.50, 'Basic Health Coverage', 0), \n".
        " (default, 'Molinare', 10, 'Mgr', 7,".
        " 22959.20, 'Basic Health Coverage', 0)\n";

  // populate table company_b with data.
  $sql = "INSERT INTO company_b".
         "  VALUES(default, 'Naughton', 38, 'Clerk', 0,".
         "           12954.75, 'No Benefits', 0),".
         "        (default, 'Yamaguchi', 42, 'Clerk', 6,".
         "           10505.90, 'Basic Health Coverage', 0),".
         "        (default, 'Fraye', 51, 'Mgr', 6,".
         "           21150.00, 'Basic Health Coverage', 0),".
         "        (default, 'Williams', 51, 'Sales', 6,".
         "           19456.50, 'Basic Health Coverage', 0),".
         "        (default, 'Molinare', 10, 'Mgr', 7,".
         "           22959.20, 'Basic Health Coverage', 0)";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  // commit the transactions 
  odbc_commit($dbconn);

  return 0;
} // Insert

/****************************************************************************
* Description: The Buy_company function encapsulates the table updates after
*              Company B takes over Company A. Each employee from table
*              company_a is allocated a benefits package. The employee data
*              is moved into table company_b. Each employee's salary is
*              increased by 5%. The old and new salaries are recorded in a
*              table salary_change.
* Input      : ODBC connection id 
* Output     : Returns 0 on success, exits otherwise.
****************************************************************************/
function Buy_company($dbconn)
{
  /* the following SELECT statement references a DELETE statement in its
     FROM clause.  It deletes all rows from company_a, selecting all deleted
     rows into the result set. */
  
  $sql = "SELECT ID, NAME, DEPARTMENT, JOB, YEARS, SALARY".
         "  FROM OLD TABLE (DELETE FROM company_a)";
  
  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);

  /* the following while loop iterates through each employee of table
     company_a. */
  
  while (odbc_fetch_row($res))
  {
    $id = odbc_result($res, "ID");
    $name = odbc_result($res, "NAME");
    $department = odbc_result($res, "DEPARTMENT");
    $job = odbc_result($res, "JOB");
    $years = odbc_result($res, "YEARS");
    $salary = odbc_result($res, "SALARY");

    /* The following if statement sets the new employee's benefits based on
       their years of experience. */
    if ($years > 14)
    {
      $benefits = 'Advanced Health Coverage and Pension Plan';
    }
    elseif ($years > 9)
    {
      $benefits = 'Advanced Health Coverage';
    }
    elseif ($years > 4)
    {
      $benefits = 'Basic Health Coverage';
    }
    else
    {
      $benefits = 'No Benefits';
    }

    // escape the ' character, if any, in the employee name.
    $name = str_replace("'", "''", $name);

    /* the following SELECT statement references an INSERT statement in its
       FROM clause.  It inserts an employee record from host variables into
       table company_b.  The current employee ID from the result set is 
       selected into the host variable new_id. The keywords FROM FINAL TABLE
       determine that the value in new_id is the value of ID after the
       INSERT statement is complete.
    
       Note that the ID column in table company_b is generated and without
       the SELECT statement an additional query would have to be made in
       order to retrieve the employee's ID number. */

    $sql = "SELECT ID FROM FINAL TABLE(INSERT INTO company_b".
           "  VALUES(default, '$name', $department, '$job',".
           "           $years, $salary, '$benefits', $id))"; 
    
    // prepare and execute the sql statement
    $res1 = odbc_exec($dbconn, $sql);

    $new_id = odbc_result($res1, "ID");

    /* the following SELECT statement references an UPDATE statement in its
       FROM clause.  It updates an employee's salary by giving them a 5%
       raise.  The employee's id, old salary and current salary are all read
       into host variables for later use in this function.
 
       the INCLUDE statement works by creating a temporary column to keep
       track of the old salary.  This temporary column is only available
       for this statement and is gone once the statement completes.  The
       only way to keep this data after the statement completes is to
       read it into a host variable. */
 
    $sql = "SELECT ID, OLD_SALARY, SALARY".
           "  FROM FINAL TABLE (UPDATE company_b INCLUDE".
           "                      (OLD_SALARY DECIMAL(7,2))".
           "                         SET OLD_SALARY = SALARY,".
           "                           SALARY = SALARY * 1.05".
           "                         WHERE ID = $new_id)";

    // prepare and execute the sql statement
    $res1 = odbc_exec($dbconn, $sql);

    $id = odbc_result($res1, "ID");
    $old_salary = odbc_result($res1, "OLD_SALARY");
    $salary = odbc_result($res1, "SALARY");

    /* this INSERT statement inserts an employee's id, old salary and current
       salary into the salary_change table. */

    $sql = "INSERT INTO salary_change".
           "  VALUES($id, $old_salary, $salary)";
 
    // prepare and execute the sql statement
    odbc_exec($dbconn, $sql);
  } 
 
  /* the following DELETE statement references a SELECT statement in its FROM
     clause.  It lays off the highest paid manager.  This DELETE statement
     removes the manager from the table company_b. */

  $sql = "DELETE FROM".
         "  (SELECT * FROM company_b".
         "     ORDER BY SALARY DESC FETCH FIRST ROW ONLY)";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);
 
  /* the following UPDATE statement references a SELECT statement in its FROM
     clause.  It gives the most senior employee a $10000 bonus.  This UPDATE
     statement raises the employee's salary in the table company_b. */
  
  $sql = "UPDATE (SELECT MAX(YEARS) OVER() AS max_years,".
         "                 YEARS,                       ".
         "                 SALARY                       ".
         "          FROM company_b)                     ".
         "  SET SALARY = SALARY + 10000                 ".
         "  WHERE max_years = YEARS                     ";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);
               
  return 0;
} // Buy_company

/****************************************************************************
* Description: The TbPrint function outputs the data in the tables: 
*              company_a, company_b and salary_change.
*              For each table, a while loop is  used to fetch and display
*              row data.
* Input      : ODBC connection id
* Output     : Returns 0 on success, exits otherwise.
****************************************************************************/
function TbPrint($dbconn)
{
  $sql = "SELECT ID,
                 NAME,
                 DEPARTMENT,
                 JOB,
                 YEARS,
                 SALARY
            FROM company_a";
  
  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);
 
  printf("\nSELECT * FROM company_a\n\n");
  printf("ID     NAME      DEPARTMENT JOB   YEARS  SALARY\n");
  printf("------ --------- ---------- ----- ------ ---------\n");

  while (odbc_fetch_row($res))
  {
    $id = odbc_result($res, "ID");
    $name = odbc_result($res, "NAME");
    $department = odbc_result($res, "DEPARTMENT");
    $job = odbc_result($res, "JOB");
    $years = odbc_result($res, "YEARS");
    $salary = odbc_result($res, "SALARY");

    printf("%-6d %-9s %-10d %-5s %-7d %-7.2f\n",
                             $id, $name, $department, $job, $years, $salary);
  }
 
   $sql = "SELECT ID,".
          "       NAME,".
          "       DEPARTMENT,".
          "       JOB,".
          "       YEARS,".
          "       SALARY,".
          "       BENEFITS,".
          "       OLD_ID".
          "  FROM company_b";

   // prepare and execute the sql statement
   $res = odbc_exec($dbconn, $sql);

   printf("\nSELECT * FROM company_b\n\n");
   print("ID     NAME      DEPARTMENT JOB   YEARS  SALARY    BENEFITS                                           OLD_ID\n");
   printf("------ --------- ---------- ----- ------ ---------");
   printf(" -------------------------------------------------- ------\n");

   while (odbc_fetch_row($res))
   {
      $id = odbc_result($res, "ID");
      $name = odbc_result($res, "NAME");
      $department = odbc_result($res, "DEPARTMENT");
      $job = odbc_result($res, "JOB");
      $years = odbc_result($res, "YEARS");
      $salary = odbc_result($res, "SALARY");
      $benefits = odbc_result($res, "BENEFITS");
      $old_id = odbc_result($res, "OLD_ID");

      printf("%-6d %-9s %-10d %-5s %-7d %-6.2f %-50s %-6d\n\n",
                                      $id, $name, $department, $job, $years,
                                         $salary, $benefits, $old_id);
   }

   $sql = "SELECT ID, OLD_SALARY, SALARY FROM salary_change";

   // prepare and execute the sql statement
   $res = odbc_exec($dbconn, $sql);

   printf("\nSELECT * FROM salary_change\n\n");
   printf("ID     OLD_SALARY SALARY\n");
   printf("------ ---------- ---------\n");
   
   while (odbc_fetch_row($res))
   {
     $id = odbc_result($res, "ID");
     $old_salary = odbc_result($res, "OLD_SALARY");
     $salary = odbc_result($res, "SALARY");

     printf("%-8d %-6.2f %-6.2f\n", $id, $old_salary, $salary);
   }
   
   return 0;
} //TbPrint

/****************************************************************************
* Description: The Drop function drops the tables used by this sample.
* Input      : ODBC connection id
* Output     : Returns 0 on success, exits otherwise.
****************************************************************************/
function Drop($dbconn)
{
  printf("\nDROP TABLE company_a\n");
  $sql = "DROP TABLE company_a";

  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);
  
  print "\nDROP TABLE company_b\n";
  $sql = "DROP TABLE company_b";

  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);

  print "\nDROP TABLE salary_change\n";
  $sql = "DROP TABLE salary_change";

  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);

  // commit the transaction
  odbc_commit($dbconn);

  return 0;
} // Drop

?>
