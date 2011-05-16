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
// SOURCE FILE NAME: AdmCmdUpdateCfg.java
//
// SAMPLE: How to update and reset the Database configuration and Database 
//         Manager Configuration Parameters 
//
// JAVA 2 CLASS USED:
//         CallableStatement
//
// Class used from Util.java are:
//         Db
//         JdbcException
//
// OUTPUT FILE: AdmCmdUpdateCfg.out (available in the online 
//                                   documentation)
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

import java.io.*;
import java.lang.*;
import java.util.*;
import java.sql.*;

class AdmCmdUpdateCfg 
{

  public static void main(String argv[])
  {
    Connection con = null;
    Db db = null;  
    CallableStatement callStmt = null;
    try
    {
      db = new Db(argv);

      System.out.print("\nTHIS SAMPLE SHOWS HOW TO UPDATE AND RESET THE"); 
      System.out.print(" DB CFGAND DBM CFG PARAMETERS USING ADMIN_CMD.\n");
    
      // connect to the 'sample' database
      db.connect();
      con = db.con;

      // prepare the CALL statement for ADMIN_CMD
      String sql = "CALL SYSPROC.ADMIN_CMD(?)";
      callStmt = con.prepareCall(sql);
        
      // update the Database configuration Parameter dbheap to 1500 
      String param = "UPDATE DATABASE CONFIGURATION USING DBHEAP 1500";

      // set the input parameter  
      callStmt.setString(1, param);

      System.out.println("\nCALL ADMIN_CMD('" + param + "')");
      // call the stored procedure
      callStmt.execute();
      
      System.out.print("The DB CFG parameter is updated successfully.\n");
    
      // update the Database Manager Configuration 
      // Parameter aslheapsz to 1000 
      param = "UPDATE DATABASE MANAGER CONFIGURATION using ASLHEAPSZ 1000";

      // set the input parameter  
      callStmt.setString(1, param);
      System.out.println("\nCALL ADMIN_CMD('" + param + "')");

      // call the stored procedure
      callStmt.execute();

      System.out.print("The DBM CFG parameter is updated successfully.\n");
 
      // reset the DB CFG parameters for SAMPLE 
      param = "RESET DB CFG FOR SAMPLE";

      // set the input parameter  
      callStmt.setString(1, param);
      System.out.println("\nCALL ADMIN_CMD('" + param + "')");

      // call the stored procedure
      callStmt.execute();
      System.out.print("The DB CFG parameters for SAMPLE DB are"); 
      System.out.print(" resetted successfully.\n");

      // reset the DBM CFG parameters 
      param = "RESET DBM CFG";

      // set the input parameter  
      callStmt.setString(1, param);
      System.out.println("\nCALL ADMIN_CMD('" + param + "')");

      // call the stored procedure
      callStmt.execute();
      
      System.out.print("The DBM CFG parameters are resetted successfully\n");
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
        // close the callStmt
        callStmt.close();

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
} // AdmCmdUpdateCfg 
