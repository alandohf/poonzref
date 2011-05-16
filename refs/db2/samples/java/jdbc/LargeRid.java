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
// SOURCE FILE NAME: LargeRid.java
//
// SAMPLE: How to enable Large RIDs support on both new tables/tablespaces
//         and existing tables/tablespaces.
//
// SQL Statements USED:
//         ALTER TABLESPACE
//         CREATE TABLE
//         CREATE TABLESPACE
//         DROP
//         INSERT
//         REORG
//         SELECT
//
// JAVA 2 CLASSES USED:
//         Statement
//
// Classes used from Util.java are:
//         Db
//         Data
//         JdbcException
//
// OUTPUT FILE: LargeRid.out (available in the online documentation)
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

class LargeRid
{
  public static void main(String argv[])
  {
    try
    {
      Db db = new Db(argv);

      System.out.println();
      System.out.println(
        "THIS SAMPLE SHOWS HOW TO ENABLE LARGE RID SUPPORT ON TABLES AND\n" +
        "  TABLESPACES\n");

      // connect to the 'sample' database
      db.connect();

      dmstspaceaceCreate(db.con);

      System.out.println
        ("\n************************************************************\n");
      System.out.println
        ("THE FOLLOWING SCENARIO SHOWS HOW TO ENABLE LARGE RID SUPPORT");
      System.out.println("     FOR A NON-PARTITIONED TABLE\n");
      System.out.println
        ("************************************************************");

      tbCreate(db.con);      
      createIndex(db.con); 
      tbAlterSpace(db.con);  
      reorgIndex(db.con);   
      indexDrop(db.con);  

      System.out.println
        ("\n************************************************************\n"); 
      System.out.println
        ("THE FOLLOWING SCENARIO SHOWS HOW TO ENABLE LARGE RID SUPPORT");
      System.out.println
        ("     FOR A PARTITIONED TABLE\n");
      System.out.println
        ("************************************************************");

      partitionedTbCreate(db.con);  
      insertData(db.con);      
      tbDetachPartition(db.con); 
      convertTbSpace(db.con);     
      tbReorganize(db.con);      
      tbAttachPartition(db.con);
      tbDrop(db.con);          
      tablespacesDrop(db.con);

      // disconnect from the 'sample' database
      db.disconnect();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    }
  } // main

  // Creates regular DMS tablespaces
  static void dmstspaceaceCreate(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENT:\n" +
       "  CREATE REGULAR TABLESPACE \n" +
       "TO CREATE A REGULAR TABLESPACE \n" +
       "\n    Execute the statement:\n" +
       "    CREATE REGULAR TABLESPACE dms_tspace\n" +
       "      MANAGED BY DATABASE \n" +
       "      USING (FILE 'dms_cont.dat' 1000)");

     // create regular DMS table space dms_tspace
     Statement stmt = con.createStatement();
     String str = "";
     str = "CREATE REGULAR TABLESPACE dms_tspace";
     str = str + " MANAGED BY DATABASE USING (FILE 'dms_cont.dat' 10000)";
     stmt.executeUpdate(str);

     System.out.println(
       "\nUSE THE SQL STATEMENT:\n" +
       "  CREATE REGULAR TABLESPACE \n" +
       "TO CREATE A REGULAR TABLESPACE \n" +
       "\n    Execute the statement:\n" +
       "    CREATE REGULAR TABLESPACE dms_tspace1\n" +
       "      MANAGED BY DATABASE \n" +
       "      USING (FILE 'dms_cont1.dat' 1000)");

     // create regular DMS table space dms_tspace1
     str = "CREATE REGULAR TABLESPACE dms_tspace1" +
           " MANAGED BY DATABASE USING (FILE 'dms_cont1.dat' 10000)";
     stmt.executeUpdate(str);

     System.out.println(
       "\nUSE THE SQL STATEMENT:\n" +
       "  CREATE REGULAR TABLESPACE \n" +
       "TO CREATE A REGULAR TABLESPACE \n" +
       "\n    Execute the statement:\n" +
       "    CREATE REGULAR TABLESPACE dms_tspace2\n" +
       "      MANAGED BY DATABASE \n" +
       "      USING (FILE 'dms_cont2.dat' 1000)");

     // create regular DMS table space dms_tspace2
     str = "CREATE REGULAR TABLESPACE dms_tspace2" +
           " MANAGED BY DATABASE USING (FILE 'dms_cont2.dat' 10000)";
     stmt.executeUpdate(str);

     System.out.println(
       "\nUSE THE SQL STATEMENT:\n" +
       "  CREATE REGULAR TABLESPACE \n" +
       "TO CREATE A REGULAR TABLESPACE \n" +
       "\n    Execute the statement:\n" +
       "    CREATE REGULAR TABLESPACE dms_tspace3\n" +
       "      MANAGED BY DATABASE \n" +
       "      USING (FILE 'dms_cont3.dat' 1000)");

     // create regular DMS table space dms_tspace3
     str = "CREATE REGULAR TABLESPACE dms_tspace3" +
           " MANAGED BY DATABASE USING (FILE 'dms_cont3.dat' 10000)";
     stmt.executeUpdate(str);

     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // dmstspaceaceCreate

  // Creates a non-partitioned table.
  static void tbCreate(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\nUSE THE SQL STATEMENT:\n" +
       "  CREATE TABLE \n" +
       "TO CREATE A TABLE \n" +
       "\n    Execute the statement:\n" +
       "    CREATE TABLE large (max INT, min INT) IN dms_tspace");

     // create table in 'dms_tspace' regular DMS tablespace
     Statement stmt = con.createStatement();
     String str = "";
     str = "CREATE TABLE large (max INT, min INT)" +
           "  IN dms_tspace";
     stmt.executeUpdate(str);

     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // tbCreate

  // Creates index on a table.
  static void createIndex(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENT:\n" +
       "  CREATE INDEX \n" +
       "TO CREATE AN INDEX \n" +
       "\n    Execute the statement:\n" +
       "    CREATE INDEX large_ind ON large (max)");

     // create index
     Statement stmt = con.createStatement();
     stmt.executeUpdate("CREATE INDEX large_ind ON large (max)");

     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // createIndex

  // Changes table space from regular to large.
  static void tbAlterSpace(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENT:\n" +
       "  ALTER TABLESPACE \n" +
       "TO ALTER A TABLESPACE \n" +
       "\n    Execute the statement:\n" +
       "    ALTER TABLESPACE dms_tspace CONVERT TO LARGE");

     // convert regular DMS tablespace 'dms_tspace' to large DMS tablespace
     Statement stmt = con.createStatement();
     stmt.executeUpdate("ALTER TABLESPACE dms_tspace CONVERT TO LARGE");

     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // tbAlterSpace

  // Reorganize indexes defined on a table.
  static void reorgIndex(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENT:\n" +
       "  REORG INDEXES \n" +
       "TO REORG INDEXES FOR A TABLE \n" +
       "\n    Execute the statement:\n" +
       "    REORG INDEXES ALL FOR TABLE large");

      String sql = "CALL SYSPROC.ADMIN_CMD(?)";
      CallableStatement callStmt1 = con.prepareCall(sql);

      String param = "REORG INDEXES ALL FOR TABLE large" ;
 
      // set the input parameter
      callStmt1.setString(1, param);
        
      // execute import by calling ADMIN_CMD
      callStmt1.execute();

     con.commit();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // reorgIndex

  // Drop indexes defined on a table.
  static void indexDrop(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENT:\n" +
       "  DROP INDEX \n" +
       "TO DROP AN INDEX \n" +
       "\n    Execute the statement:\n" +
       "    DROP INDEX large_ind");

     // drop the index
     Statement stmt = con.createStatement();
     stmt.executeUpdate("DROP INDEX large_ind");

     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // indexDrop

  // Creates a partitioned table with 'part1' in 'dms_tspace1', 'part2' 
  // in 'dms_tspace2', and 'part3' in 'dms_tspace3'.
  static void partitionedTbCreate(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\nUSE THE SQL STATEMENT:\n" +
       "  CREATE TABLE \n" +
       "TO CREATE A TABLE \n" +
       "\n    Execute the statement:\n" +
       "    CREATE TABLE large_ptab (max SMALLINT NOT NULL,\n" +
       "                             CONSTRAINT CC CHECK (max>0))\n" +  
       "      PARTITION BY RANGE (max)\n "+
       "       (PART  part1 STARTING FROM (1) ENDING (3) IN dms_tspace1,\n" +
       "        PART part2 STARTING FROM (4) ENDING (6) IN dms_tspace2,\n" +
       "        PART part3 STARTING FROM (7) ENDING (9) IN dms_tspace3)");

     // create a partitioned table in regular DMS tablespaces i.e; part1 is
     // placed at dms_tspace1, part2 is placed at dms_tspace2 and
     // part3 at dms_tspace3.
     Statement stmt = con.createStatement();
     String str = "";

     str = str + "CREATE TABLE large_ptab " +
                 "(max SMALLINT NOT NULL, CONSTRAINT CC CHECK (max>0))" +
                 " PARTITION BY RANGE (max) " +
                 "(PART  part1 STARTING FROM (1) ENDING (3) " +
                 "IN dms_tspace1, PART part2 STARTING FROM (4) ENDING (6) " +
                 "IN dms_tspace2, PART part3 STARTING FROM (7) ENDING (9) " +
                 "IN dms_tspace3)";
    
     stmt.executeUpdate(str);
           
     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // partitionedTbCreate

  // Insert data into the table.
  static void insertData(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENT:\n" +
       "  INSERT INTO \n" +
       "TO INSERT DATA IN A TABLE \n" +
       "\n    Execute the statement:\n" +
       "    INSERT INTO large_ptab VALUES (1), (2), (3),\n" + 
       "                                  (4), (5), (6),\n" +
       "                                  (7), (8), (9)");

     // insert data into the table
     Statement stmt = con.createStatement();
     String str = "";

     str = "INSERT INTO large_ptab VALUES (1), (2), (3), (4)," +
           " (5), (6), (7), (8), (9)";
     stmt.executeUpdate(str);

     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // insertData

  // If a partitioned table has data partitions in different regular DMS
  // tablespaces, then the tablespaces cannot be converted to large
  // with the current definition.
  // To do this, first detach all the partitions of the table, later
  // convert all the tablespaces to large, reorg all the detached
  // partitions to support large RID. Finally, reattach the partitions.
  // Now the entire table supports large RIDs.

  // Remove partition from a partitioned table.
  static void tbDetachPartition(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENT:\n" +
       "  ALTER TABLE \n" +
       "TO DETACH THE PARTITIONS  \n" +
       "\n    Execute the statements:\n" +
       "    ALTER TABLE large_ptab\n" +
       "      DETACH PARTITION PART3\n" +
       "      INTO TABLE detach_part3\n\n" +
       "    ALTER TABLE large_ptab\n" +
       "      DETACH PARTITION PART3\n" +
       "      INTO TABLE detach_part2");

     // detach partitions from base table into some temporary tables
     Statement stmt = con.createStatement();
     String str ="";
     str = "ALTER TABLE large_ptab DETACH PARTITION part3 " +
           "INTO TABLE detach_part3";
     stmt.executeUpdate(str);

     str = "ALTER TABLE large_ptab DETACH PARTITION part2 " +
           "INTO TABLE detach_part2";
     stmt.executeUpdate(str);

     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // tbDetachPartition

  // Changes table space from regular to large.
  static void convertTbSpace(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENT:\n" +
       "  ALTER TABLE \n" +
       "TO DETACH THE PARTITIONS  \n" +
       "\n    Execute the statements:\n" +
       "    ALTER TABLESPACE dms_tspace1 CONVERT TO LARGE\n" +
       "    ALTER TABLESPACE dms_tspace2 CONVERT TO LARGE\n" +
       "    ALTER TABLESPACE dms_tspace3 CONVERT TO LARGE");

     // convert regular DMS tablespaces to large DMS tablespaces
     Statement stmt = con.createStatement();
     stmt.executeUpdate("ALTER TABLESPACE dms_tspace1 CONVERT TO LARGE");
     stmt.executeUpdate("ALTER TABLESPACE dms_tspace2 CONVERT TO LARGE");
     stmt.executeUpdate("ALTER TABLESPACE dms_tspace3 CONVERT TO LARGE");

     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // convertTbSpace

  // Reorganize table. 
  static void tbReorganize(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENT:\n" +
       "  REORG TABLE \n" +
       "TO REORG THE DETACHED PARTITIONS  \n" +
       "\n    Execute the statements:\n" +
       "    REORG TABLE large_ptab ALLOW NO ACCESS\n" +
       "    REORG TABLE detach_part2 ALLOW NO ACCESS\n" +
       "    REORG TABLE detach_part3 ALLOW NO ACCESS\n");

      String sql = "CALL SYSPROC.ADMIN_CMD(?)";
      CallableStatement callStmt1 = con.prepareCall(sql);

      String param1 = "REORG TABLE large_ptab ALLOW NO ACCESS";
      String param2 = "REORG TABLE detach_part2 ALLOW NO ACCESS";
      String param3 = "REORG TABLE detach_part3 ALLOW NO ACCESS";

      // set the input parameter
      callStmt1.setString(1, param1);
        
      // execute reorg by calling ADMIN_CMD
      callStmt1.execute();
 
      // set the input parameter
      callStmt1.setString(1, param2);
        
      // execute reorg by calling ADMIN_CMD
      callStmt1.execute();

      // set the input parameter
      callStmt1.setString(1, param3);
        
      // execute reorg by calling ADMIN_CMD
      callStmt1.execute();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // tbReorganize

  // Add partition to a partitioned table.
  static void tbAttachPartition(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENT:\n" +
       "  REORG TABLE \n" +
       "TO REORG THE DETACHED PARTITIONS  \n" +
       "\n    Execute the statements:\n" +
       "    ALTER TABLE large_ptab\n" +
       "      ATTACH PARTITION part2\n" +
       "      STARTING FROM (4) ENDING (6)\n" +
       "      FROM TABLE detach_part2\n\n" +
       "    ALTER TABLE large_ptab\n" +
       "      ATTACH PARTITION part2\n" +
       "      STARTING FROM (7) ENDING (9)\n" +
       "      FROM TABLE detach_part3");

     // reattach the reorganized detached partitions for table to support 
     // large RIDs.
     Statement stmt = con.createStatement();
     String str = "";

     str = "ALTER TABLE large_ptab ATTACH PARTITION part2" +
           " STARTING FROM (4) ENDING (6)" +
           " FROM TABLE detach_part2";
     stmt.executeUpdate(str);

     str = "ALTER TABLE large_ptab ATTACH PARTITION part3";
     str = str + " STARTING FROM (7) ENDING (9)";
     str = str + " FROM TABLE detach_part3";
     stmt.executeUpdate(str);

     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // tbAttachPartition

  // Drop tables.
  static void tbDrop(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENT:\n" +
       "  DROP \n" +
       "TO DROP THE TABLES  \n" +
       "\n    Execute the statements:\n" +
       "    DROP TABLE large\n" +
       "    DROP TABLE large_ptab");

     // drop the tables
     Statement stmt = con.createStatement();
     stmt.executeUpdate("DROP TABLE large");
     stmt.executeUpdate("DROP TABLE large_ptab");

     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // tbDrop

  // Drop tablespaces.
  static void tablespacesDrop(Connection con) throws SQLException
  {
    try
    {
     System.out.println(
       "\n-----------------------------------------------------------" +
       "\nUSE THE SQL STATEMENT:\n" +
       "  DROP \n" +
       "TO DROP THE TABLESPACES  \n" +
       "\n    Execute the statements:\n" +
       "    DROP TABLESPACE dms_tspace\n" +
       "    DROP TABLESPACE dms_tspace1\n" +
       "    DROP TABLESPACE dms_tspace2\n" +
       "    DROP TABLESPACE dms_tspace3");

     // drop the tablespaces
     Statement stmt = con.createStatement();
     stmt.executeUpdate("DROP TABLESPACE dms_tspace");
     stmt.executeUpdate("DROP TABLESPACE dms_tspace1");
     stmt.executeUpdate("DROP TABLESPACE dms_tspace2");
     stmt.executeUpdate("DROP TABLESPACE dms_tspace3");

     con.commit();
     stmt.close();

    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e, con);
      jdbcExc.handle();
    }
  } // tablespacesDrop
} // LargeRid
