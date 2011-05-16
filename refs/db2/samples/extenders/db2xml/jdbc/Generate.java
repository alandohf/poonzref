//  Source File Name: Generate.java  1.2
/******************************************************************************/
/** Source File Name = Generate.java                                         **/
/** Licensed Materials - Property of IBM                                     **/
/** (C) COPYRIGHT International Business Machines Corp. 1999 - 2004          **/
/** All Rights Reserved.                                                     **/
/** US Government Users Restricted Rights - Use, duplication or disclosure   **/
/** restricted by GSA ADP Schedule Contract with IBM Corp.                   **/
/**                                                                          **/
/**                                                                          **/
/** PURPOSE:          Composes the XML document specified by the DAD file    **/
/**                                                                          **/
/** STEPS:            Compile this file by doing: javac Generate.java        **/
/**                   run JDBCGenXML.cmd or see usage below                  **/
/**                                                                          **/
/** FUNCTIONS USED:   dxxGenXML stored procedure                             **/
/**                                                                          **/
/** CONFIGURATION:    Database already created                               **/
/**                   Database must enabled with XML Extender                **/
/**                   run: dxxadm enable_db <dbname>                         **/
/**                                                                          **/
/** USAGE:            java Generate <dbname> <dadfilename> <result_tab>      **/
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

class Generate {
    static
    {
        try {
            Class.forName ("COM.ibm.db2.jdbc.app.DB2Driver").newInstance ();
        } catch (Exception e) {
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

            if ((argv.length != 3) && (argv.length != 6)) {
                System.out.println("Usage: java Generate dbname dadfilename result_tab [-o OVERRIDE_TYPE override-string]");
                System.exit(1);
            }

            String DBName = argv[0];

            // read DAD
            // buffer is the temp 4k buffer to read in a while loop
            int bufSize = 4096;
            char[] buffer = new char[bufSize];
            StringBuffer StringDAD = new StringBuffer("");
            System.out.println ("\n dad file : " + argv[1] );
            System.out.println ("\n result_tab : " + argv[2] );


            FileReader in = new FileReader(argv[1]);
            int nRead = -1;

            // read in a loop
            while ((nRead = in.read(buffer)) >=0) {
                StringDAD.append(buffer, 0, nRead);
            }

            // get result_tab
            String   result_tab = argv[2];

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

            String storedProcName = "db2xml.dxxGenXML";

            // prepare the CALL statement
            CallableStatement callableStmt;

            String sql = null;
            if ( Generate.getJDBCDriverVersion(con).equals("2.0") ) {
                sql = "Call " + storedProcName + "(?, ?, ?, ?, ?, ?, ?, ?) ";
            } else {
                sql = "Call " + storedProcName + "(? ? ? ? ? ? ? ?) ";
            }
            callableStmt = con.prepareCall (sql);

            // register the output parameters
            int actualNumOfDocs = 0;
            int errCode = 0;
            String msgText = "";

            callableStmt.registerOutParameter (6, Types.INTEGER);
            callableStmt.setInt(6, actualNumOfDocs);
            callableStmt.registerOutParameter (7, Types.INTEGER);
            callableStmt.setInt(7, errCode);
            callableStmt.registerOutParameter (8, Types.VARCHAR);
            callableStmt.setString(8, msgText);

            // set all parameters
            callableStmt.setString(1, StringDAD.toString());
            callableStmt.setString(2, result_tab);

            int  overrideType = 0;       // overrideType: NO_OVERRIDE
            String override = "";        // override value
            if (argv.length==6) {
                overrideType = (argv[4].equals("SQL_OVERRIDE"))? 1: 2;
                override = argv[5] + '\0';
            }

            callableStmt.setInt(3, overrideType);
            callableStmt.setString(4, override);

            int maxNumOfDocs = 100;       // just set to 100 for this example
            callableStmt.setInt(5, maxNumOfDocs);

            // call the stored procedure
            con.setAutoCommit(false);  // Enable transactions
            try {
                System.out.println ("\n  Calling stored procedure : " + storedProcName );
                callableStmt.execute ();

                // Commit the transaction
                con.commit();
            } catch (Exception e) {   // Rollback the transaction
                con.rollback();
                throw e;
            }

            finally {   // Restore initial AutoCommit
                con.setAutoCommit(true);
            }

            // retrieve output parameters
            actualNumOfDocs = callableStmt.getInt (6);
            errCode = callableStmt.getInt (7);
            msgText = callableStmt.getString (8);

            // display the information returned from the stored procedure
            System.out.println ("\n Number of docs generated = " + actualNumOfDocs);
            System.out.println ("\n errCode = " + errCode);
            System.out.println (" msgText = " + msgText);

            callableStmt.close ();
        } catch (FileNotFoundException e) {
            System.err.println (e);
            return;
        } catch (IOException e) {
            System.out.println ("Error reading DAD file" + e);
            return;
        } catch (Exception e) {
            System.err.println (e);
            return;
        }
    }
}
