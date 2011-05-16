//***************************************************************************
// Licensed Materials - Property of IBM
//
// Governed under the terms of the International
// License Agreement for Non-Warranted Sample Code.
//
// (C) COPYRIGHT International Business Machines Corp. 1997 - 2004
// All Rights Reserved.
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//***************************************************************************
//
// SOURCE FILE NAME: GetMessage.java
//
// SAMPLE : How to get error message in the required locale with token
//          replacement. The tokens can be programatically obtained by
//          invoking Sqlaintp using JNI.
//
// JAVA CLASSES USED:
//         Statement
//         ResultSet
//
// Classes used from Util.java are:
//         Db
//
// OUTPUT FILE: GetMessage.out (available in the online documentation)
// Output will vary depending on the JDBC driver connectivity used.
//*************************************************************************
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

import java.io.*;     //JDBC classes           
import java.lang.*;
import java.util.*;
import java.sql.*;

class GetMessage
{
  public static void main(String argv[])
  {
    Connection con = null;
    Statement stmt = null;
    ResultSet rs = null;
    Db db = null;

    try
    {
      db = new Db(argv);
      
      // connect to the 'sample' database
      db.connect();
      con = db.con;
     
      System.out.println
        ("How to get error message in the required locale with token\n" +
        "  replacement. The tokens can be programatically obtained\n" +
        "  by onvoking Sqlaintp API.\n\n");

      stmt = con.createStatement();

      System.out.print("Executing\n"); 
      System.out.print("     SELECT SYSPROC.SQLERRM ('sql551',\n" );
      System.out.print("                             'USERA;UPDATE;");
      System.out.print("SYSCAT.TABLES',\n");
      System.out.print("                             ';',\n"); 
      System.out.print("                             'en_US',\n"); 
      System.out.print("                             1)\n"); 
      System.out.print("       FROM SYSIBM.SYSDUMMY1;\n");

      // Suppose:
      //   'sql551' is sqlcode 
      //   'USERA', 'UPDATE', 'SYSCAT.TABLES' are tokens 
      //   ';' is the delimiter for tokens. 
      //   'en_US' is the locale 
      // If the above information is passed to the scalar function SQLERRM,
      // a message is returned in the specified LOCALE.

      // perform a SELECT against the "org" table in the sample database.
      rs = stmt.executeQuery("SELECT SYSPROC.SQLERRM ('sql551'," +
                                                     "'USERA;" +
                                                     "UPDATE;SYSCAT.TABLES'," +
                                                     "';','en_us'," +
                                                     "1)" +
                               "FROM SYSIBM.SYSDUMMY1");   

      // retrieve and display the result from the SELECT statement
      while (rs.next())
      {
        String message = rs.getString(1);      
        System.out.println("\nThe message is \n" + message); 
      }
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
    finally
    {
      try
      {
        //close the resultset
        rs.close(); 

        // close the Statement
        stmt.close();

        // roll back any changes to the database made by this sample
        con.rollback();

        // disconnect from the 'sample' database
        db.disconnect();
      }
      catch (Exception x)
      { 
        System.out.print("\n Unable to Rollback/Disconnect ");
        System.out.println("from 'sample' database");    
      }
    }
  } // main
} // GetMessage
