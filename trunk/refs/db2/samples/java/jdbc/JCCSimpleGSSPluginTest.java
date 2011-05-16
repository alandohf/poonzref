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
// SOURCE FILE NAME: JCCSimpleGSSPluginTest.java
// SAMPLE: Get a DB2 Connection using plugin security
//
// This set of sample shows:
// 1. How to implement a JCC GSS-API plugin sample which does a userid and password check
// 2. How to use this sample plugin to get a Connection
//
// This sample plugin corresponds to the c sample plugin
// gssapi_simple in sqllib\samples\securtiy\plugins
//
// This set of sample contains the following 6 files:
//
// JCCSimpleGSSPluginTest.java
// This file uses sample plugin JCCSimpleGSSPlugin to get a Connection from DB2 server
//
// JCCSimpleGSSPlugin.java
// This file implements the sample JCCSimpleGSSPlugin that does a userid and password check.
//
// JCCSimpleGSSContext.java
// This file is used by JCCSimpleGSSPlugin.java to implement the plugin sample.
//
// JCCSimpleGSSCredential.java
// This file is used by JCCSimpleGSSPlugin.java to implement the plugin sample.
//
// JCCSimpleGSSException.java
// This file is used by JCCSimpleGSSPlugin.java to handle Exceptions
//
// JCCSimpleGSSName.java
// This file is used by JCCSimpleGSSPlugin.java to implement the plugin sample.
//
// how to run this JCCSimpleGSSPlugin sample
//
// compile the above 6 files using javac *.java
// Run JCCSimpleGSSPluginTest using
// java JCCSimpleGSSPluginTest server port dbname userid password
// Note: To run this sample, server side plugin gssapi_simple needs to be installed in
//       the server plug-in directory on the  server. Database manager configuration
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
public class JCCSimpleGSSPluginTest
{
  public static void main (String[] args) throws Exception
  {

      if(args.length != 5)
        throw new Exception("Usage: program_name [server] [port] [dbname] [userid] [password]");
      String ServerName = args[0];
      int PortNumber = (new Integer(args[1])).intValue();
      String DatabaseName = args[2];
      String userid = args[3];
      String password = args[4];

      String url = "jdbc:db2://" + ServerName + ":"+ PortNumber + "/" +  DatabaseName;

      java.util.Properties properties = new java.util.Properties();
      properties.put("user", userid);
      properties.put("password", password);
      properties.put("pluginName", "gssapi_simple");
      properties.put("securityMechanism",
                     new String("" + com.ibm.db2.jcc.DB2BaseDataSource.PLUGIN_SECURITY + ""));
      properties.put("plugin", new JCCSimpleGSSPlugin());

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
          System.out.println("Connected through JCC Type 4 driver using JCCSimpleGSSPlugin");

      }
      catch (Exception e)
      {
         System.out.println("Error occurred in getting Connection: "+ e.getMessage());
      }
  }
}
