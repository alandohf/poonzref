//***************************************************************************
// Licensed Materials - Property of IBM
//
// Governed under the terms of the International
// License Agreement for Non-Warranted Sample Code.
//
// (C) COPYRIGHT International Business Machines Corp. 1997 - 2002
// All Rights Reserved.
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//***************************************************************************
//
// SOURCE FILE NAME: UDFjcli.java
//
// SAMPLE: Call the UDFs in UDFjsrv.java
//
//         Parameter Style used in this program is "JAVA".
//
//         Steps to run the sample with command line window:
//
//         I) If you have a compatible make/nmake program on your system, 
//            do the following:
//            1. Compile the server source file UDFjsrv (this will also compile
//               the Utility file, erase the existing library/class files and
//               copy the newly compiled class files, UDFjsrv.class and 
//               Person.class from the current directory to the 
//               $(DB2PATH)\function directory):
//                 nmake/make UDFjsrv
//            2. Compile the client source file UDFjcli (this will also call
//               the script 'udfjcat' to catalog the UDFs):
//                 nmake/make UDFjcli
//            3. Run the client UDFjcli:
//                 java UDFjcli
//
//         II) If you don't have a compatible make/nmake program on your system,
//             do the following:
//             1. Compile the utility file and the server source file with:
//                  javac Util.java
//                  javac UDFjsrv.java
//             2. Erase the existing library/class files (if exists), 
//                UDFjsrv.class and Person.class from the following path,
//                $(DB2PATH)\function. 
//             3. copy the class files, UDFjsrv.class and Person.class from 
//                the current directory to the $(DB2PATH)\function.
//             4. Register/catalog the UDFs with:
//                  udfjcat
//             5. Compile UDFjcli with:
//                  javac UDFjcli.java
//             6. Run UDFjcli with:
//                  java UDFjcli
//
// SQL Statements USED:
//         SELECT
//
// OUTPUT FILE: UDFjcli.out (available in the online documentation)
// Output will vary depending on the JDBC driver connectivity used.
//***************************************************************************
//
// For more information on the sample programs, see the README file.
//
// For information on developing JDBC applications, see the Application
// Development Guide.
//
// For information on using SQL statements, see the SQL Reference.
//
// For the latest information on programming, compiling, and running DB2
// applications, visit the DB2 application development website at
//     http://www.software.ibm.com/data/db2/udb/ad
//**************************************************************************/

import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;

class UDFjcli
{
  public static void main(String argv[])
  {
    try
    {
      Db db = new Db(argv);

      System.out.println();
      System.out.println("THIS SAMPLE SHOWS HOW TO WORK WITH UDFs.");

      // connect database
      db.connect();

      demoExternalScalarUDF(db.con);
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    }
  } // main

  static void demoExternalScalarUDF(Connection con)
  {
    System.out.println();
    System.out.println(
      "----------------------------------------------------------\n" +
      "USE THE SQL STATEMENTS:\n" +
      "  CREATE FUNCTION\n" +
      "  COMMIT\n" +
      "  SELECT\n" +
      "  DROP FUNCTION\n" +
      "TO WORK WITH SCALAR UDF.");

    try
    {
      Statement stmt = con.createStatement();

      // use scalar UDF
      System.out.println();
      System.out.println(
        "  Use the scalar UDF:\n" +
        "    SELECT name, job, salary, scalarUDF(job, salary)\n" +
        "      FROM staff\n" +
        "      WHERE name LIKE 'S%'");

      ResultSet rs = stmt.executeQuery(
        "SELECT name, job, salary, scalarUDF(job, salary) " +
        "  FROM staff " +
        "  WHERE name LIKE 'S%' ");

      System.out.println();
      System.out.println(
        "    NAME       JOB     SALARY   NEW_SALARY\n" +
        "    ---------- ------- -------- ----------");

      String name;
      String job;
      double salary;
      double newSalary;
      while (rs.next())
      {
        name = rs.getString(1);
        job = rs.getString(2);
        salary = rs.getDouble(3);
        newSalary = rs.getDouble(4);
        System.out.println("    " + Data.format(name, 10) +
                           " " + Data.format(job, 7) +
                           " " + Data.format(salary, 7, 2) +
                           " " + Data.format(newSalary, 7, 2));
      }
      rs.close();

      // close statement
      stmt.close();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  }
} // UDFjcli

