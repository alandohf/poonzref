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
// SOURCE FILE NAME: DtUdt.java
//
// SAMPLE: How to create, use and drop user defined distinct types
//
// SQL statements USED:
//         CREATE DISTINCT TYPE
//         CREATE TABLE
//         DROP DISTINCT TYPE
//         DROP TABLE
//         INSERT
//         COMMIT
//
// Classes used from Util.java are:
//         Db
//         JdbcException
//
// OUTPUT FILE: DtUdt.out (available in the online documentation)
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

import java.lang.*;
import java.sql.*;

class DtUdt
{
  public static void main(String argv[])
  {
    try
    {
      Db db = new Db(argv);

      System.out.println();
      System.out.println("THIS SAMPLE SHOWS HOW TO CREATE, USE AND DROP\n" +
        "USER DEFINED DISTINCT TYPES.");

      // connect to the 'sample' database
      db.connect();

      create(db.con);
      use(db.con);
      drop(db.con);

      // disconnect from the 'sample' database
      db.disconnect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e) ;
      jdbcExc.handle();
    }
  } // main

  // This function creates a few user defined distinct types
  static void create(Connection con)
  {
    try
    {
      System.out.println();
      System.out.println(
        "----------------------------------------------------------\n" +
        "USE THE SQL STATEMENTS:\n" +
        "  CREATE DISTINCT TYPE\n" +
        "  COMMIT\n" +
        "TO CREATE UDTs.");

      System.out.println();
      System.out.println(
        "  CREATE DISTINCT TYPE udt1 AS INTEGER WITH COMPARISONS");

      Statement stmt = con.createStatement();
      stmt.executeUpdate(
        "CREATE DISTINCT TYPE udt1 AS INTEGER WITH COMPARISONS");
      stmt.close();

      System.out.println(
        "  CREATE DISTINCT TYPE udt2 AS CHAR(2) WITH COMPARISONS");

      Statement stmt1 = con.createStatement();
      stmt1.executeUpdate(
        "CREATE DISTINCT TYPE udt2 AS CHAR(2) WITH COMPARISONS");
      stmt1.close();

      System.out.println(
        "  CREATE DISTINCT TYPE udt3 AS DECIMAL(7, 2) WITH COMPARISONS");

      Statement stmt2 = con.createStatement();
      stmt2.executeUpdate(
        "CREATE DISTINCT TYPE udt3 AS DECIMAL(7, 2) WITH COMPARISONS ");
      stmt2.close();

      System.out.println("  COMMIT");
      con.commit();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // create

  // This function uses the user defined distinct types that we created
  // at the beginning of this program.
  static void use(Connection con)
  {
    System.out.println();
    System.out.println(
      "----------------------------------------------------------\n" +
      "USE THE SQL STATEMENTS:\n" +
      "  EXECUTE IMMEDIATE\n" +
      "  COMMIT\n" +
      "TO USE UTDs.");

    // Create a table that uses the user defined distinct types
    try
    {
      System.out.println();
      System.out.println(
        "  CREATE TABLE udt_table(col1 udt1, col2 udt2, col3 udt3)");

      Statement stmt = con.createStatement();
      stmt.executeUpdate(
        "CREATE TABLE udt_table(col1 udt1, col2 udt2, col3 udt3)");
      stmt.close();

      System.out.println("  COMMIT");
      con.commit();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }

    // Insert data into the table with the user defined distinct types
    try
    {
      String strStmt;
      System.out.println();
      System.out.println(
        "  INSERT INTO udt_table \n" +
        "    VALUES(CAST(77 AS udt1),\n" +
        "           CAST('ab' AS udt2),\n" +
        "           CAST(111.77 AS udt3))");

      Statement stmt1 = con.createStatement();
      stmt1.executeUpdate(
        "INSERT INTO udt_table VALUES(CAST(77 AS udt1), " +
        "                             CAST('ab' AS udt2), " +
        "                             CAST(111.77 AS udt3))");
      stmt1.close();

      System.out.println("  COMMIT");
      con.commit();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }

    // Drop the table with the user defined distinct types
    try
    {
      System.out.println();
      System.out.println("  DROP TABLE udt_table");

      Statement stmt2 = con.createStatement();
      stmt2.executeUpdate("DROP TABLE udt_table");
      stmt2.close();

      System.out.println("  COMMIT");
      con.commit();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con) ;
      jdbcExc.handle();
    }
  } // use

  // This function drops all of the user defined distinct types that
  // we created at the beginning of this program
  static void drop(Connection con)
  {
    System.out.println();
    System.out.println(
      "----------------------------------------------------------\n" +
      "USE THE SQL STATEMENTS:\n" +
      "  DROP\n" +
      "  COMMIT\n" +
      "TO DROP UDTs.");

    try
    {
      System.out.println();
      System.out.println("  DROP USER DISTINCT TYPE udt1");
      Statement stmt = con.createStatement();
      stmt.executeUpdate("DROP DISTINCT TYPE udt1");
      stmt.close();

      System.out.println("  DROP USER DISTINCT TYPE udt2");
      Statement stmt1 = con.createStatement();
      stmt1.executeUpdate("DROP DISTINCT TYPE udt2");
      stmt1.close();

      System.out.println("  DROP USER DISTINCT TYPE udt3");
      Statement stmt2 = con.createStatement();
      stmt2.executeUpdate("DROP DISTINCT TYPE udt3");
      stmt2.close();

      System.out.println("  COMMIT");
      con.commit();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con) ;
      jdbcExc.handle();
    }
  } // drop
} // DtUdt

