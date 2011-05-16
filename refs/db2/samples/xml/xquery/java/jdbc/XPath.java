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
// SOURCE FILE NAME: XPath.java
//
// SAMPLE: How to run Queries with a simple path expression 
//            
// EXTERNAL DEPENDECIES: NULL
//
// SQL STATEMENTS USED:
//         SELECT
//
// JAVA 2 CLASSES USED:
//           Statement
//           PreparedStatement
//           ResultSet
//
// SQL/XML STATEMENTS USED:
//           xmlcolumn 
//
// XQuery FUNCTIONS USED:
//                distinct-values
//                starts-with
//                avg
//               count 
//
// OUTPUT FILE: XPath.out (available in the online documentation)
//***************************************************************************
//
// For more information on the sample programs, see the README file.
//
// For information on developing JDBC applications, see the Application
// Development Guide.
//
// For information on using SQL statements, see the SQL Reference.
//
// For information on using XQuery statements, see the XQuery Reference.
//
// For the latest information on programming, compiling, and running DB2
// applications, visit the DB2 application development website at
//     http://www.software.ibm.com/data/db2/udb/ad
//**************************************************************************/

import java.lang.*;
import java.sql.*;
import java.io.*;
import java.util.*;
import com.ibm.db2.jcc.DB2Xml;

class XPath 
{
  public static void main(String argv[])
  {
    int rc=0;
    String url = "jdbc:db2:sample";
    Connection con=null;
    try
    {
      Class.forName("com.ibm.db2.jcc.DB2Driver").newInstance();
      // connect to the 'sample' database
      con = DriverManager.getConnection( url );
      System.out.println();
      System.out.println("This sample will demonstrate how to use simple path expression in XQuery");     
    } 
    catch (SQLException sqle)
    {
      System.out.println("Error Msg: "+ sqle.getMessage());
      System.out.println("SQLState: "+sqle.getSQLState());
      System.out.println("SQLError: "+sqle.getErrorCode());
      System.out.println("Rollback the transaction and quit the program");
      System.out.println();
      try { con.rollback(); }
      catch (Exception e)
      {
      }
      System.exit(1);
    }
    catch(Exception e)
    {}

    System.out.println("----------------------------------------------------------------");
    System.out.println("Select the customer information ........");
    CustomerDetails(con);

    System.out.println("------------------------------------------------------------------");
    System.out.println("Select the customer's cities from Canada .....");
    CitiesInCanada(con);

    System.out.println("-------------------------------------------------------------------");
    System.out.println("Return the name of customers whose mobile number starts with 905.......");
    CustMobileNum(con);
    
    System.out.println("--------------------------------------------------------------------");
    System.out.println("Return the average price of all products in the 100 series.....");
    AvgPrice(con);

    System.out.println("---------------------------------------------------------------------");         
    System.out.println("Return the customers from Toronto.......");
    CustomerFromToronto(con);

    System.out.println("--------------------------------------------------------------------");
    System.out.println("Return the number of customers from Toronto.......");  
    NumOfCustInToronto(con);
  }// main

  //The CustomerDetails method returns all of the XML data in the INFO column of the CUSTOMER table 
  static void CustomerDetails(Connection con)
  {
    try
    {
      Statement stmt = con.createStatement();
      String query="XQUERY db2-fn:xmlcolumn('CUSTOMER.INFO')";
      System.out.println();
      System.out.println(query);
      ResultSet rs = stmt.executeQuery(query);

      // retrieve and display the result from the xquery 
      while (rs.next())
      {
        // getting the XML value in a string object
        String data=rs.getString(1);
       
        // Print the result  
        System.out.println(); 
        System.out.println(data);
      }
      
      // Close the result set
      rs.close();
      
      // Close the statement
      stmt.close();
    }
    catch(SQLException sqle)
    {
      System.out.println("Error Msg: "+ sqle.getMessage());
      System.out.println("SQLState: "+sqle.getSQLState());
      System.out.println("SQLError: "+sqle.getErrorCode());
      System.out.println("Rollback the transaction and quit the program");
      System.out.println();
      try { con.rollback(); }
      catch (Exception e) {}
      System.exit(1);
    }
  } // CustomerDetails
 
  //The CitiesInCanada method returns a list of cities that are in Canada
  static void CitiesInCanada(Connection con)
  {
    try
    {
      Statement stmt = con.createStatement();
      String query="XQUERY fn:distinct-values(db2-fn:xmlcolumn('CUSTOMER.INFO')"+
                   "/customerinfo/addr[@country=\"Canada\"]/city)";
      System.out.println(); 
      System.out.println(query);
      ResultSet rs = stmt.executeQuery(query);

      // retrieve and display the result from the query 
      while (rs.next())
      {
        // retrieve the data as binary stream
        InputStream data=rs.getBinaryStream(1);
        
        // Print the result 
        System.out.println(); 
         dispValue(data);
      }
      
      // Close the resultset
      rs.close();
      
      // Close the statement
      stmt.close();
    }
    catch(SQLException sqle)
    {
      System.out.println("Error Msg: "+ sqle.getMessage());
      System.out.println("SQLState: "+sqle.getSQLState());
      System.out.println("SQLError: "+sqle.getErrorCode());
      System.out.println("Rollback the transaction and quit the program");
      System.out.println();
      try { con.rollback(); }
      catch (Exception e) {}
      System.exit(1);
    }
  } // CitiesInCanada

  //The CustMobileNum method returns the names of customers whose mobile number starts with 905
  static void CustMobileNum(Connection con)
  {
    try
    {
      Statement stmt = con.createStatement();
      String query="XQUERY db2-fn:xmlcolumn(\"CUSTOMER.INFO\")"+
                           "/customerinfo[phone[@type=\"cell\" and fn:starts-with(text(),\"905\")]]"; 
      System.out.println();
      System.out.println(query);
      ResultSet rs = stmt.executeQuery(query);

      // retrieve and display the result from the query 
      while (rs.next())
      {
        com.ibm.db2.jcc.DB2Xml data=(com.ibm.db2.jcc.DB2Xml) rs.getObject(1);
        
        // Print the result as DB2 XML String
        System.out.println();
        System.out.println(data.getDB2String());
      }
      
      // Close the result set
      rs.close();
      
      // Close the statement
      stmt.close();
    }
    catch(SQLException sqle)
    {
      System.out.println("Error Msg: "+ sqle.getMessage());
      System.out.println("SQLState: "+sqle.getSQLState());
      System.out.println("SQLError: "+sqle.getErrorCode());
      System.out.println("Rollback the transaction and quit the program");
      System.out.println();
      try { con.rollback(); }
      catch (Exception e) {}
      System.exit(1);
    }
  } // CustMobileNum

  // The AvgPRice method determines the average prive of the products in the 100 series
  static void AvgPrice(Connection con)
  {
    try
    {
      Statement stmt = con.createStatement();
      String query="XQUERY let $prod_price := db2-fn:xmlcolumn('PRODUCT.DESCRIPTION')"+
                             "/product[fn:starts-with(@pid,\"100\")]/description/price"+
                              " return avg($prod_price)";
      System.out.println(); 
      System.out.println(query);
      ResultSet rs = stmt.executeQuery(query);

      // retrieve and display the result from the query 
      while (rs.next())
      {
        com.ibm.db2.jcc.DB2Xml data=(com.ibm.db2.jcc.DB2Xml) rs.getObject(1);
        
        // Print the result as DB2 String 
        System.out.println(); 
        System.out.println(data.getDB2String());
      }
      
      // Close the result set
      rs.close();
      
      // Close the statement
      stmt.close();
    }
    catch(SQLException sqle)
    {
      System.out.println("Error Msg: "+ sqle.getMessage());
      System.out.println("SQLState: "+sqle.getSQLState());
      System.out.println("SQLError: "+sqle.getErrorCode());
      System.out.println("Rollback the transaction and quit the program");
      System.out.println();
      try { con.rollback(); }
      catch (Exception e) {}
      System.exit(1);
    }
  } // AvgPrice
  
  //The CustomerFromToronto method returns information about customers from Toronto 
  static void CustomerFromToronto(Connection con)
  {
    try
    {
      Statement stmt = con.createStatement();
      String query="XQUERY db2-fn:xmlcolumn (\"CUSTOMER.INFO\")/customerinfo[addr/city=\"Toronto\"]";
      System.out.println(); 
      System.out.println(query);
      ResultSet rs = stmt.executeQuery(query);

      // retrieve and display the result from the query 
      while (rs.next())
      {
        com.ibm.db2.jcc.DB2Xml data=(com.ibm.db2.jcc.DB2Xml) rs.getObject(1);
        
        // Print the result as DB2 String 
        System.out.println(); 
        System.out.println(data.getDB2String());
      }
      
      // Close the result set
      rs.close();
      
      // Close the statement
      stmt.close();
    }
    catch(SQLException sqle)
    {
      System.out.println("Error Msg: "+ sqle.getMessage());
      System.out.println("SQLState: "+sqle.getSQLState());
      System.out.println("SQLError: "+sqle.getErrorCode());
      System.out.println("Rollback the transaction and quit the program");
      System.out.println();
      try { con.rollback(); }
      catch (Exception e) {}
      System.exit(1);
    }
  } // CustomerFromToronto
  
  // The NumOfCustInToronto method returns the number of customer from Toronto city 
  static void NumOfCustInToronto(Connection con)
  {
    try
    {
      Statement stmt = con.createStatement();
      String query="XQUERY fn:count(db2-fn:xmlcolumn(\"CUSTOMER.INFO\")/customerinfo[addr/city=\"Toronto\"])";
      System.out.println(); 
      System.out.println(query);
      ResultSet rs = stmt.executeQuery(query);

      // retrieve and display the result from the query 
      while (rs.next())
      {
        com.ibm.db2.jcc.DB2Xml data=(com.ibm.db2.jcc.DB2Xml) rs.getObject(1);
        
        // Print the result as DB2 String
        System.out.println();
        System.out.println(data.getDB2String());
      }
      
      // Close the result set
      rs.close();
      
      // Close the statement
      stmt.close();
    }
    catch(SQLException sqle)
    {
      System.out.println("Error Msg: "+ sqle.getMessage());
      System.out.println("SQLState: "+sqle.getSQLState());
      System.out.println("SQLError: "+sqle.getErrorCode());
      System.out.println("Rollback the transaction and quit the program");
      System.out.println();
      try { con.rollback(); }
      catch (Exception e) {}
      System.exit(1);
    } 
  } // NumOfCustInToronto
  public static void dispValue(InputStream in)
  {
        int size;
        byte buf;
        int count = 0;
        try
        {
             size = in.available();
             byte ary[] = new byte[size];
             buf = (byte) in.read();
             while(buf!=-1)
            {
                  ary[count] = buf;
                  count++;
                  buf = (byte) in.read();
            }
            System.out.println(new String(ary));
        }
        catch (Exception e)
        {
             System.out.println("Error occured while reading stream ... \n");
        }
  } // dispValue
} //XPath
