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
// SOURCE FILE NAME: DbInfo.java
//
// SAMPLE: How to get/set info in a database
//
// JAVA 2 CLASSES USED:
//         DatabaseMetaData
//         ResultSet
//
// Classes used from Util.java are:
//         Db
//         Data
//         JdbcException
//
// OUTPUT FILE: DbInfo.out (available in the online documentation)
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

class DbInfo
{
  public static void main(String argv[])
  {
    try
    {
      Db db = new Db(argv);

      System.out.println();
      System.out.println(
        "THIS SAMPLE SHOWS HOW TO GET/SET INFO ABOUT DATABASES.");

      // connect database
      db.connect();

      // Get information in a database
      infoGet(db.con);
      db.con.commit();

      // disconnect database
      db.disconnect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e) ;
      jdbcExc.handle();
    }
  } // main

  static void infoGet(Connection con)
  {
    System.out.println();
    System.out.println(
      "--------------------------------------------------------\n" +
      "USE THE JAVA APIs:\n" +
      "  DatabaseMetaData.getSchemas()\n" +
      "  ResultSet.getMetaData()\n" +
      "  DatabaseMetaData.getURL()\n" +
      "  DatabaseMetaData.isReadOnly()\n" +
      "  DatabaseMetaData.supportsPositionedDelete()\n" +
      "TO GET INFORMATION AT THE DATABASE LEVEL.");

    try
    {
      DatabaseMetaData dbMetaData = con.getMetaData();

      System.out.println();
      System.out.println("  Information of The current database:\n");

      // Get the schema names available in this database
      ResultSet rs = dbMetaData.getSchemas();
      System.out.println("    Schema names: ");
      String schemaName;

      while (rs.next())
      {
        schemaName = rs.getString(1);
        System.out.println("                                 " + schemaName);
      }
      rs.close();
      System.out.println();

      // Get the URL for this database
      String url = dbMetaData.getURL();
      System.out.println("    Database URL:                " + url);

      // Is the database in read-only mode?
      boolean isReadOnly = dbMetaData.isReadOnly();
      System.out.println();
      System.out.println("    Database is Read-only:       " + isReadOnly);

      // Is positional DELETE supported?
      boolean isPosDelete = dbMetaData.supportsPositionedDelete();
      System.out.println();
      System.out.println("    Positioned DELETE supported: " + isPosDelete);
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // infoGet
} // DbInfo

