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
// SOURCE FILE NAME: UDFcli.java
//
// SAMPLE: Call the UDFs in UDFsrv.java
//
//         Parameter Style used in this program is "DB2GENERAL".
//
//         Steps to run the sample with command line window:
//
//         I) If you have a compatible make/nmake program on your system, 
//            do the following:
//            1. Compile the server source file UDFsrv (this will also compile
//               the Utility file, erase the existing library/class files and
//               copy the newly compiled class files, UDFsqlsv.class and 
//               Person.class from the current directory to the 
//               $(DB2PATH)\function directory):
//                 nmake/make UDFsrv
//            2. Compile the client source file UDFcli (this will also call
//               the script 'udfcat' to catalog the UDFs):
//                 nmake/make UDFcli
//            3. Run the client UDFcli:
//                 java UDFcli
//
//         II) If you don't have a compatible make/nmake program on your system,
//             do the following:
//             1. Compile the utility file and the server source file with:
//                  javac Util.java
//                  javac UDFsrv.java
//             2. Erase the existing library/class files (if exists), 
//                UDFsrv.class and Person.class from the following path,
//                $(DB2PATH)\function. 
//             3. copy the class files, UDFsrv.class and Person.class from 
//                the current directory to the $(DB2PATH)\function.
//             4. Register/catalog the UDFs with:
//                  udfcat
//             5. Compile UDFcli with:
//                  javac UDFcli.java
//             6. Run UDFcli with:
//                  java UDFcli
//
// SQL Statements USED:
//         SELECT
//
// OUTPUT FILE: UDFcli.out (available in the online documentation)
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

import java.sql.*; // JDBC classes

class UDFcli
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

      demoExternalScratchpadScalarUDF(db.con);
      demoExternalScalarUDFReturningErr(db.con);
      demoExternalTableUDF(db.con);
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    }
  } // main

  static void demoExternalScratchpadScalarUDF(Connection con)
  {
    System.out.println();
    System.out.println(
      "----------------------------------------------------------\n" +
      "USE THE SQL STATEMENTS:\n" +
      "  SELECT\n" +
      "TO WORK WITH SCRATCHPAD SCALAR UDF.");

    try
    {
      Statement stmt = con.createStatement();

      // use SCRATCHPAD scalar UDF
      System.out.println();
      System.out.println(
        "  Use the SCRATCHPAD scalar UDF:\n" +
        "    SELECT scratchpadScUDF(), name, job\n" +
        "      FROM staff\n" +
        "      WHERE name LIKE 'S%'");

      ResultSet rs = stmt.executeQuery(
        "SELECT scratchpadScUDF(), name, job " +
        "  FROM staff " +
        "  WHERE name LIKE 'S%' ");

      System.out.println("    COUNTER NAME       JOB\n" +
                         "    ------- ---------- -------");

      int counter;
      String name;
      String job;
      while (rs.next())
      {
        counter = rs.getInt(1);
        name = rs.getString(2);
        job = rs.getString(3);

        System.out.println("    " + Data.format(counter, 7) +
                           " " + Data.format(name, 10) +
                           " " + Data.format(job, 7));
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
  } // demoExternalScratchpadScalarUDF

  static void demoExternalScalarUDFReturningErr(Connection con)
  {
    System.out.println();
    System.out.println(
      "----------------------------------------------------------\n" +
      "USE THE SQL STATEMENTS:\n" +
      "  SELECT\n" +
      "TO WORK WITH SCALAR UDF THAT RETURNS ERROR.");

    try
    {
      Statement stmt = con.createStatement();

      // use scalar UDF
      System.out.println();
      System.out.println(
        "  Use the scalar UDF that returns error:\n" +
        "    SELECT name, job, scUDFReturningErr(salary, 0.00)\n"+
        "      FROM staff\n" +
        "      WHERE name LIKE 'S%'");

      ResultSet rs = stmt.executeQuery(
        "SELECT name, job, scUDFReturningErr(salary, 0.00)\n" +
        "  FROM staff " +
        "  WHERE name LIKE 'S%'");

      System.out.println("    NAME    JOB        COMM\n" +
                         "    ------- ---------- --------");

      String name;
      String job;
      double comm;
      while (rs.next())
      {
        name = rs.getString(1);
        job = rs.getString(2);
        comm = rs.getDouble(3);

        System.out.println("    " + Data.format(name, 7) +
                           " " + Data.format(job, 10) +
                           " " + Data.format(comm, 7, 2));
      }
      rs.close();

      // close statement
      stmt.close();
    }
    catch (SQLException e)
    {
      if (e.getSQLState().equals("38999"))
      {
        System.out.println();
        System.out.println("--------- Expected Error ---------\n");
      }
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // demoExternalscalarUDFReturningErr

  static void demoExternalTableUDF(Connection con)
  {
    System.out.println();
    System.out.println(
      "----------------------------------------------------------\n" +
      "USE THE SQL STATEMENTS:\n" +
      "  SELECT\n" +
      "TO WORK WITH TABLE UDF.");

    try
    {
      Statement stmt = con.createStatement();

      // use table UDF
      System.out.println();
      System.out.println(
        "  Use the table UDF:\n" +
        "    SELECT udfTb.name, udfTb.job, udfTb.salary\n" +
        "      FROM TABLE(TableUDF(1.5)) AS udfTb");

      ResultSet rs = stmt.executeQuery(
        "SELECT udfTb.name, udfTb.job, udfTb.salary " +
        "  FROM TABLE(TableUDF(1.5)) AS udfTb ");

      System.out.println("    NAME    JOB        SALARY\n" +
                         "    ------- ---------- --------");

      String name;
      String job;
      double newSalary;
      while (rs.next())
      {
        name = rs.getString(1);
        job = rs.getString(2);
        newSalary = rs.getDouble(3);

        System.out.println("    " + Data.format(name, 7) +
                           " " + Data.format(job, 10) +
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
  } // demoExternalTableUDF
} // UDFcli

