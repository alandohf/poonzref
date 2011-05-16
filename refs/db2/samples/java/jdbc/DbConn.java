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
// SOURCE FILE NAME: DbConn.java
//
// SAMPLE: How to connect to or disconnect from a database
//
// Classes used from Util.java are:
//         Db
//         JdbcException
//
// OUTPUT FILE: DbConn.out (available in the online documentation)
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

import java.sql.*;

class DbConn
{
  public static void main(String argv[])
  {
    try
    {
      Db  db = new Db(argv);

      System.out.println();
      System.out.println(
        "THIS SAMPLE SHOWS " +
        "HOW TO CONNECT TO/DISCONNECT FROM DATABASES.");

      System.out.println();
      System.out.println(
        "----------------------------------------------------------\n" +
        "USE JAVA 2 CLASSES:\n" +
        "  Connection\n" +
        "  DriverManager\n" +
        "TO CONNECT TO/DISCONNECT FROM A DATABASE.");

      // connect to the 'sample' database
      db.connect();

      // disconnect from the 'sample' database
      db.disconnect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    }
  } // main
} // DbConn

