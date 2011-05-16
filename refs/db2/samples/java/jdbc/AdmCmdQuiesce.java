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
// SOURCE FILE NAME: AdmCmdQuiesce.java
//
// SAMPLE: How to quiesce tablespace and database using ADMIN_CMD
//
// JAVA 2 CLASSES USED:
//         CallableStatement
//
// Classes used from Util.java are:
//         Db
//
// OUTPUT FILE: AdmCmdQuiesce.out (available in the online documentation)
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

import java.io.*;     // JDBC classes
import java.lang.*;
import java.util.*;
import java.sql.*;

class AdmCmdQuiesce 
{

  public static void main(String argv[])
  {
    Connection con = null;

    try
    {
      Db db = new Db(argv);

      System.out.print("\nTHIS SAMPLE SHOW TO QUIESCE TABLESPACES");
      System.out.print("AND DATABASE USING ADMIN_CMD.\n");  
    
      // connect to the 'sample' database
      db.connect();
      con = db.con;

      // prepare the CALL statement for ADMIN_CMD
      String sql = "CALL SYSPROC.ADMIN_CMD(?)";
      CallableStatement callStmt = con.prepareCall(sql);
        
      // quiesce tablespaces for empoyee table 
      String param = "QUIESCE TABLESPACES FOR TABLE EMPLOYEE EXCLUSIVE";

      // set the input parameter  
      callStmt.setString(1, param);
      System.out.println("\nCALL ADMIN_CMD('" + param + "')");
     
      // call the stored procedure
      callStmt.execute();
      
      System.out.print("The quiesce tablespaces for employee ");
      System.out.print("table done successfully\n");

      // quiesce reset of tablespaces of employee table
      param = "QUIESCE TABLESPACES FOR TABLE EMPLOYEE RESET";

      // set the input parameter  
      callStmt.setString(1, param);
      System.out.println("\nCALL ADMIN_CMD('" + param + "')");

      // call the stored procedure
      callStmt.execute();

      System.out.print("The quiesce reset of tablespaces ");
      System.out.print("done successfully\n");
 
      // quiesce database
      param = "QUIESCE DATABASE IMMEDIATE";

      // set the input parameter  
      callStmt.setString(1, param);
      System.out.println("\nCALL ADMIN_CMD('" + param + "')");

      // call the stored procedure
      callStmt.execute();
      System.out.println("The quiesce database done successfully.");

      // unquiesce database 
      param = "UNQUIESCE DB";

      // set the input parameter  
      callStmt.setString(1, param);
      System.out.println("\nCALL ADMIN_CMD('" + param + "')");

      // call the stored procedure
      callStmt.execute();
      System.out.println("The unquiesce database done successfully.");

      // close the callStmt
      callStmt.close();
     
      // rollback changes 
      con.rollback();   
                                
      // disconnect from the 'sample' database
      db.disconnect();  
    }
    catch (Exception e)
    {
      try
      {
        con.rollback();
        con.close();
      }
      catch (Exception x)
      { }

      e.printStackTrace();
    }
  } // main
} // AdmCmdQuiesce 
