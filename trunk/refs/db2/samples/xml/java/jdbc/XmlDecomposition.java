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
// SOURCE FILE NAME: XmlDecomposition.java
// 
// SAMPLE: This sample demonstrates XML Decomposition functionality. Using
//        this functionality, information from a XML document can be
//        stored in relational tables.
//
// USER SCENARIO:
//
//        Consider the user scenario below:
//
//        A bookstore owner has some XML documents which contains descriptive
//        information about a book which he has for sale. The owner needs to
//        store these details in a relational table for easy retrival of information.
//        He/She can easily do it using the Decomposition function.
//
// SOLUTION:
//        The user must have an annotated schema based on which the instance document
//        can be decomposed. Once a valid annotated schema for the instance document
//        is ready , it needs to be registered with the XML Schema repository with
//        decomposition option enabled. Also the tables in which the data will be
//        decomposed should exist before the schema is registered. Now using the new
//        XMLDecomp function, the user can decompose the instance document and put the
//        data in the relational tables.
//
//        Here the tables that we need are
//             a) ADMIN.BOOK_AUTHOR
//             b) XDB.BOOK_CONTENTS
//
//       As per the schema document BOOKDETAIL.XSD, the data in the instance document
//       BOOKDETAIL.XML will be put into these two tables. As per the annotations in
//       the xmlschema, the schema for the table BOOK_AUTHOR will be ADMIN. While for
//       the other tables it will be the value assigned by the annotation
//          defaultSQLSchema which is XDB.
//       This annotation can be used only once in the xmlschema.
//
//       The text within the tag "authorId" will be of type integer and will be inserted
//       in the column "AUTHID" of the TABLE "BOOK_AUTHOR". A condition annotation has
//       been put here to check if the "AUTHID" is a number between 1 and 999. If the
//       value passes the CONDITION check, then it is inserted in the table.
//
//       The text in the "chapter" tag is inserted in different tables and different
//       columns. The contents of tag "chaptercontents" is inserted in the column
//       "CHPTCONTENT" of TABLE "BOOK_CONTENTS". The annoatation truncate indicates
//       that the value to be inserted into the column will be trucated if its size is larger
//       than the column size. Another annotation that is used for this element is
//       contenthandling, which indicates that the concatenation of this element's character
//       data (including character content of CDATA sections) with the character data in this
//       element's descendants, in document order will be inserted into the table.
//
// PRE-REQUISTES
//       The instance document i,e. "bookdetail.xml" and the annotated schema that will be
//       registered to the XSR "bookdetail.xsd" have to exist in the same directory as the
//       sample itself. The Schema document needs to be properly annotated to ensure that
//       the right data is inserted into the right table.
//
// EXECUTION
//       The sample can be executed by first running the setup script which creates
//       the required tables. The script can be run using the command
//            db2 -tvf setupfordecomposition.db2
//       Build the application using the command
//            javac xmldecomposition.java
//       Execute by invoking
//            java xmldecomposition
//       The clean up script will have to be executed to drop all the tables that
//       were create by the setupscript.
//            db2 -tvf cleanupfordecomposition.db2
//
// SQL STATEMENTS USED:
//         REGISTER XMLSCHEMA
//         COMPLETE XMLSCHEMA
//         SELECT
//         DECOMPOSE
//
// Classes used from Util.java are:
//         Db
//         Data
//         JdbcException
//         Statement
//         ResultSet
//
// OUTPUT FILE: XmlDecomposition.out (available in the online documentation)
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
import java.io.*;

class XmlDecomposition
{
  public static void main(String argv[])
  {
    try
    {
      Db db = new Db(argv);

      System.out.println();
      System.out.println("THIS SAMPLE DEMONSTRATES TO DECOMPOSE DATA FROM XML FILE");

      // connect to the 'sample' database
      db.connect();

      XmlDecompose(db.con);

      // disconnect from the 'sample' database
      db.disconnect();
    }
    catch (Exception e)
    {
      JdbcException jdbcExc = new JdbcException(e);
      jdbcExc.handle();
    }
  } // main
  
  static void XmlDecompose(Connection con)
  {
    try
      {
         String dbname;
         String RelSchema;
         String SchemaName;
         String SchemaLocation;
         String PrimaryDocument;
         String xmlfilename;
         int shred = 1;
         String Status;
         String Decomposition;
         String Decomposition_version;
         boolean  xmlRegister = false;
         boolean  xmlAdd = false;
         boolean  xmlComplete = false;
         boolean  xmlDecomp = false;
    
         RelSchema = "xdb";
         SchemaName = "bookdetail";
         SchemaLocation = "http://bookdetail/schema1";
         PrimaryDocument = "bookdetail.xsd";
         xmlfilename = "bookdetail.xml";
 
         // Register the XML Schema to the XSR.
         CallableStatement callStmt = con.prepareCall("CALL SYSPROC.XSR_REGISTER(?,?,?,?,NULL)");
         File xsdfile = new File(PrimaryDocument);
         FileInputStream xsdfileis = new FileInputStream(xsdfile);

         callStmt.setString(1, RelSchema );
         callStmt.setString(2, SchemaName );
         callStmt.setString(3, SchemaLocation );
         callStmt.setBinaryStream(4, xsdfileis, (int)xsdfile.length() );
         callStmt.execute();
         xsdfileis.close();
         callStmt.close();
         System.out.println("**** CALL SYSPROC.XSR_REGISTER SUCCESSFULLY");

         // Complete the Schema registration with Validate Option true.
         callStmt = con.prepareCall("CALL SYSPROC.XSR_COMPLETE(?,?,NULL,?)");
         callStmt.setString(1, RelSchema );
         callStmt.setString(2, SchemaName );
         callStmt.setInt(3, shred );
         callStmt.execute();
         callStmt.close();
         System.out.println("**** CALL SYSPROC.XSR_COMPLETE SUCCESSFULLY");

         // Check the status of the XSR object registered.
         Statement stmt = con.createStatement();
         ResultSet rs = stmt.executeQuery(
           "SELECT status, decomposition, decomposition_version FROM SYSIBM.SYSXSROBJECTS WHERE XSROBJECTNAME = 'BOOKDETAIL'");
   
         while(rs.next())
          {
            Status = rs.getString(1);
            Decomposition = rs.getString(2);
            Decomposition_version = rs.getString(3);

            System.out.println("\nStatus          : " +
                               Data.format(Status, 5) + "\n" +
                               "Decomposition      : " +
                               Data.format(Decomposition, 5) + "\n" +
                               "Version : " +
                               Data.format(Decomposition_version, 5));
          } 
        rs.close();       

        // Decompose the XML document by calling the SYSPROC.XDBDECOMPXML
        callStmt = con.prepareCall("CALL SYSPROC.XDBDECOMPXML(?,?,?,?,?, NULL, NULL, NULL)");
        File xmlfile = new File(xmlfilename);
        FileInputStream xmlfileis = new FileInputStream(xmlfile);
        callStmt.setString(1, RelSchema );
        callStmt.setString(2, SchemaName );
        callStmt.setBinaryStream(3, xmlfileis, (int)xmlfile.length() );
        callStmt.setString(4, SchemaName );
        callStmt.setInt(5, shred);
        callStmt.execute();
        xmlfileis.close();
        callStmt.close();
        System.out.println("**** CALL SYSPROC.XDBDECOMPXML SUCCESSFULLY");

        // Read Data from the tables, where the data is stored after decomposition.
        SelectFromTables(con);
    
      }
    catch (Exception e)
      {
        JdbcException jdbcExc = new JdbcException(e, con);
        jdbcExc.handle();
      }
  }
  static void SelectFromTables(Connection con)
  {
    try
      {
        String isbn = "";
        int chptnum = 0;
        String chpttittle = "";
        String chptcontent = "";
        int authid = 0;
        String book_title = "";
        String status = "";
        String decompose = "";
        String decomp_version = "";

        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery(
          "SELECT isbn, chptnum, chpttittle, chptcontent FROM XDB.BOOK_CONTENTS");

        while (rs.next())
          {
            isbn = rs.getString(1);
            chptnum = rs.getInt(2);
            chpttittle = rs.getString(3);
            chptcontent = rs.getString(4);
 
            System.out.println("\nISBN          : " +
                               Data.format(isbn, 13) + "\n" +
                               "CHAPTER NUMBER  : " +
                               Data.format(chptnum, 5) + "\n" +
                               "Chapter Title   : " +
                               Data.format(chpttittle, 50) + "\n" +
                               "Chapter Content : " +
                               Data.format(chptcontent, 1000));
          } 
  
        // Select data from the ADMIN.BOOK_AUTHOR TABLE.
        rs = stmt.executeQuery("SELECT authid, isbn, book_title FROM ADMIN.BOOK_AUTHOR");
       
        while(rs.next())
          {
            authid = rs.getInt(1);
            isbn = rs.getString(2);
            book_title = rs.getString(3);
            
            System.out.println("\nAuthor ID   : " +
                              Data.format(authid, 5) + "\n" +
                              "ISBN       : " + 
                              Data.format(isbn, 13) + "\n" +
                              "Book Title : " +
                              Data.format(book_title, 50));
          } 
        rs.close();
      }
    catch (Exception e)
      {
        JdbcException jdbcExc = new JdbcException(e, con);
        jdbcExc.handle();
      } //Try Block
   }  //SelectFromTable
}  //XmlDecomposition Class  
   
