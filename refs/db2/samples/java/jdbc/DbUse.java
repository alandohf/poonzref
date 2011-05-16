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
// SOURCE FILE NAME: DbUse.java
//
// SAMPLE: How to use a database
//
// SQL Statements USED:
//         CREATE TABLE
//         DROP TABLE
//         DELETE
//         COMMIT
//         ROLLBACK
//
// JAVA 2 CLASSES USED:
//         Statement
//         PreparedStatement
//
// Classes used from Util.java are:
//         Db
//         JdbcException
//
// OUTPUT FILE: DbUse.out (available in the online documentation)
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

class DbUse
{
  public static void main(String argv[])
  {
    try
    {
      Db db = new Db(argv);

      System.out.println();
      System.out.println("THIS SAMPLE SHOWS HOW TO USE A DATABASE.");

      // connect to the 'sample' database
      db.connect();

      execStatement(db.con);
      execPreparedStatement(db.con);
      execPreparedStatementWithParam(db.con);

      // disconnect from the 'sample' database
      db.disconnect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    }
  } // main

  static void execStatement(Connection con)
  {
    System.out.println();
    System.out.println(
      "----------------------------------------------------------\n" +
      "USE THE JAVA 2 CLASS:\n" +
      "  Statement\n" +
      "TO EXECUTE A STATEMENT.");

    try
    {
      Statement stmt = con.createStatement();

      // execute the statement
      System.out.println();
      System.out.println("  CREATE TABLE t1(col1 INTEGER)");
      stmt.execute("CREATE TABLE t1(col1 INTEGER)");

      // commit the transaction
      System.out.println("  COMMIT");
      con.commit();

      // execute the statement
      System.out.println("  DROP TABLE t1");
      stmt.execute("DROP TABLE t1");

      // commit the transaction
      System.out.println("  COMMIT");
      con.commit();

      // close the statement
      stmt.close();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // execStatement

  static void execPreparedStatement(Connection con)
  {
    System.out.println();
    System.out.println(
      "----------------------------------------------------------\n" +
      "USE THE JAVA 2 CLASS:\n" +
      "  PreparedStatement\n" +
      "TO EXECUTE A PREPARED STATEMENT.");

    try
    {
      // prepare the statement
      System.out.println();
      System.out.println("  Prepared the statement:\n" +
                         "    DELETE FROM org WHERE deptnumb <= 70");

      PreparedStatement prepStmt = con.prepareStatement(
        "  DELETE FROM org WHERE deptnumb <= 70");

      // execute the statement
      System.out.println();
      System.out.println("  Executed the statement");
      prepStmt.execute();

      // rollback the transaction
      System.out.println();
      System.out.println("  ROLLBACK");
      con.rollback();

      // close the statement
      prepStmt.close();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // execPreparedStatement

  static void execPreparedStatementWithParam(Connection con)
  {
    System.out.println();
    System.out.println(
      "----------------------------------------------------------\n" +
      "USE THE JAVA 2 CLASS:\n" +
      "  PreparedStatement\n" +
      "TO EXECUTE A PREPARED STATEMENT WITH PARAMETERS.");

    try
    {
      // prepare the statement
      System.out.println();
      System.out.println(
        "  Prepared the statement:\n" +
        "    DELETE FROM org WHERE deptnumb <= ? AND division = ?");

      PreparedStatement prepStmt = con.prepareStatement(
        "  DELETE FROM org WHERE deptnumb <= ? AND division = ? ");

      // execute the statement
      System.out.println();
      System.out.println("  Executed the statement for:\n" +
                         "    parameter 1 = 70\n" +
                         "    parameter 2 = 'Eastern'");

      prepStmt.setInt(1, 70);
      prepStmt.setString(2, "Eastern");
      prepStmt.execute();

      // rollback the transaction
      System.out.println();
      System.out.println("  ROLLBACK");
      con.rollback();

      // close the statement
      prepStmt.close();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // execPreparedStatementWithParam
} // DbUse

