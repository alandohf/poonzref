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
// SOURCE FILE NAME: DbNative.java
//
// SAMPLE: Converts an SQL statement into the system's native SQL grammar
//
// SQL Statements USED:
//         SELECT
//
// JAVA 2 CLASSES USED:
//         Connection
//
// Classes used from Util.java are:
//         Db
//         JdbcException
//
// OUTPUT FILE: DbNative.out (available in the online documentation)
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

class DbNative
{
  public static void main(String argv[])
  {
    try
    {
      Db db = new Db(argv);

      System.out.println();
      System.out.println(
        "THIS SAMPLE SHOWS HOW TO CONVERT A GIVEN SQL STATEMENT INTO \n" +
        "THE SYSTEM'S NATIVE SQL GRAMMAR. ");

      // connect to the 'sample' database
      db.connect();

      String stmt = "SELECT * FROM employee WHERE hiredate={d '1994-03-29'}";
      String odbcEscapeClause = "{d '1994-03-29'}";

      System.out.println();
      System.out.println(
        "----------------------------------------------------------\n" +
        "USE THE API Function:\n" +
        "  Connection.nativeSQL()\n" +
        "TO CONVERT AN SQL STATEMENT INTO THE SYSTEM'S NATIVE SQL GRAMMAR");

      System.out.println();
      System.out.println(
        "  Translate the statement\n\n" +
        "    " + stmt + "\n\n" +
        "  that contains the ODBC escape clause" + odbcEscapeClause + "\n" +
        "  into the system's native SQL grammar:\n");

      // The Java 2 method Connection.nativeSQL() converts the given SQL
      // statement into the system's native SQL grammar.
      String nativeSql = db.con.nativeSQL(stmt);
      if (nativeSql == null)
      {
        System.out.println("Invalid ODBC statement\n");
      }
      else
      {
        System.out.println("    " + nativeSql);
      }

      // disconnect from the 'sample' database
      db.disconnect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e) ;
      jdbcExc.handle();
    }
  } // main
} // DbNative

