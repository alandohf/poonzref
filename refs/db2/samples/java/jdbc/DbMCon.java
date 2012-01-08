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
// SOURCE FILE NAME: DbMCon.java
//
// SAMPLE: How to use multiple databases
//
//         NOTE:
//         This sample program requires a second database
//         that has to be created as follows:
//           - locally:
//               db2 create db sample2
//           - remotely:
//               db2 attach to node_name
//               db2 create db sample2
//               db2 detach
//               db2 catalog db sample2 as sample2 at node node_name
//
//         In case another name is used for the second database,
//         it can be specified in the command line arguments as
//         follows:
//           java DbMCon "" "dbAlias2 [userid2 passwd2]"
//
//         The second database can be dropped as follows:
//           - locally:
//               db2 drop db sample2
//           - remotely:
//               db2 attach to node_name
//               db2 drop db sample2
//               db2 detach
//               db2 uncatalog db sample2
//
// SQL Statements USED:
//         CREATE TABLE
//         DROP TABLE
//         COMMIT
//
// Classes used from Util.java are:
//         Db
//
// OUTPUT FILE: DbMCon.out (available in the online documentation)
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

class DbMCon
{
  public static void main(String argv[])
  {
    Db db1 = new Db();
    Db db2 = new Db();

    try
    {
      setup( argv, db1, db2 );

      System.out.println();
      System.out.println(
        "THIS SAMPLE SHOWS HOW TO USE MULTIPLE DATABASES.");

      System.out.println("------------------------------------------------");
      db1.connect();
      createTable( db1.con );
      dropTable( db1.con );
      db1.disconnect();
      System.out.println("------------------------------------------------");

      db2.connect();
      createTable( db2.con );
      dropTable( db2.con );
      db2.disconnect();
      System.out.println("------------------------------------------------");
    }
    catch (Exception e)
    {
      System.out.println(e);
    }
  } // main


  private static void setup( String argv[], Db db1, Db db2 ) throws Exception
  {
    if( argv.length > 11 ||
        ( argv.length == 1 &&
          ( argv[0].equals( "?" )               ||
            argv[0].equals( "-?" )              ||
            argv[0].equals( "/?" )              ||
            argv[0].equalsIgnoreCase( "-h" )    ||
            argv[0].equalsIgnoreCase( "/h" )    ||
            argv[0].equalsIgnoreCase( "-help" ) ||
            argv[0].equalsIgnoreCase( "/help" ) ) ) )
    {
      throwUsageException();
    }

    // Initialize default database names
    db1.alias      = "sample";
    db1.server     = "";
    db1.portNumber = 0;
    db1.userId     = "";
    db1.password   = "";

    db2.alias      = "sample2";
    db2.server     = "";
    db2.portNumber = 0;
    db2.userId     = "";
    db2.password   = "";

    switch (argv.length) {
      case 0:	// Use type 2 driver
	break;
	
      case 1:
        if ( argv[0].equalsIgnoreCase("-u2") ) {
	  // type 2 Universal
	  db1.portNumber = -1;
	  db2.portNumber = -1;
			
	  // Use the defaults
	} 
	else
	{
	  // Use type 2 driver with db name specified
	  db1.alias      = argv[0];
	}
	break;
	
      case 2:
	if ( argv[0].equalsIgnoreCase("-u2") ) {
    	  // type 2 Universal
	  db1.portNumber = -1;
	  db2.portNumber = -1;
	  db1.alias      = argv[0];
	} 
	else
	{	
	  // Use type 2 driver with userid/password specified
          db1.userId     = argv[0];
          db1.password   = argv[1];
	}
	break;

      case 3:
	if ( argv[0].equalsIgnoreCase("-u2") ) {
   	  // type 2 Universal
	  db1.portNumber = -1;
	  db2.portNumber = -1;
	  db1.userId     = argv[1];
	  db1.password   = argv[2];
	}
	else
	{
	  // Use type 2 driver with dbname/userid/password specified
	  db1.alias      = argv[0];
          db1.userId     = argv[1];
	  db1.password   = argv[2];
	}
	break;
	
      case 4:
	if ( argv[0].equalsIgnoreCase("-u2") ) {
	  // type 2 Universal
	  db1.portNumber = -1;
	  db2.portNumber = -1;
	  db1.alias      = argv[1];
	  db1.userId     = argv[2];
	  db1.password   = argv[3];
	}
	else
	{
	  throwUsageException();
	}		
	break;

      case 11:
	// Universal type 4 driver
		
	db1.alias      = argv[1];
  	db1.server     = argv[2];
	db1.portNumber = Integer.valueOf( argv[3] ).intValue();
	db1.userId     = argv[4];
	db1.password   = argv[5];
		
	db2.alias      = argv[6];
        db2.server     = argv[7];
	db2.portNumber = Integer.valueOf( argv[8] ).intValue();
	db2.userId     = argv[9];
	db2.password   = argv[10];
	break;
	
      default:  //throw exception
     	throwUsageException();
	break;
    }		

  } // setup

  private static void throwUsageException() throws Exception
  {
    throw new Exception(
      "\n" +
      "Usage: prog_name [\"connection 1 information\" [\"connection 2 information\"]]\n" +
      "\n" +
      "  where \"connection N information\" is:\n" +
      "\n" +
      "    [dbAlias] [userId passwd] (use JDBC type 2 driver)\n" +
      "    -u2 [dbAlias] [userId passwd] (use JDBC Universal type 2 driver)\n" +
      "    -u4 [dbAlias] server portNum userId passwd (use JDBC Universal type 4 driver)\n" +
      "\n" +
      "  dbAlias defaults to 'sample' for connection 1 and 'sample2' for connection 2" );
  }

  public static void createTable( Connection con )
  {
    System.out.println();
    System.out.println(
      "  CREATE TABLE books(title VARCHAR(21), price DECIMAL(7, 2))\n");

    try
    {
      Statement stmt = con.createStatement();
      stmt.executeUpdate("CREATE TABLE books(title VARCHAR(21), " +
                         "                    price DECIMAL(7, 2))");
      stmt.close();

      System.out.println("  COMMIT\n");
      con.commit();
    }
    catch (Exception e)
    {
      System.out.println(e);
    }
  } // createTable

  public static void dropTable( Connection con )
  {
    System.out.println("  DROP TABLE books\n");

    try
    {
      Statement stmt = con.createStatement();
      stmt.executeUpdate("DROP TABLE books");
      stmt.close();

      System.out.println("  COMMIT");
      con.commit();
    }
    catch (Exception e)
    {
      System.out.println(e);
    }
  } // dropTable
} // DbMCon