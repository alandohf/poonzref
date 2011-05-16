//**************************************************************************
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
//**************************************************************************
//
// SOURCE FILE NAME: TbCompress.java
//
// SAMPLE: How to create tables with null and default value compression 
//         option. 
//
// SQL STATEMENTS USED:
//         CREATE TABLE 
//         ALTER TABLE
//         DROP TABLE
//
// JAVA 2 CLASSES USED:
//         Statement
//
// Classes used from Util.java are:
//         Db
//         JdbcException
//
// OUTPUT FILE: TbCompress.out (available in the online documentation)
// Output will vary depending on the JDBC driver connectivity used.
//**************************************************************************
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
//**************************************************************************

import java.lang.*;
import java.sql.*;

class TbCompress
{
  public static void main(String argv[])
  {
    try
    {
      Db db = new Db(argv);

      System.out.println();
      System.out.println(
        "THIS SAMPLE SHOWS HOW TO USE NULL AND DEFAULT VALUE\n" + 
        "COMPRESSION OPTION AT TABLE LEVEL AND COLUMN LEVEL \n");

      // connect to database
      db.connect();

      // create a new table
      tbCreate(db.con);
      
      // activate null and default value compression
      tbCompress(db.con);
      
      // drop the table created
      tbDrop(db.con);

      // disconnect from 'sample' database
      db.disconnect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e) ;
      jdbcExc.handle();
    }
  } // main

  // create a new table
  static void tbCreate(Connection con)
  {
    try
    {
      Statement stmt = con.createStatement();
      
      // create base table            
      System.out.println(
        "\n-----------------------------------------------------------\n" +
        "USE THE SQL STATEMENT \n" +
        "  CREATE TABLE \n" +
        "TO CREATE A TABLE \n\n" +  
        "  CREATE TABLE comp_tab(col1 INT NOT NULL WITH DEFAULT,\n" + 
        "                        col2 CHAR(7),\n" +
        "                        col3 VARCHAR(7) NOT NULL,\n" +
        "                        col4 DOUBLE) \n");
      stmt.executeUpdate(
        "CREATE TABLE comp_tab(col1 INT NOT NULL WITH DEFAULT," +
        "                      col2 CHAR(7)," +
        "                      col3 VARCHAR(7) NOT NULL," +
        "                      col4 DOUBLE)");
      System.out.println("  COMMIT");
      con.commit();
      
      stmt.close();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    } 
  } // tbCreate
  
  // activate null and default value compression
  static void tbCompress(Connection con)
  {
    try
    {
      Statement stmt = con.createStatement();
          
      System.out.println(
        "\n-----------------------------------------------------------\n" +
        "USE THE SQL STATEMENT \n" +
        "  ALTER TABLE \n" +
        "TO ALTER COMPRESSION OPTIONS OF THE TABLE\n\n" + 
        "To activate VALUE COMPRESSION at table level and COMPRESS \n" +
        "SYSTEM DEFAULT at column level \n\n" +
        "  ALTER TABLE comp_tab ACTIVATE VALUE COMPRESSION \n\n" +
        "Rows will be formatted using the new row format on subsequent\n" +
        "insert, load and update operation, and NULL values will not be\n" +
        "taking up space if applicable.\n");

      // if the table comp_tab does not have many NULL values, enabling
      // compression will result in using more disk space than using 
      // the old row format 
      stmt.executeUpdate("ALTER TABLE comp_tab ACTIVATE VALUE COMPRESSION");
      con.commit();
      
      System.out.println(
        "\nTo save more disk space on system default value for column\n" +
        "col1, enter\n" +
        "\n  ALTER TABLE comp_tab ALTER col1 COMPRESS SYSTEM DEFAULT\n" +
        "\nOn subsequent insert, load, and update operations, numerical\n" +
        "0 value (occupying 4 bytes of storage) for column col1 will\n" +
        "not be saved on disk.\n");     
      stmt.executeUpdate("ALTER TABLE comp_tab "+
                         "  ALTER col1 COMPRESS SYSTEM DEFAULT");
      con.commit();
      
      System.out.println(
        "\nTo switch the table to use the old format, enter\n\n" +
        "  ALTER TABLE comp_tab DEACTIVATE VALUE COMPRESSION\n\n" +
        "Rows inserted, loaded or updated after the ALTER statement\n" +
        "will have old row format.");      
      stmt.executeUpdate( "ALTER TABLE comp_tab " +
                          "  DEACTIVATE VALUE COMPRESSION");
      con.commit();
      
      stmt.close();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e) ;
      jdbcExc.handle();
    } 
  } // tbCompress

  // drop the table created
  static void tbDrop(Connection con)
  {
    try
    {
      Statement stmt = con.createStatement();
     
      // drop the table
      System.out.println(
        "\n-----------------------------------------------------------" +
        "\nUSE THE SQL STATEMENT\n" +
        "  DROP TABLE\n" +
        "TO DROP THE TABLE\n\n" +
        "  DROP TABLE comp_tab\n");
      stmt.executeUpdate("DROP TABLE comp_tab");
      System.out.println("\n  COMMIT");
      con.commit();
      
      stmt.close();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e) ;
      jdbcExc.handle();
    } 
  } // tbDrop
} // TbCompress
