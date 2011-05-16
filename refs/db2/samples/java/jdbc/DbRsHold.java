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
// SOURCE FILE NAME: DbRsHold.java
//
// SAMPLE: How to use result set cursor holdability in DB2 JDBC Type 2 Driver
//         for Linux, UNIX and Windows and Universal JDBC driver. The
//         Universal JDBC driver implements the result set cursor holdability
//         APIS specified in JDBC3. To compile this sample, you need JDK1.4
//         or above; To run this sample, you need JRE1.4 or above.
//
// SQL Statements Used:
//         SELECT 
//         UPDATE
//
// Classes used from Util.java are:
//         Db
//         Data
//         JdbcException
//
// OUTPUT FILE: DbRsHold.out (available in the online documentation)
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

import java.io.*;
import java.lang.*;
import java.util.*;
import java.sql.*;
import javax.sql.*;

public class DbRsHold 
{
  // The SQL statements used in this sample
  static final String sqlQuery = "SELECT empno, firstnme, lastname, salary "
                               + "  FROM employee WHERE workdept='A00'";
  static final String sqlUpdt = "SELECT empno, firstnme, lastname, salary\n"
                               + "  FROM employee WHERE workdept='A00'"
                               + "  FOR UPDATE of salary";
  static double salaryInc = 0.0;
    
  public static void main(String[] args)
  {
    if( args.length > 5 ||
        ( args.length == 1 &&
          ( args[0].equals( "?" )               ||
            args[0].equals( "-?" )              ||
            args[0].equals( "/?" )              ||
            args[0].equalsIgnoreCase( "-h" )    ||
            args[0].equalsIgnoreCase( "/h" )    ||
            args[0].equalsIgnoreCase( "-help" ) ||
            args[0].equalsIgnoreCase( "/help" ) ) ) )
    {
      System.out.println(
        "Usage: prog_name [dbAlias] [userId passwd] " + 
                "(use DB2 JDBC type 2 Driver)\n" + 
        "       prog_name -u2 [dbAlias] [userId passwd] " + 
                "(use universal JDBC type 2 driver)\n" + 
        "       prog_name [dbAlias] server portNum userId passwd " + 
                "(use universal JDBC type 4 driver)");
      System.exit(0);
    }

    if(args.length == 0 || 
       (args.length > 0 && args.length <= 3 && 
         !args[0].equalsIgnoreCase("-u2")))
    {
      holdabilityOfLegacyType2(args);
    }
    else
    {
      // Check the JRE version. JRE1.4 or above is required
      String jreVersion = System.getProperty("java.version");
      StringTokenizer token = new StringTokenizer(jreVersion, ".");
      String simpVersion = jreVersion;
        
      if(token.hasMoreTokens())
        simpVersion = token.nextToken();
      if(token.hasMoreTokens())
        simpVersion = simpVersion + "." + token.nextToken();

      float fVersion = (new Float(simpVersion)).floatValue();
      if(fVersion < (float)1.4)
      {
        System.out.println("To run this sample by using the Universal JDBC" +
                           " driver, you need JRE1.4 or above"); 
        System.exit(0);
      }
                            
      holdabilityOfUniversalDriver(args);
    }
    
  } //main 
  
  static void holdabilityOfLegacyType2(String[] args)
  {
    // Db class is used to connect to the database
    // Variable connDd is the connection that displays data in the table
    Db dbDd = null;
    Connection connDd = null;
    
    try
    {
      dbDd = new Db(args);
      connDd = dbDd.connect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    }
    
    // Set cursor holdability at connection level: CURSORHOLD = 1
    System.out.println(
      "-----------------------------------------------------------------\n" +
      "Set cursor holdability at connection level: CURSORHOLD = 1\n");
    salaryInc = 2000.0;
    setHoldabilityLegacyType2(args, 1, connDd);
   
    // Set cursor holdability at connection level: CURSORHOLD = 0
    // SQLException is expected since the cursor will be closed at commit
    System.out.println(
      "-----------------------------------------------------------------\n" +
      "Set cursor holdability at connection level: CURSORHOLD = 0\n" +
      "    'CLI0125E Function sequence error' " + 
      "IS EXPECTED AFTER THE FIRST COMMIT\n");
    setHoldabilityLegacyType2(args, 0, connDd);

    // Recover data in the table
    System.out.println(
      "-----------------------------------------------------------------\n");
    System.out.println("......Data Recovery......");
    salaryInc = -2000.0;
    setHoldabilityLegacyType2(args, 1, connDd);
    
    System.out.println("'CLI0125E Function sequence error' " + 
      "IS EXPECTED AFTER THE FIRST COMMIT\n");
    setHoldabilityLegacyType2(args, 0, connDd);
    System.out.println("......Data Recovery Complete......");
    
    System.out.println(
      "-----------------------------------------------------------------");
    
    try
    {
      dbDd.disconnect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    }

  } //holdabilityOfLegacyType2

  // This method shows how to set cursor holdability by legacy type 2 driver
  static void setHoldabilityLegacyType2(String[] args,
                                        int holdability, 
                                        Connection connDd)
  {
    ResultSet rs = null;
    Connection conn = null;
    String dbUrl = null;
    
    try
    { 
      // Set the connection properties
      Properties connProp = new Properties();
      if(args.length == 2)
      {
        connProp.setProperty("UID", args[0]);
        connProp.setProperty("PWD", args[1]);
      }
      else if (args.length == 3)
      {
      	connProp.setProperty("UID", args[1]);
        connProp.setProperty("PWD", args[2]);
      }
      
      connProp.setProperty("CURSORHOLD", 
                           (new Integer(holdability)).toString());
      
      if (args.length == 1 || args.length == 3)
        dbUrl = "jdbc:db2:" + args[0];
      else 
        dbUrl = "jdbc:db2:sample";

      // Get a connection      
      conn = DriverManager.getConnection(dbUrl, connProp);
      conn.setAutoCommit(false);

      // Create a statement with the holdability of the connection
      Statement stmt = conn.createStatement();

      // Execute the query and obtain the result set
      rs = stmt.executeQuery(sqlUpdt);
      String curName = rs.getCursorName();  

      // Create a statement for updating data
      Statement stmt1 = conn.createStatement();
      System.out.println("Original data:");
      displayData(connDd);
      int num = 1;
      
      while (rs.next())
      {
      	System.out.println("UPDATE salary: row " + num);
        float salary = rs.getFloat("SALARY");
        stmt1.executeUpdate("UPDATE employee" +
                            " SET salary = " + (float)(salary + salaryInc) + 
                            " WHERE CURRENT OF " + curName);
                           
        // If CURSORHOLD is 1, the cursor is still open after commit;
        // If CURSORHOLD is 0, the cursor is closed after commit. 
        conn.commit();
        System.out.println("COMMIT updates: row " + num);

        displayData(connDd);
        num ++;
      }
    } 
    catch (Exception e)
    {     
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    } 
    finally
    {
      try
      {
        if (rs != null)
          rs.close();
        if (conn != null)  
          conn.close();
      }
      catch(Exception e)
      {
        JdbcException jdbcExc = new JdbcException(e);
        jdbcExc.handle();
      }
    }
    
  } //setHoldabilityLegacyType2

  static void holdabilityOfUniversalDriver(String[] args)
  {
    // Db class is used to connect to the database
    // Variable conn is the connection that shows cursor holdability changes
    // Variable connDd is the connection that displays data in the table
    Db db = null;
    Db dbDd = null;
    Connection conn = null;
    Connection connDd = null;
    
    try
    {
      db = new Db(args);
      conn = db.connect();
      dbDd = new Db(args);
      connDd = dbDd.connect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    }
    
    // Print different types of result set cursor holdability
    System.out.println(
      "-----------------------------------------------------------------\n" +
      "ResultSet.HOLD_CURSORS_OVER_COMMIT = " + 
      ResultSet.HOLD_CURSORS_OVER_COMMIT);
    System.out.println(
      "ResultSet.CLOSE_CURSORS_AT_COMMIT = " + 
      ResultSet.CLOSE_CURSORS_AT_COMMIT + "\n");

    // Set cursor holdability at connection level: HOLD_CURSORS_OVER_COMMIT
    System.out.println(
      "-----------------------------------------------------------------\n" +
      "Set cursor holdability at connection level: " + 
      "HOLD_CURSORS_OVER_COMMIT\n");
    salaryInc = 2000.00;
    setHoldabilityAtConnection(conn, 
                               ResultSet.HOLD_CURSORS_OVER_COMMIT, 
                               connDd);

    // Set cursor holdability at connection level: CLOSE_CURSORS_AT_COMMIT
    // SQLException is expected since the cursor will be closed at commit
    System.out.println(
      "-----------------------------------------------------------------\n" +
      "Set cursor holdability at connection level: " +
      "CLOSE_CURSORS_AT_COMMIT\n" +
      "'Result set closed' ERROR IS EXPECTED AFTER THE FIRST COMMIT\n");
    setHoldabilityAtConnection(conn, 
                               ResultSet.CLOSE_CURSORS_AT_COMMIT,
                               connDd);

    // Set cursor holdability at statement level: HOLD_CURSORS_OVER_COMMIT
    System.out.println(
      "-----------------------------------------------------------------\n" +
      "Set cursor holdability at statement level: " +
      "HOLD_CURSORS_OVER_COMMIT");
    salaryInc = -2000.0;
    setHoldabilityAtStatement(conn,
                              ResultSet.HOLD_CURSORS_OVER_COMMIT, 
                              connDd);

    // Set cursor holdability at statement level: CLOSE_CURSORS_AT_COMMIT
    // SQLException is expected since the cursor will be closed at commit
    System.out.println(
      "-----------------------------------------------------------------\n" +
      "Set cursor holdability at statement level: " +
      "CLOSE_CURSORS_AT_COMMIT\n" +
      "'Result set closed' ERROR IS EXPECTED AFTER THE FIRST COMMIT\n");
    setHoldabilityAtStatement(conn, 
                              ResultSet.CLOSE_CURSORS_AT_COMMIT, 
                              connDd);

    System.out.println(
      "-----------------------------------------------------------------");
      
    try
    {
      db.disconnect();
      dbDd.disconnect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    }
    
  } // holdabilityOfUniversalDriver

  // This method shows how to set cursor holdability at the connection level
  static void setHoldabilityAtConnection(Connection conn, 
                                         int holdability, 
                                         Connection connDd)
  {
    ResultSet rs = null;

    try
    {
      // Set cursor holdability at the connection level
      conn.setHoldability(holdability);

      // Print the cursor holdability of the connection
      System.out.println("Connection.getHoldability = " + 
                         conn.getHoldability());

      // Print the database MetaData supports for cursor holdability
      DatabaseMetaData dbMeta = conn.getMetaData();
      System.out.println("DatabaseMetaData.getResultSetHoldability =  " + 
                         dbMeta.getResultSetHoldability());
      System.out.println("  Supports HOLD_CURSORS_OVER_COMMIT = " + 
                         dbMeta.supportsResultSetHoldability(
                         ResultSet.HOLD_CURSORS_OVER_COMMIT));
      System.out.println("  Supports CLOSE_CURSORS_AT_COMMIT = " + 
                         dbMeta.supportsResultSetHoldability(
                         ResultSet.CLOSE_CURSORS_AT_COMMIT));

      // Create a statement with the holdability from the connection
      Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,
                                            ResultSet.CONCUR_UPDATABLE);

      // Print the cursor holdability of the statement, 
      // which should be same as the connection's
      System.out.println("Statement.getResultSetHoldability = " + 
                         stmt.getResultSetHoldability() + "\n");

      // Execute the query and obtain the result set
      rs = stmt.executeQuery(sqlQuery);		

      // Update rows in the result set and commit one by one
      updateData(conn, rs, connDd);

    } 
    catch (Exception e)
    {     
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    } 
    finally
    {
      try
      {
        if (rs != null)
          rs.close();
      }
      catch(Exception e)
      {
        JdbcException jdbcExc = new JdbcException(e);
        jdbcExc.handle();
      }
    }

  } // setHoldabilityAtConnection

  // This method shows how to set cursor holdability at the statement level
  static void setHoldabilityAtStatement(Connection conn, 
                                        int holdability, 
                                        Connection connDd)
  {
    ResultSet rs = null;

    try
    {
      // Print the cursor holdability of the connection
      System.out.println("Connection.getHoldability = " + 
                         conn.getHoldability());

      // Print the database MetaData supports for cursor holdability
      DatabaseMetaData dbMeta = conn.getMetaData();
      System.out.println("DatabaseMetaData.getResultSetHoldability =  " + 
                         dbMeta.getResultSetHoldability());
      System.out.println("  Supports HOLD_CURSORS_OVER_COMMIT = " + 
                         dbMeta.supportsResultSetHoldability(
                         ResultSet.HOLD_CURSORS_OVER_COMMIT));
      System.out.println("  Supports CLOSE_CURSORS_AT_COMMIT = " + 
                         dbMeta.supportsResultSetHoldability(
                         ResultSet.CLOSE_CURSORS_AT_COMMIT));
			
      // Set cursor holdability at the statement level
      // which can override the connection's
      PreparedStatement prepStmt = conn.prepareStatement(sqlQuery, 
                                     ResultSet.TYPE_SCROLL_SENSITIVE, 
                                     ResultSet.CONCUR_UPDATABLE, 
                                     holdability);

      // Print the cursor holdability of the statement, 
      // which can be different from the connection's
      System.out.println("Statement.getResultSetHoldability = " + 
                         (prepStmt).getResultSetHoldability() +
                         "\n");

      // Execute the query and obtain the result set
      rs = prepStmt.executeQuery();	

      // Update rows in the result set and commit one by one
      updateData(conn, rs, connDd);

    } 
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    } 
    finally
    {
      try
      {
        if (rs != null)
          rs.close();
      }
      catch (Exception e)
      {
        JdbcException jdbcExc = new JdbcException(e);
        jdbcExc.handle();
      }
    }

  } // setHoldabilityAtStatement

  // This method updates the rows in the result set and commit one by one.
  // Depending on the result set cursor holdability, the cursor is open or 
  // closed each commits.
  static void updateData(Connection conn, 
                         ResultSet rs, 
                         Connection connDd)
  {
    try
    {
      System.out.println("Original data:");
      displayData(connDd);
      int num = 1;
      
      while (rs.next())
      {
      	System.out.println("UPDATE salary: row " + num);
      	float salary = rs.getFloat("SALARY");
        rs.updateFloat("SALARY", (float)(salary + salaryInc));
        rs.updateRow();

        // If cursor holdability is HOLD_CURSORS_OVER_COMMIT,
        // the cursor is still open after commit;
        // If cursor holdability is CLOSE_CURSORS_AT_COMMIT,
        // the cursor is closed after commit.
        System.out.println("COMMIT updates: row " + num);
        conn.commit();
				
        displayData(connDd);
        num ++;
      }
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    } 

  } // updateData

  // This method is a helping method. It displays the content
  // in the EMPLOYEE table and reflects the data updates.
  static void displayData(Connection connDd)
  {
    ResultSet rs = null;

    try
    {
      // Create a prepared statement to execute the query
      PreparedStatement prepStmt = connDd.prepareStatement(sqlQuery, 
                                   ResultSet.TYPE_FORWARD_ONLY, 
                                   ResultSet.CONCUR_READ_ONLY);

      // Execute the query and obtain the result set
      rs = prepStmt.executeQuery();
	
      // Print the content of the result set
      System.out.println(
        "     EMPNO        NAME          SALARY\n" +
        "     ------ ------------------- ----------");
      while (rs.next())
        System.out.println("     " + Data.format(rs.getString("EMPNO"), 7) + 
                           Data.format(rs.getString("FIRSTNME") + " " + 
                                       rs.getString("LASTNAME"), 20) + 
                           rs.getFloat("SALARY"));
      System.out.println();
      connDd.commit();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    } 
    finally
    {
      try
      {
        if (rs != null)
          rs.close();
       }
      catch (Exception e)
      {
        JdbcException jdbcExc = new JdbcException(e);
        jdbcExc.handle();
      }
    }

  } // displayData
 
} // DbRsHold
