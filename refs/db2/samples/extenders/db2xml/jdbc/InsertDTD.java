//  Source File Name: InsertDTD.java
/******************************************************************************/
/** Source File Name = InsertDTD.java                                        **/
/** Licensed Materials - Property of IBM                                     **/
/** (C) COPYRIGHT International Business Machines Corp. 2003 - 2004          **/
/** All Rights Reserved.                                                     **/
/** US Government Users Restricted Rights - Use, duplication or disclosure   **/
/** restricted by GSA ADP Schedule Contract with IBM Corp.                   **/
/**                                                                          **/
/**                                                                          **/
/** PURPOSE:       This is a sample Java program to insert a DTD             **/
/**                document in unicode (UTF-8) codepage into the             **/
/**                XML Extender db2xml.dtd_ref table.                        **/
/**                                                                          **/
/** STEPS:         Compile this file by running: javac InsertDTD.java        **/
/**                                                                          **/
/** CONFIGURATION: You must have a database that is enabled for XML Extender **/
/**                                                                          **/
/** USAGE:                                                                   **/
/**        java InsertDTD <dbname> <dtdfile> <dtdid> <userid> <password>     **/
/**        If you are running a 64-bit instance, you must add the            **/
/**        -d64 option to the java command before executing it.              **/
/**                                                                          **/
/**                                                                          **/
/**                                                                          **/
/******************************************************************************/


import java.sql.*;
import java.io.*;


/* DOCUMENTED */
/**
 *
 * <h2>Purpose</h2>
 * This class inserts a DTD document in unicode (UTF-8) codepage into the XML Extender db2xml.dtd_ref table.
 * @version 1.0
 */
class InsertDTD {
   static
   {
        try {
          Class.forName ("COM.ibm.db2.jdbc.app.DB2Driver").newInstance ();
          }
        catch (Exception e) {
          System.err.println ("\n  Error loading DB2 Driver...\n" + e);
          System.exit(1);
          }
    }

   public static String getALine() {        // reads a line from standard input

     InputStreamReader reader=new InputStreamReader(System.in);
     BufferedReader buffer =new BufferedReader(reader);
     String aLine="";
     
     try { 
     	aLine=buffer.readLine();
        } 
     catch (IOException e) {}

     return ( aLine );
            
     }

    public static void main (String argv[]) {
        try {


            if (argv.length < 3) {
              System.out.println("Usage: java InsertDTD DBName DTD-file DTD-ID Userid Password");
              System.exit(1);
              }
            int ch;
            String DBName = argv[0];
            String DTDid  = argv[2];
            String UserID = "";
            String PassWd = "";
            if (argv.length > 3) {
               UserID = argv[3];
               if ( argv.length > 4 ) {
                 PassWd = argv[4];
                 }
               }
            else {
               System.out.println("\nIf accessing the database remotely, enter UserID. Press Enter when done.");
               UserID = getALine();
               if ( !UserID.equals("") ) {
                  System.out.println("Enter Password. Press Enter when done.");
                  PassWd = getALine();
                  }
               }

            FileInputStream fis1 = null;
            try {
             fis1 = new FileInputStream(argv[1]);
             }
            catch (FileNotFoundException fe) {
             System.out.println (fe.getMessage());
             throw fe;
            }
            
            StringBuffer content = new StringBuffer("");
            
        
            //User can choose to change UTF-8 to some other encoding that the document might be using.
            InputStreamReader isr1 = new InputStreamReader(fis1, "UTF-8");
            Reader in1 = new BufferedReader(isr1);

            // read in a loop
            while ((ch = in1.read()) >=0) {
              content.append((char)ch);
            }

            Connection con = null;
            String url = "jdbc:db2:" + DBName;

            con = DriverManager.getConnection(url, UserID, PassWd);

            con.setAutoCommit(true);
            System.out.println ("Connected to " + url  );

            try {
              PreparedStatement pstmt1=null;

              pstmt1 = con.prepareStatement ("INSERT into DB2XML.DTD_REF (DTDID, CONTENT, USAGE_COUNT) values(?, ?, 0)");
              pstmt1.setString(1,DTDid);
              pstmt1.setString(2,content.toString());

              pstmt1.execute();

              System.out.println("\nDTD file inserted");

              pstmt1.close();
              }

            catch( Exception e ) {
               System.err.println (e);
               return;
               }

            }
        catch( Exception e ) {
          System.out.println(e);
         }
 }
}
