//***************************************************************************
// Licensed Materials - Property of IBM
//
// Governed under the terms of the International
// License Agreement for Non-Warranted Sample Code.
//
// (C) COPYRIGHT International Business Machines Corp. 2006
// All Rights Reserved.
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//***************************************************************************
//
// SOURCE FILE NAME: XmlRead.java
//
// SAMPLE: How to read table data
//
// SQL Statements USED:
//         SELECT
//
// JAVA 2 CLASSES USED:
//         Statement
//         PreparedStatement
//         ResultSet
//
// Classes used from Util.java are:
//         Db
//         Data
//         JdbcException
//
// OUTPUT FILE: XmlRead.out (available in the online documentation)
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

import java.util.*;
import java.io.*;
import java.lang.*;
import java.sql.*;


class XmlRead 
{ 
  public static void main(String argv[])
  {
    try
    {
      Db db = new Db(argv);

      System.out.println();
      System.out.println(
        "THIS SAMPLE SHOWS HOW TO READ TABLE DATA.");

      // connect to the 'sample' database
      db.connect();

      // different ways to read table data
      execQuery(db.con);
      execPreparedQuery(db.con);
      execPreparedQueryWithParam(db.con);
      ReadClobData(db.con);
      ReadBlobData(db.con);      

      // disconnect from the 'sample' database
      db.disconnect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    }
  } // main

  static void execQuery(Connection con)
  {
    try
    {
       System.out.println();
       System.out.println(
          "----------------------------------------------------------\n" +
          "USE THE JAVA 2 CLASS:\n" +
          "  Statement\n" +
          "TO EXECUTE A QUERY.");

       Statement stmt = con.createStatement();

       // execute the query
       System.out.println();
       System.out.println(
         " Execute Statement:\n" +
         " SELECT cid,XMLSERIALIZE(info as varchar(600) " +
         " FROM customer WHERE cid < 1005");

       ResultSet rs = stmt.executeQuery(
          " SELECT cid,XMLSERIALIZE(info as varchar(600)) " +
          "FROM customer WHERE cid < 1005 ");

       System.out.println();
       System.out.println("  Results:\n" +
                        "   CUSTOMERID    CUSTOMERINFO \n" +
                        "   ----------    --------------");
      
       int customerid = 0;
       String customerInfo = "";

       while (rs.next())
       {
          customerid = rs.getInt(1);
          customerInfo= rs.getString(2);

          System.out.println("    " +
                            Data.format(customerid,10) + " " +
                            Data.format(customerInfo, 1024));
       }
     
       rs.close();
       stmt.close();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // execQuery

  static void execPreparedQuery(Connection con)
  {
    try
    {
      System.out.println();
      System.out.println(
          "-----------------------------------------------\n" +
          "USE THE JAVA 2 CLASS:\n" +
          "  PreparedStatement\n" +
          "TO EXECUTE A PREPARED QUERY.");

      Statement stmt = con.createStatement();

      // prepare the query
      System.out.println();
      System.out.println(
        "  Prepare Statement:\n" +
        "  SELECT cid,XMLSERIALIZE(info as varchar(600)"+
        "  FROM customer WHERE cid < 1005");

      PreparedStatement pstmt = con.prepareStatement(
         " SELECT cid,XMLSERIALIZE(info as varchar(600)) "+
         " FROM customer WHERE cid < 1005 ");

      System.out.println();
      System.out.println("  Execute prepared statement");
      ResultSet rs = pstmt.executeQuery();

      System.out.println();
      System.out.println("  Results:\n" +
                       "    CUSTOMERID    CUSTOMERINFO\n" +
                       "    ----------    --------------");

      int customerid = 0;
      String customerInfo = "";
      
      while (rs.next())
      {
         customerid = rs.getInt(1);
         customerInfo= rs.getString(2);

         System.out.println("    " +
                 Data.format(customerid,10) + " " +
                 Data.format(customerInfo, 1024));      
      }
      rs.close();
      stmt.close();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } //execPreparedQuery

  static void execPreparedQueryWithParam(Connection con)
  {
    try
    {
      System.out.println();
      System.out.println(
        "----------------------------------------------------\n" +
        "USE THE JAVA 2 CLASS:\n" +
        "  PreparedStatement\n" +
        "TO EXECUTE A PREPARED QUERY WITH PARAMETERS.");

      Statement stmt = con.createStatement();

      // prepare the query
      System.out.println();
      System.out.println(
        "  Prepare Statement:\n" +
        "  SELECT cid,XMLSERIALIZE(info as varchar(600)"+
        "  FROM customer WHERE cid < ? ");

      PreparedStatement pstmt = con.prepareStatement(
          " SELECT cid,XMLSERIALIZE(info as varchar(600))" +
          " FROM customer WHERE cid < ? ");
 

      System.out.println();
      System.out.println("  Set parameter value: parameter 1 = 1005");

      pstmt.setInt(1, 1005);

      System.out.println();
      System.out.println("  Execute prepared statement");
      ResultSet rs = pstmt.executeQuery();

      System.out.println();
      System.out.println("  Results:\n" +
                       "    CUSTOMERID    CUSTOMERINFO\n" +
                       "    ----------    --------------");

      int customerid = 0;
      String customerInfo = "";

      while (rs.next())
      {
         customerid = rs.getInt(1);
         customerInfo= rs.getString(2);

         System.out.println("    " +
                  Data.format(customerid,10) + " " +
                  Data.format(customerInfo, 1024));
      }
      rs.close();
      stmt.close();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } //execPreparedQueryWithParam

  static void ReadClobData(Connection con)
  {
    try
    {
      int customerid = 0;
      String customerInfo = "";

      String cursorName = "";
      String xmlData = "";
      // Create a CLOB object
      java.sql.Clob clobData =
          com.ibm.db2.jcc.t2zos.DB2LobFactory.createClob(xmlData);

      System.out.println();
      System.out.println(" READ CLOB DATA FROM XML COLUMN\n");

      System.out.println("SELECT cid, XMLSERIALIZE(info as clob)" +
                        " from customer where cid < 1005");

      Statement stmt = con.createStatement();
      ResultSet rs = stmt.executeQuery( 
                      "SELECT cid, XMLSERIALIZE(info as Clob)" +
                      " from customer where cid < 1005");
      //cursorName = rs.getCursorName();

      String temp_clob = null;

      while(rs.next())
      {
         customerid = rs.getInt(1);

         System.out.println("     " +
                           Data.format(customerid, 10) + "    ");
         
         Clob clob = rs.getClob(2);
         long clob_length = clob.length(); 
         temp_clob = clob.getSubString(1,(int) clob_length);;
         //String temp_blob = clobData.getString(2);
         System.out.println(temp_clob);
      }
    }
    catch( Exception e)
    {
      System.out.println(e);
    }
  } //ReadClobData

  static void ReadBlobData(Connection con)
  {
    try
    {
      int customerid = 0;
      Blob blobData = null;

      System.out.println();
      System.out.println(" READ BLOB DATA FROM XML COLUMN\n");


      System.out.println("SELECT cid, " +
                        "XMLSERIALIZE(info as blob)" +
                        " from customer where cid < 1005");

      PreparedStatement pstmt = con.prepareStatement(
                 "  SELECT cid, XMLSERIALIZE(info as blob)"+
                 "  from customer where cid < 1005 ");
      ResultSet rs = pstmt.executeQuery();

      while(rs.next())
      {

         customerid = rs.getInt(1);

         System.out.println("     " +
                           Data.format(customerid, 10) + "    ");

         Blob blob = rs.getBlob(2);
         byte[] Array=blob.getBytes(1, (int) blob.length());
         String temp_string = "";
         for (int i =0; i < Array.length; i++ )
         {
           char temp_char;
           temp_char = (char)Array[i];
           temp_string += temp_char;
         }

         System.out.println(temp_string);
         System.out.println();
       

      }
    }
    catch (Exception e)
    {
      System.out.println(e);
    }
  } //ReadBlobData
}
