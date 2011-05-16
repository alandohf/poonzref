//***************************************************************************
// Licensed Materials - Property of IBM
//
// Governed under the terms of the International
// License Agreement for Non-Warranted Sample Code.
//
// (C) COPYRIGHT International Business Machines Corp. 1997 - 2006
// All Rights Reserved.
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//***************************************************************************
//
// SOURCE FILE NAME: GetDBMCfgParams.java
//
// SAMPLE: Use the view SYSIBMADM.DBMCFG to retrieve a database 
//         manager configuration parameter.
//
// Run this sample using the following steps:
//         1. Create and populate the "sample" database 
//            with the following command:
//            db2sampl
//
//         2. Compile the program with the following command:
//            javac GetDBMCfgParams.java Util.java
//
//         3. Run this sample with the following command:
//            java GetDBMCfgParams <configuration parameter names>
//
// JAVA 2 CLASSES USED:
//         Statement
//         ResultSet
//
// Class used from Util.java are:
//         JdbcException
//
// OUTPUT FILE: GetDBMCfgParams.out (available in the online documentation)
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

class GetDBMCfgParams
{
  public static void main(String argv[])
  {    
  
    System.out.print("--------------------------------------------------");
    System.out.println("----------------------------------------");         
    System.out.print("THIS SAMPLE SHOWS HOW TO CALL THE UDF DBM_GET_CFG ");
    System.out.println("AND RETRIEVE DBM CONFIGURATION PARAMETERS.");
    System.out.print("--------------------------------------------------");    
    System.out.println("----------------------------------------");        
    Connection con = null;
    Statement stmt = null;
    ResultSet rs = null;

    if (argv.length < 1)
    {
      System.out.print("Missing input arguments. Enter one or");
      System.out.println(" more configuration parameter names.");
    }
    else
    {           
      try
      {
        // initialize DB2Driver and establish database connection.
        COM.ibm.db2.jdbc.app.DB2Driver db2Driver =
          (COM.ibm.db2.jdbc.app.DB2Driver)
            Class.forName("COM.ibm.db2.jdbc.app.DB2Driver").newInstance();
        con = DriverManager.getConnection("jdbc:db2:SAMPLE");

        // create the SQL statement and execute.
        stmt = con.createStatement();
  
        String whereClause = "WHERE NAME IN (";
        
        for (int i = 0; i < argv.length; i++)
        {
          whereClause += "'" + argv[i].trim() + "',";
        }
        
        whereClause = whereClause.substring(0, whereClause.length()-1) + ")";
 
        String stmtText = "SELECT NAME, VALUE, DEFERRED_VALUE, DATATYPE " +
                          "FROM SYSIBMADM.DBMCFG " + 
                          whereClause;
                          
        System.out.println(stmtText);

        rs = stmt.executeQuery(stmtText);

        while (rs.next()) 
        {        
          String paramName = rs.getString("NAME").trim();
          String paramValue = rs.getString("VALUE");
          String paramDeferredValue = rs.getString("DEFERRED_VALUE");
          String paramType = rs.getString("DATATYPE").trim();
        
          paramValue = (paramValue == null) ? "" : paramValue.trim();
          paramDeferredValue = (paramDeferredValue == null) ? 
                                 "" : paramDeferredValue.trim();
          System.out.println();
          System.out.println("Parameter Name           = " + paramName);
          System.out.println("Parameter Value          = " + paramValue);
          System.out.print("Parameter Deferred Value = ");
          System.out.println(paramDeferredValue);
          System.out.println("Parameter Data Type      = " + paramType);
                        
          // cast parameter value to appropriate type if needed.
          if (paramType.equals("INTEGER")) 
          {
            int value = Integer.parseInt(paramValue);
          }
          else if (paramType.equals("BIGINT")) 
          {
            long value = Long.parseLong(paramValue);
          }
          else if (paramType.equals("DOUBLE"))
          {
            double value = Double.parseDouble(paramValue);
          }
          else if (paramType.startsWith("VARCHAR"))
          {
            String value = paramValue;
          }
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
          // close the resultset
          rs.close();      

          // close the statement
          stmt.close();
    
          // close the connection
          con.close();   
        }
        catch (Exception x)
        { 
          System.out.print("\n Unable to Rollback/Disconnect ");
          System.out.println("from 'sample' database"); 
        }
      }
    }
  } // main
} // GetDBMCfgParams
