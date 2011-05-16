//  Source File Name: GenerateC.java  1.2
/******************************************************************************/
/** Source File Name = GenerateC.java                                        **/
/** Licensed Materials - Property of IBM                                     **/
/** (C) COPYRIGHT International Business Machines Corp. 1999 - 2004          **/
/** All Rights Reserved.                                                     **/
/** US Government Users Restricted Rights - Use, duplication or disclosure   **/
/** restricted by GSA ADP Schedule Contract with IBM Corp.                   **
/**                                                                          **/
/**                                                                          **/
/** PURPOSE:          Constructs XML documents by calling dxxGenXMLClob      **/ 
/**                   stored procedure                                       **/
/**                                                                          **/
/** STEPS:            Compile this file by doing: javac GenerateC.java       **/
/**                   run JDBCGenXMLC.cmd or see usage below                 **/
/**                                                                          **/
/** FUNCTIONS USED:   dxxGenXMLClob stored procedure                         **/
/**                                                                          **/
/** CONFIGURATION:    Database already created                               **/
/**                   Database must enabled with XML Extender                **/
/**                   run: dxxadm enable_db <dbname>                         **/
/**                                                                          **/
/** USAGE:            java generateC <dbname> <dadfilename>                  **/
/**                      [-o OVERRIDE_TYPE override-string]                  **/
/******************************************************************************/                     


import java.sql.*;              // JDBC classes
import java.io.*;
import java.util.*;

/* DOCUMENTED */
/**
 *
 * <h2>Purpose</h2>
 * This class calls the dxxGenXML Stored Procedure.
 *
 * @version 1.0
 */

class GenerateC {
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

    /**
     * Utility method that returns the JDBC driver version.
     *
     * @param con
     *
     * @return
     * @exception SQLException
     */
    public static String getJDBCDriverVersion( Connection con )
    throws SQLException {
        DatabaseMetaData  dbmd = null;
        if ( con != null )
            dbmd = con.getMetaData();

        String    JDBCVersion = null;
        /*
          - Obtain driver name from DatabaseMetaData.
          - Parse to obtain version number.
        */

        if ((dbmd != null) &&
            (( JDBCVersion =  dbmd.getDriverName()) != null )) {
            StringTokenizer strTok = new StringTokenizer( JDBCVersion );
            String          tokenValue  = null;
            while ( strTok.hasMoreElements() == true ) {
                tokenValue = strTok.nextToken();
                if ( tokenValue.equalsIgnoreCase( "JDBC" ) ) {
                    if ( strTok.hasMoreElements() == true ) {
                        tokenValue = strTok.nextToken();//Get Number version
                        break;
                    }
                }
            }
            JDBCVersion = tokenValue;
        }
        return JDBCVersion;
    }


    public static void main (String argv[])
    {
        try {
        	
            if ((argv.length != 2) && (argv.length != 5)) {
                  System.out.println("Usage: java GenerateC dbname dadfilename [-o OVERRIDE_TYPE override-string]");
                  System.exit(1);
                }

                String DBName = argv[0];

                // read DAD
                // buffer is the temp 4k buffer to read in a while loop
                int bufSize = 4096;
                char[] buffer = new char[bufSize];
                StringBuffer StringDAD = new StringBuffer("");
                System.out.println ("\ndad file : " + argv[1] );
                //System.out.println ("\n result_tab : " + argv[2] );


                FileReader in = new FileReader(argv[1]);
                int nRead = -1;

                // read in a loop
                while ((nRead = in.read(buffer)) >=0) {
                  StringDAD.append(buffer, 0, nRead);
                }

            // get result_tab
            //String   result_tab = argv[2];

            System.out.println ("DAD size = "+ StringDAD.length());

            System.out.println();

            System.out.println ("Java GenXML Stored Procedure Sample");

            // Connect to Sample database

            System.out.println ("Connect to "+DBName);

            Connection con = null;
            String url = "jdbc:db2:"+DBName;

            con = DriverManager.getConnection(url);

            // Set AutoCommit
            con.setAutoCommit(true);

            String storedProcName = "db2xml.dxxGenXMLClob";

            // prepare the CALL statement
            CallableStatement callableStmt;
            String sql = null;
            if( GenerateC.getJDBCDriverVersion(con).equals("2.0") ){
                sql = "Call " + storedProcName + "(?, ?, ?, ?, ?, ?, ?, ?) ";
            } else {
                sql = "Call " + storedProcName + "(? ? ? ? ? ? ? ?) ";
            }

            callableStmt = con.prepareCall (sql);

            // register the output parameters
            int isValid = 0;
            int actualNumOfDocs = 0;
            int errCode = 0;
            Clob outClob ;
            String msgText = "";

            callableStmt.registerOutParameter (4, Types.CLOB);
            //callableStmt.setClob (4, outClob);
            callableStmt.registerOutParameter (5, Types.INTEGER);
            //callableStmt.setInt(5, isValid);
            callableStmt.registerOutParameter (6, Types.INTEGER);
            //callableStmt.setInt(6, actualNumOfDocs);
            callableStmt.registerOutParameter (7, Types.INTEGER);
            //callableStmt.setInt(7, errCode);
            callableStmt.registerOutParameter (8, Types.VARCHAR);
            //callableStmt.setString(8, msgText);

            // set all parameters
            callableStmt.setString(1, StringDAD.toString());
            //callableStmt.setString(2, result_tab);

            int  overrideType = 0;       // overrideType: NO_OVERRIDE
            String override = "";        // override value
            if (argv.length==5) {
              overrideType = (argv[3].equals("SQL_OVERRIDE"))? 1: 2;
              override = argv[4] + '\0';
            }

            callableStmt.setInt(2, overrideType);
            callableStmt.setString(3, override);

            //int maxNumOfDocs = 100;       // just set to 100 for this example
            //callableStmt.setInt(5, maxNumOfDocs);

            // call the stored procedure
            con.setAutoCommit(false);  // Enable transactions
            try {
                System.out.println ("\nCalling stored procedure : " + storedProcName );
                callableStmt.execute ();
                outClob = callableStmt.getClob (4);
                String outString = clobToString(outClob);
                System.out.println ("\n Document Generated:" + outString);
                // Commit the transaction
                con.commit();
            }
            catch (Exception e) {   // Rollback the transaction
                con.rollback();
                throw e;
            }

            finally {   // Restore initial AutoCommit
                con.setAutoCommit(true);
            }

            // retrieve output parameters

            //Reader reader = outClob.getCharacterStream();
            //Reader.read();

            isValid = callableStmt.getInt (5);
            actualNumOfDocs = callableStmt.getInt (6);
            errCode = callableStmt.getInt (7);
            msgText = callableStmt.getString (8);

            // display the information returned from the stored procedure

            System.out.println ("\n Document is valid = " + isValid);
            System.out.println ("\n Number of docs generated = " + actualNumOfDocs);
            System.out.println ("\n errCode = " + errCode);
            System.out.println (" msgText = " + msgText);

            callableStmt.close ();
        }
        catch (FileNotFoundException e) {
                System.err.println (e);
                return;
        }
        catch (IOException e) {
                System.out.println ("Error reading DAD file" + e);
                return;
        }
        catch (Exception e)     {
                System.err.println (e);
                return;
        }
    }

    public static String clobToString(Clob clob) throws Exception {

        if (clob == null)
                return null;

    Reader reader = clob.getCharacterStream();
    int bufSize = 1024;
    char[] cbuf = new char[bufSize];
    StringBuffer strBuf = new StringBuffer();
    int numRead = reader.read(cbuf, 0, bufSize);
    while (numRead > 0) {
        strBuf.append(cbuf, 0, numRead);
        numRead = reader.read(cbuf, 0, bufSize);
    }

    return strBuf.toString();
}
}
