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
// disclosure restricted by Gsal ADP Schedule Contract with IBM Corp.
//***************************************************************************
//
// SOURCE FILE NAME: TbRowcompress.java
//
// SAMPLE: How to perform row compression on a table
//
//         This sample shows:
//         1. How to enable the row compression after a table is created.
//         2. How to enable the row compression during table creation.
//         3. Usage of the options to REORG to use the exiting dictionary
//            or creating a new dictionary.
//         4. How to estimate the effectiveness of the compression.
//
//         This sample should be run using the following steps:
//         1.Compile the program with the following command:
//           javac TbRowcompress.java
//
//         2.The sample should be run using the following command
//           java TbRowcompress <path for dummy file>
//           The fenced user id must be able to create or overwrite files in
//           the directory specified.This directory must 
//           be a full path on the server. The dummy file 'dummy.del' must
//           exist before the sample is run.
// 
// SQL STATEMENTS USED:
//         ALTER TABLE
//         COMMIT
//         CREATE TABLE
//         DECLARE
//         DELETE
//         DROP TABLE
//         FETCH
//         INSERT
//         OPEN
//         PREPARE
//         SELECT
//         UPDATE
//
// JAVA 2 CLASSES USED:
//         Statement
//         CallableStatement
//         ResultSet
//
// Classes used from Util.java are:
//         Db
//         Data
//         JdbcException
//
// OUTPUT FILE: TbRowcompress.java (available in the online documentation)
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
//***************************************************************************

import java.lang.*;
import java.sql.*;

class TbRowcompress
{
  public static void main(String argv[])
  {
    if (argv.length < 1)
    {
      System.out.println("\n Usage : java TbRowcompress" +
                         " <path for dummy file>");
    }
    else
    {     
      try
      {
        Connection con = null;
        String path = argv[0];

        // initialize DB2Driver and establish database connection.
        COM.ibm.db2.jdbc.app.DB2Driver db2Driver =
          (COM.ibm.db2.jdbc.app.DB2Driver)
            Class.forName("COM.ibm.db2.jdbc.app.DB2Driver").newInstance();
        con = DriverManager.getConnection("jdbc:db2:SAMPLE");

        System.out.println(
          "THIS SAMPLE SHOWS HOW TO PERFROM ROW COMPRESSION ON A TABLE.");

         // to Load table data into a file.
        getLoadData(con, path);

        // to Enable Row compression on table.
        enableRowCompressionForTables(con, path); 

        // to disable row compression on tables.
        disableRowCompressionForTables(con, path); 

        // to inspect the compression.
        inspectCompression(con, path); 

        // close the connection                                   
        con.close();

      }
      catch (Exception e)
      {
        JdbcException jdbcExc = new JdbcException(e);
        jdbcExc.handle();
      }
    }
  } // main

  static void getLoadData(Connection con, String path) throws SQLException
  {
    try
    {
     String sql = "";
     String param = "";
     CallableStatement callStmt1 = null;
     ResultSet rs = null;
     Statement stmt = con.createStatement();

     int rows_exported = 0;

     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENTS:\n" +
       "  CREATE TABLE \n" +
       "TO CREATE A TABLE \n" +
       "\n    Perform:\n" +
       "    CREATE TABLE temp(empno INT, sal INT)");

     // create a temporary table
     stmt.executeUpdate("CREATE TABLE temp(empno INT, sal INT)");

     // insert data into the table and export the data in order to obtain
     // dummy.del file in the required format for load.

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  INSERT \n" +
       "TO INSERT DATA INTO THE TABLE \n" +
       "\n    Perform:\n" +
       "    INSERT INTO temp VALUES(100, 20000)\n" +
       "    INSERT INTO temp VALUES(101, 30000)\n" +
       "    INSERT INTO temp VALUES(102, 30500)\n" +
       "    INSERT INTO temp VALUES(103, 20000)\n" +
       "    INSERT INTO temp VALUES(104, 30000)");

     // insert data into the table
     stmt = con.createStatement();
     stmt.executeUpdate("INSERT INTO temp VALUES(100, 20000)");
     stmt.executeUpdate("INSERT INTO temp VALUES(200, 30000)");
     stmt.executeUpdate("INSERT INTO temp VALUES(100, 30500)");
     stmt.executeUpdate("INSERT INTO temp VALUES(300, 20000)");
     stmt.executeUpdate("INSERT INTO temp VALUES(400, 30000)");

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  EXPORT \n" +
       "TO EXPORT TABLE DATA INTO A FILE \n" +
       "\n    Perform:\n" +
       "    EXPORT TO dummy.del OF DEL SELECT * FROM temp");

     // export data into a dummy file
     sql = "CALL SYSPROC.ADMIN_CMD(?)";
     callStmt1 = con.prepareCall(sql);

     // 'path' is the path for the file to which the data is to be exported
     param = "EXPORT TO " + path + "dummy.del OF DEL SELECT * FROM temp" ;

     // set the input parameter
     callStmt1.setString(1, param);
     System.out.println();

     // execute import by calling ADMIN_CMD
     callStmt1.execute();

     rs = callStmt1.getResultSet();
      
     // retrieve the resultset  
     if( rs.next())
     { 
       // the numbers of rows exported
       rows_exported = rs.getInt(1);

       // display the output
       System.out.println
         ("Total number of rows exported  : " + rows_exported);
     } 

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  DROP \n" +
       "TO DROP THE TABLE \n" +
       "\n    Perform:\n" +
       "    DROP TABLE temp");

     // drop the temporary table
     stmt = con.createStatement();
     stmt.executeUpdate("DROP TABLE temp");

     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // getLoadData

  static void enableRowCompressionForTables
                (Connection con, String path) throws SQLException
  {
    try
    {
     String sql = "";
     String param = "";
     CallableStatement callStmt1 = null;
     ResultSet rs = null;
     Statement stmt = con.createStatement();

     int rows_read = 0;
     int rows_skipped = 0;
     int rows_loaded = 0;
     int rows_rejected = 0;
     int rows_deleted = 0;
     int rows_committed = 0;

     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENTS:\n" +
       "  CREATE TABLE \n" +
       "TO CREATE A TABLE \n" +
       "\n    Perform:\n" +
       "    CREATE TABLE empl(emp_no INT, salary INT)");

     // create a table without enabling row compression at the time of
     // table creation
     stmt = con.createStatement();
     stmt.executeUpdate("CREATE TABLE empl(emp_no INT, salary INT)");

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  IMPORT \n" +
       "TO IMPORT THE DATA INTO THE TABLE \n" +
       "\n    Perform:\n" +
       "    IMPORT FROM dummy.del OF DEL INSERT INTO empl");

     // import data from file
     sql = "CALL SYSPROC.ADMIN_CMD(?)";
     callStmt1 = con.prepareCall(sql);

     // 'path' is the path for the file to be loaded
     param = "IMPORT FROM " + path + "dummy.del OF DEL INSERT INTO empl" ;

     // set the input parameter
     callStmt1.setString(1, param);
       
     // execute import by calling ADMIN_CMD
     callStmt1.execute();
     rs = callStmt1.getResultSet();
      
     // retrieve the resultset  
     if( rs.next())
     { 
       // retrieve the no of rows read
       rows_read = rs.getInt(1);
       // retrieve the no of rows skipped
       rows_skipped = rs.getInt(2);
       // retrieve the no of rows loaded
       rows_loaded = rs.getInt(3);
       // retrieve the no of rows rejected
       rows_rejected = rs.getInt(4);
       // retrieve the no of rows deleted
       rows_deleted = rs.getInt(5);
       // retrieve the no of rows committed
       rows_committed = rs.getInt(6);

       // display the resultset
       System.out.print("\nTotal number of rows read      : ");
       System.out.println(rows_read);
       System.out.print("Total number of rows skipped   : ");
       System.out.println( rows_skipped);
       System.out.print("Total number of rows loaded    : ");
       System.out.println(rows_loaded);
       System.out.print("Total number of rows rejected  : "); 
       System.out.println(rows_rejected);
       System.out.print("Total number of rows deleted   : "); 
       System.out.println(rows_deleted);
       System.out.print("Total number of rows committed : "); 
       System.out.println(rows_read);
      } 

      System.out.println(
        "\nUSE THE SQL STATEMENTS:\n" +
        "  ALTER TABLE \n" +
        "TO ENABLE ROW COMPRESSION \n" +
        "\n    Perform:\n" +
        "    ALTER TABLE empl COMPRESS YES");

      // enable row compression
      stmt = con.createStatement();
      stmt.executeUpdate("ALTER TABLE empl COMPRESS YES");

      System.out.println(
        "\nUSE THE SQL STATEMENTS:\n" +
        "  REORG \n" +
        "TO COMPRESS ROWS \n" +
        "\n    Perform:\n" +
        "    REORG TABLE empl");

      // perform non-inplace reorg to compress rows and to retain
      // existing dictionary
      sql = "CALL SYSPROC.ADMIN_CMD(?)";
      callStmt1 = con.prepareCall(sql);

      param = "REORG TABLE empl" ;
 
      // set the input parameter
      callStmt1.setString(1, param);
        
      // execute import by calling ADMIN_CMD
      callStmt1.execute();

      System.out.println(
        "\nUSE THE SQL STATEMENTS:\n" +
        "  DROP \n" +
        "TO DROP THE TABLE \n" +
        "\n    Perform:\n" +
        "    DROP TABLE empl");
 
      // drop the temporary table
      stmt = con.createStatement();
      stmt.executeUpdate("DROP TABLE empl");
 
      con.commit();
      stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // enableRowCompressionForTables

  static void disableRowCompressionForTables
                (Connection con, String path) throws SQLException
  {
    try
    {
     String sql = "";
     String param = "";
     CallableStatement callStmt1 = null;
     ResultSet rs = null;
     Statement stmt = con.createStatement();

     int rows_read = 0;
     int rows_skipped = 0;
     int rows_loaded = 0;
     int rows_rejected = 0;
     int rows_deleted = 0;
     int rows_committed = 0;

     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENTS:\n" +
       "  CREATE \n" +
       "TO CREATE A TABLE \n" +
       "\n    Perform:\n" +
       "    CREATE TABLE empl(emp_no INT, salary INT) COMPRESS YES");

     // create a table enabling compression initially
     stmt = con.createStatement();
     stmt.executeUpdate
            ("CREATE TABLE empl(emp_no INT, salary INT) COMPRESS YES");

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  IMPORT \n" +
       "TO IMPORT THE DATA INTO THE TABLE \n" +
       "\n    Perform:\n" +
       "    IMPORT FROM dummy.del OF DEL INSERT INTO empl");

     // load data into table
     sql = "CALL SYSPROC.ADMIN_CMD(?)";
     callStmt1 = con.prepareCall(sql);

     // 'path' is the path for the file to be loaded
     param = "IMPORT FROM " + path + "/dummy.del OF DEL INSERT INTO empl" ;

     // set the input parameter
     callStmt1.setString(1, param);
       
     // execute import by calling ADMIN_CMD
     callStmt1.execute();
     rs = callStmt1.getResultSet();
      
     // retrieve the resultset  
     if( rs.next())
     { 
       // retrieve the no of rows read
       rows_read = rs.getInt(1);
       // retrieve the no of rows skipped
       rows_skipped = rs.getInt(2);
       // retrieve the no of rows loaded
       rows_loaded = rs.getInt(3);
       // retrieve the no of rows rejected
       rows_rejected = rs.getInt(4);
       // retrieve the no of rows deleted
       rows_deleted = rs.getInt(5);
       // retrieve the no of rows committed
       rows_committed = rs.getInt(6);
     
       // display the resultset
       System.out.print("\nTotal number of rows read      : ");
       System.out.println(rows_read);
       System.out.print("Total number of rows skipped   : ");
       System.out.println( rows_skipped);
       System.out.print("Total number of rows loaded    : ");
       System.out.println(rows_loaded);
       System.out.print("Total number of rows rejected  : "); 
       System.out.println(rows_rejected);
       System.out.print("Total number of rows deleted   : "); 
       System.out.println(rows_deleted);
       System.out.print("Total number of rows committed : "); 
       System.out.println(rows_read);
     } 

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  REORG \n" +
       "TO COMPRESS ROWS \n" +
       "\n    Perform:\n" +
       "    REORG TABLE empl");

     // perform reorg to compress rows
     param = "REORG TABLE empl" ;

     // set the input parameter
     callStmt1.setString(1, param);
       
     // execute import by calling ADMIN_CMD
     callStmt1.execute();

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  INSERT \n" +
       "  UPDATE \n" +
       "  DELETE \n" +
       "TO INSERT, UPDATE OR DELETE DATA IN TABLE \n" +
       "\n    Perform:\n" +
       "    INSERT INTO empl VALUES(400, 30000)\n" +
       "    UPDATE empl SET salary = salary + 1000\n" +
       "    DELETE FROM empl WHERE emp_no = 200");

     // perform modifications on table
     stmt = con.createStatement();
     stmt.executeUpdate("INSERT INTO empl VALUES(400, 30000)");
     stmt.executeUpdate("UPDATE empl SET salary = salary + 1000");
     stmt.executeUpdate("DELETE FROM empl WHERE emp_no = 200");

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  ALTER TABLE \n" +
       "TO DISABLE ROW COMPRESSION FOR THE TABLE \n" +
       "\n    Perform:\n" +
       "    ALTER TABLE empl COMPRESS NO");

     // disable row compression for the table
     stmt = con.createStatement();
     stmt.executeUpdate("ALTER TABLE empl COMPRESS NO");

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  REORG TABLE \n" +
       "TO REORG THE TABLE AND REMOVE EXISTING DICTIONARY \n" +
       "\n    Perform:\n" +
       "    REORG TABLE empl RESETDICTIONARY");

     // Perform reorg to remove existing dictionary.
     // New dictionary will be created and all the rows processed
     // by the reorg are decompressed.
     param = "REORG TABLE empl RESETDICTIONARY" ;

     // set the input parameter
     callStmt1.setString(1, param);
       
     // execute import by calling ADMIN_CMD
     callStmt1.execute();

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  DROP \n" +
       "TO DROP THE TABLE \n" +
       "\n    Perform:\n" +
       "    DROP TABLE empl");

     // drop the table
     stmt = con.createStatement();
     stmt.executeUpdate("DROP TABLE empl");
     
     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // disableRowCompressionForTables

  static void inspectCompression
                (Connection con, String path) throws SQLException
  {
    try
    {
     String sql = null;
     String param = null;
     String str = null;
     ResultSet rs = null;
     Statement stmt = con.createStatement();

     CallableStatement callStmt1 = null;

     int emp_no = 0;
     int sal = 0;

     int rows_read = 0;
     int rows_skipped = 0;
     int rows_loaded = 0;
     int rows_rejected = 0;
     int rows_deleted = 0;
     int rows_committed = 0;

     int avgrowsize = 0;
     int avgcompressedrowsize = 0;
     int pctpagessaved = 0;
     int avgrowcompressionratio = 0;
     int pctrowscompressed = 0;

     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENTS:\n" +
       "  CREATE TABLE \n" +
       "TO CREATE A TABLE \n" +
       "\n    Perform:\n" +
       "    CREATE TABLE empl(emp_no INT, salary INT)");

     // create a table
     stmt = con.createStatement();
     stmt.executeUpdate("CREATE TABLE empl(emp_no INT, salary INT)");

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  IMPORT \n" +
       "TO IMPORT DATA INTO TABLE \n" +
       "\n    Perform:\n" +
       "    IMPORT FROM dummy.del OF DEL INSERT INTO empl");

     // import data into the table
     sql = "CALL SYSPROC.ADMIN_CMD(?)";
     callStmt1 = con.prepareCall(sql);

     // 'path' is the path for the file to be loaded
     param = "IMPORT FROM " + path + "/dummy.del OF DEL INSERT INTO empl" ;

     // set the input parameter
     callStmt1.setString(1, param);
            
     // execute import by calling ADMIN_CMD
     callStmt1.execute();
     rs = callStmt1.getResultSet();
      
     // retrieve the resultset  
     if( rs.next())
     { 
       // retrieve the no of rows read
       rows_read = rs.getInt(1);
       // retrieve the no of rows skipped
       rows_skipped = rs.getInt(2);
       // retrieve the no of rows loaded
       rows_loaded = rs.getInt(3);
       // retrieve the no of rows rejected
       rows_rejected = rs.getInt(4);
       // retrieve the no of rows deleted
       rows_deleted = rs.getInt(5);
       // retrieve the no of rows committed
       rows_committed = rs.getInt(6);
    
       // display the resultset
       System.out.print("\nTotal number of rows read      : ");
       System.out.println(rows_read);
       System.out.print("Total number of rows skipped   : ");
       System.out.println( rows_skipped);
       System.out.print("Total number of rows loaded    : ");
       System.out.println(rows_loaded);
       System.out.print("Total number of rows rejected  : "); 
       System.out.println(rows_rejected);
       System.out.print("Total number of rows deleted   : "); 
       System.out.println(rows_deleted);
       System.out.print("Total number of rows committed : "); 
       System.out.println(rows_read);
     } 

      System.out.println(
        "\nUSE THE SQL STATEMENTS:\n" +
        "  ALTER TABLE \n" +
        "TO ENABLE COMPRESSION \n" +
        "\n    Perform:\n" +
        "    ALTER TABLE empl COMPRESS YES");

      // enable row compression for the table
      stmt = con.createStatement();
      stmt.executeUpdate("ALTER TABLE empl COMPRESS YES");

      System.out.println(
        "\nUSE THE SQL STATEMENTS:\n" +
        "  INSERT \n" +
        "TO INSERT DATA INTO THE TABLE \n" +
        "\n    Perform:\n" +
        "    INSERT INTO empl VALUES(400, 30000)");
 
      // insert some data into the table
      stmt = con.createStatement();
      stmt.executeUpdate("INSERT INTO empl VALUES(400, 30000)");
 
      System.out.println(
        "\nUSE THE SQL STATEMENTS:\n" +
        "  INSPECT \n" +
        "TO ESTIMATE THE EFFECTIVENESS OF COMPRESSION \n" +
        "\n    Perform:\n" +
        "    INSPECT ROWCOMPESTIMATE TABLE NAME empl RESULTS KEEP result");
 
      // Perform inspect to estimate the effectiveness of compression.
      // Inspect has to be run before the REORG utility.
      // Inspect allows you to look over tablespaces and tables for their
      // architectural integrity.
      // 'result' file contains percentage of bytes saved from compression,
      // Percentage of rows ineligible for compression due to small row size,
      // Compression dictionary size, Expansion dictionary size etc.
      // To view the contents of 'result' file perform
      //    db2inspf result result.out; This formats the 'result' file to
      // readable form.
 
      String execCmd = "db2 INSPECT ROWCOMPESTIMATE TABLE NAME empl" +
                       " RESULTS KEEP result";

      // execute the command
      Process p1 = Runtime.getRuntime().exec(execCmd);

      System.out.println(
        "\nUSE THE SQL STATEMENTS:\n" +
        "  REORG \n" +
        "TO REORG THE TABLE \n" +
        "\n    Perform:\n" +
        "    REORG TABLE empl");
 
      // perform reorg on the table
 
      param = "REORG TABLE empl" ;

      // set the input parameter
      callStmt1.setString(1, param);
       
      // execute import by calling ADMIN_CMD
      callStmt1.execute();

      System.out.println(
        "\nUSE THE SQL STATEMENTS:\n" +
        "  INSERT \n" +
        "TO INSERT DATA INTO THE TABLE \n" +
        "\n    Perform:\n" +
        "    INSERT INTO empl VALUES(500, 40000)");
 
      // all the rows will be compressed including the one inserted
      // after reorg
      stmt = con.createStatement();
      stmt.executeUpdate("INSERT INTO empl VALUES(500, 40000)");
 
      System.out.println(
        "\nUSE THE SQL STATEMENTS:\n" +
        "  ALTER TABLE \n" +
        "TO DISABLE THE COMPRESSION \n" +
        "\n    Perform:\n" +
        "    ALTER TABLE empl COMPRESS NO");

      // disable row compression for the table.
      // rows inserted after this will be non-compressed.
      stmt = con.createStatement();
      stmt.executeUpdate("ALTER TABLE empl COMPRESS NO");

      System.out.println(
        "\nUSE THE SQL STATEMENTS:\n" +
        "  INSERT \n" +
        "TO INSERT DATA INTO THE TABLE \n" +
        "\n    Perform:\n" +
        "    INSERT INTO empl VALUES(600, 40500)");

      // add one row of data to the table
      stmt = con.createStatement();
      stmt.executeUpdate("INSERT INTO empl VALUES(600, 40500)");
 
      System.out.println(
        "\nUSE THE SQL STATEMENTS:\n" +
        "  ALTER TABLE \n" +
        "TO ENABLE THE COMPRESSION \n" +
        "\n    Perform:\n" +
        "    ALTER TABLE empl COMPRESS YES");

     // enable the row compression for the table
     stmt = con.createStatement();
     stmt.executeUpdate("ALTER TABLE empl COMPRESS YES");

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  INSERT \n" +
       "TO INSERT DATA INTO THE TABLE \n" +
       "\n    Perform:\n" +
       "    INSERT INTO empl VALUES(700, 40600)");

     // add one row of data to the table
     stmt = con.createStatement();
     stmt.executeUpdate("INSERT INTO empl VALUES(700, 40600)");

     System.out.println(
       "\nUSE THE SQL STATEMENTS:\n" +
       "  RUNSTATS \n" +
       "TO MEASURE THE EFFECTIVENESS OF COMPRESSION \n" +
       "\n    Perform:\n" +
       "    RUNSTATS ON TABLE EMPL");

     // Perform runstats to measure the effectiveness of compression using
     // compression related catalog fields. New columns will be updated to
     // catalog table after runstats if performed on a compressed table.

     // get fully qualified name of the table
     String tableName = "EMPL";
     String schemaName = getSchemaName(con, tableName);
     String fullTableName = schemaName + "." + tableName;

     param = "RUNSTATS ON TABLE " + fullTableName;

     // set the input parameter
     callStmt1.setString(1, param);
            
     // execute import by calling ADMIN_CMD
     callStmt1.execute();

     System.out.println();
     System.out.println("  SELECT * FROM empl");
     System.out.println(
       "    EMP_NO  SALARY\n" +
       "    ------  ------");
     stmt = con.createStatement();

     // perform a SELECT against the "empl" table.
     rs = stmt.executeQuery("SELECT * FROM empl");

     // retrieve and display the result from the SELECT statement
     while (rs.next())
     {
       emp_no = rs.getInt(1);
       sal    = rs.getInt(2);

       System.out.println(
         "      " + Data.format(emp_no, 3) +
         "   " + Data.format(sal, 5));
     }
     rs.close();

     System.out.println();
     System.out.println(
       "SELECT avgrowsize, avgcompressedrowsize, pctpagessaved,\n" +
       "       avgrowcompressionratio, pctrowscompressed\n" +
       "  FROM SYSCAT.TABLES WHERE tabname = 'EMPL'");
     System.out.println(
       "\n    AvRowSize AvCmprsdRowSize PerPgSaved AvgRowCmprRatio" +
       " PerRowsCmprsd\n" +
       "    --------- --------------- ---------- ---------------" +
       " -------------");

      stmt = con.createStatement();
      // perform a SELECT against the "SYSCAT.TABLES" table.
      str = "SELECT avgrowsize, avgcompressedrowsize, pctpagessaved, " + 
            "avgrowcompressionratio, pctrowscompressed from " +
            "SYSCAT.TABLES WHERE tabname = 'EMPL'";
      rs = stmt.executeQuery(str);

      // retrieve and display the result from the SELECT statement
      while (rs.next())
      {
        avgrowsize = rs.getInt(1);
        avgcompressedrowsize = rs.getInt(2);
        pctpagessaved = rs.getInt(3);
        avgrowcompressionratio = rs.getInt(4);
        pctrowscompressed = rs.getInt(5);

        System.out.println(
          "    " + Data.format(avgrowsize, 4) +
          "    " + Data.format(avgcompressedrowsize, 11) +
          "    " + Data.format(pctpagessaved, 9) +
          "    " + Data.format(avgrowcompressionratio, 9) +
          "    " + Data.format(pctrowscompressed, 13));

      }
      rs.close();

      System.out.println(
        "\nUSE THE SQL STATEMENTS:\n" +
        "  DROP \n" +
        "TO DROP THE TABLE \n" +
        "\n    Perform:\n" +
        "    DROP TABLE empl");

      // drop the temporary table
      stmt = con.createStatement();
      stmt.executeUpdate("DROP TABLE empl");

      con.commit();
      stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // inspectCompression

  // function to get the schema name for a particular table
  static String getSchemaName
                  (Connection conn, String tableName) throws Exception
  {
    Statement stmt = conn.createStatement();
    ResultSet rs = stmt.executeQuery(
                     "SELECT tabschema "+
                     "  FROM syscat.tables "+
                     "  WHERE tabname = '"+ tableName + "'");

    boolean result = rs.next();
    String schemaName = rs.getString("tabschema");
    rs.close();
    stmt.close();

    // remove the trailing white space characters from schemaName before
    // returning it to the calling function
    return schemaName.trim();
  } // getSchemaName
} // TbRowcompress
