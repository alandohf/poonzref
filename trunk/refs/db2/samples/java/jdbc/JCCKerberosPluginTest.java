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
// SOURCE FILE NAME: JCCKerberosPluginTest.java
//
// This set of sample shows
//
// 1. How to implement a JCC plugin which does Kerberos authentication
// 2. How to use this sample plugin to get a Connection.
//
// In order to implement a JCC plugin in, user needs to extend com.ibm.db2.jcc.DB2JCCPlugin
// and implement the following method:
// public abstract byte[] getTicket (String username, String password, 
//                                   byte[] returnedToken) throws org.ietf.jgss.GSSException;
//
// User also needs to implement some JGSS APIs
//
// This set of sample implements a plugin that does kerberos authentication.
// It uses Kerberos implementation in jgss package
// It corresponds to the c sample plugin IBMkrb5 in sqllib\samples\securtiy\plugins
//
// This set of samples contain the following 3 files:
//
// JCCKerberosPluginTest.java
// This file uses sample plugin JCCKerberosPlugin to get a Connection from DB2 server
//
// JCCKerberosPlugin.java
// This file implements the sample JCCKerberosPlugin.
//
// JCCSimpleGSSException.java
// used by JCCKerberosPlugin for Exception handling
// How to run this JCCKerberosPlugin sample
//
//   Compile the above 3 files using javac *.java
//   Run JCCKerberosPluginTest using
//   java JCCKerberosPluginTest server port dbname userid password serverPrincipalName
//
// Note: To run this sample, server side plugin IBMkrb5 needs to be installed in
//       the server plug-in directory on the server. Database manager configuration
//       parameters SRVCON_GSSPLUGIN_LIST and SRVCON_AUTH need to set correctly
//
// OUTPUT FILE: None
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

public class JCCKerberosPluginTest
{
  public static void main (String[] args) throws Exception
  {

     if(args.length != 6)
       throw new Exception("Usage: program_name [server] [port] [dbname] [userid] [password] [serverPrincipalName]");
     String ServerName = args[0];
     int PortNumber = (new Integer(args[1])).intValue();
     String DatabaseName = args[2];
     String userid = args[3];
     String password = args[4];
     String serverPrincipalName = args[5];

     String url = "jdbc:db2://" + ServerName + ":"+ PortNumber + "/" +  DatabaseName ;

      java.util.Properties properties = new java.util.Properties();
      properties.put("user", userid);
      properties.put("password", password);
      properties.put("pluginName", "IBMkrb5");
      properties.put("securityMechanism",
                     new String("" + com.ibm.db2.jcc.DB2BaseDataSource.PLUGIN_SECURITY + ""));
      properties.put("plugin", new JCCKerberosPlugin( serverPrincipalName) );

      java.sql.Connection con = null;
      try
      {
              Class.forName("com.ibm.db2.jcc.DB2Driver").newInstance();
      }
      catch ( Exception e )
      {
                System.out.println("Error: failed to load Db2 jcc driver.");
      }

      try
      {
          con = java.sql.DriverManager.getConnection(url, properties);
          System.out.println("Connected through JCC Type 4 driver using JCCKerberosPlugin");

      }
      catch (Exception e)
      {
         System.out.println("Error occurred when getting a Connection. " + e.getMessage());
      }

  }
}
