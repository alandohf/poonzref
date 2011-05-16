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
// SOURCE FILE NAME: TbPriv.java
//
// SAMPLE: How to grant, display and revoke privileges on a table
//
// SQL Statements USED:
//         GRANT (Table, View, or Nickname Privileges)
//         SELECT
//         REVOKE (Table, View, or Nickname Privileges)
//         COMMIT
//
// Classes used from Util.java are:
//         Db
//         JdbcException
//
// OUTPUT FILE: TbPriv.out (available in the online documentation)
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

class TbPriv
{
  public static void main(String argv[])
  {
    try
    {
      Db db = new Db(argv);

      System.out.println();
      System.out.println(
        "THIS SAMPLE SHOWS HOW TO GRANT, DISPLAY AND REVOKE \n" +
        "PRIVILEGES ON A TABLE.");

      // connect to the 'sample' database
      db.connect();

      grant(db.con);
      display(db.con);
      revoke(db.con);

      // disconnect from the 'sample' database
      db.disconnect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    }
  } // main

  static void grant(Connection con)
  {
    System.out.println();
    System.out.println(
      "----------------------------------------------------------\n" +
      "USE THE SQL STATEMENTS:\n" +
      "  GRANT (Table, View, or Nickname Privileges)\n" +
      "  COMMIT\n" +
      "TO GRANT PRIVILEGES ON A TABLE.");

    System.out.println();
    System.out.println(
      "  GRANT SELECT, INSERT, UPDATE(salary, comm)\n" +
      "    ON TABLE staff\n" +
      "    TO USER user1");

    try
    {
      Statement stmt = con.createStatement();

      stmt.execute("GRANT SELECT, INSERT, UPDATE(salary, comm) " +
                   "  ON TABLE staff" +
                   "  TO USER user1");
      stmt.close();

      System.out.println();
      System.out.println("  COMMIT");
      con.commit();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // grant

  static void display(Connection con)
  {
    System.out.println();
    System.out.println(
      "----------------------------------------------------------\n" +
      "USE THE SQL STATEMENT:\n" +
      "  SELECT\n" +
      "TO DISPLAY PRIVILEGES ON A TABLE.");

    System.out.println();
    System.out.println(
      "  SELECT granteetype, controlauth, alterauth,\n" +
      "         deleteauth, indexauth, insertauth,\n" +
      "         selectauth, refauth, updateauth\n" +
      "    FROM syscat.tabauth\n" +
      "    WHERE grantee = 'USER1' AND\n" +
      "          tabname = 'STAFF'");

    try
    {
      Statement stmt = con.createStatement();
      ResultSet rs = stmt.executeQuery(
        "SELECT granteetype, controlauth, alterauth, " +
        "       deleteauth, indexauth, insertauth, " +
        "       selectauth, refauth, updateauth " +
        "  FROM syscat.tabauth " +
        "  WHERE grantee = 'USER1' AND " +
        "        tabname = 'STAFF' ");

      boolean result = rs.next();
      String  granteetype = rs.getString(1);
      String  controlauth = rs.getString(2);
      String  alterauth = rs.getString(3);
      String  deleteauth = rs.getString(4);
      String  indexauth = rs.getString(5);
      String  insertauth = rs.getString(6);
      String  selectauth = rs.getString(7);
      String  refauth = rs.getString(8);
      String  updateauth = rs.getString(9);

      rs.close();
      stmt.close();

      System.out.println();
      System.out.println(
        "  Grantee Type     = " + granteetype + "\n" +
        "  CONTROL priv.    = " + controlauth + "\n" +
        "  ALTER priv.      = " + alterauth   + "\n" +
        "  DELETE priv.     = " + deleteauth  + "\n" +
        "  INDEX priv.      = " + indexauth   + "\n" +
        "  INSERT priv.     = " + insertauth  + "\n" +
        "  SELECT priv.     = " + selectauth  + "\n" +
        "  REFERENCES priv. = " + refauth     + "\n" +
        "  UPDATE priv.     = " + updateauth);
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // display

  static void revoke(Connection con)
  {
    System.out.println();
    System.out.println(
      "----------------------------------------------------------\n" +
      "USE THE SQL STATEMENTS:\n" +
      "  REVOKE (Table, View, or Nickname Privileges)\n" +
      "  COMMIT\n" +
      "TO REVOKE PRIVILEGES ON A TABLE.");

    System.out.println();
    System.out.println("  REVOKE SELECT, INSERT, UPDATE\n" +
                       "    ON TABLE staff\n" +
                       "    FROM USER user1");

    try
    {
      Statement stmt = con.createStatement();

      stmt.execute("REVOKE SELECT, INSERT, UPDATE " +
                   "  ON TABLE staff" +
                   "  FROM USER user1");
      stmt.close();

      System.out.println();
      System.out.println("  COMMIT");
      con.commit();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // revoke
} // TbPriv

