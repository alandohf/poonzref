//  Source File Name: Shred.java  1.2
/******************************************************************************/
/** Source File Name = Shred.java                                            **/
/** Licensed Materials - Property of IBM                                     **/
/** (C) COPYRIGHT International Business Machines Corp. 1999 - 2002          **/
/** All Rights Reserved.                                                     **/
/** US Government Users Restricted Rights - Use, duplication or disclosure   **/
/** restricted by GSA ADP Schedule Contract with IBM Corp.                   **
/**                                                                          **/
/**                                                                          **/
/** PURPOSE:          Decompose a XML document to database                   **/
/**                                                                          **/
/** STEPS:            Compile this file by doing: javac Shred.java           **/
/**                   run JDBCShredXML.cmd or see usage below                **/
/**                                                                          **/
/** FUNCTIONS USED:   dxxShredXML stored procedure                           **/
/**                                                                          **/
/** CONFIGURATION:    Database already created                               **/
/**                   Database must be enabled with XML Extender
/**                   run: dxxadm enable_db <dbname>
/**                                                                          **/
/** USAGE:            java Shred <dbname> <dadfilename> <xmlfilename>        **/
/**                                                                          **/
/******************************************************************************/


import java.sql.*;              // JDBC classes
import java.io.*;
import java.util.*;

/* DOCUMENTED */
/**
 *
 * <h2>Purpose</h2>
 * This class calls the dxxShredXML Stored Procedure.
 *
 * @version 1.0
 */

class Shred {
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
    		
    		if (argv.length < 3) {
    		  System.out.println("Usage: java Shred dbname dadfilename xmlfilename");
    		  System.exit(1);
    		}
    		
  		String DBName = argv[0];
    		
                // buffer is the temp 4k buffer to read in  while loop

		int bufSize = 4096;
		char[] buffer = new char[bufSize];
		StringBuffer StringDAD = new StringBuffer("");
		StringBuffer StringXML = new StringBuffer("");
		
		FileReader in = new FileReader(argv[1]);
		int nRead = -1;
		
                // read in a loop
		while ((nRead = in.read(buffer)) >=0) {
		  StringDAD.append(buffer, 0, nRead);
		}
		
		in = new FileReader(argv[2]);
		
		while ((nRead = in.read(buffer)) >=0) {
		  StringXML.append(buffer, 0, nRead);
		}

	    System.out.println ("DAD size = "+ StringDAD.length());
	    System.out.println ("XML size = "+ StringXML.length());
	    
	    System.out.println();
	    
       	    System.out.println ("Java Shred Stored Procedure Sample");
			
            // Connect to Sample database
            
            System.out.println ("Connect to "+DBName); 

            Connection con = null;
            // URL is jdbc:db2:dbname
            String url = "jdbc:db2:"+DBName;

            con = DriverManager.getConnection(url);

            // Set AutoCommit
            con.setAutoCommit(true);

            String storedProcName = "db2xml.dxxShredXML";

            // prepare the CALL statement
            CallableStatement callableStmt;
            String sql = null;
           if( Shred.getJDBCDriverVersion(con).equals("2.0") ){
               sql = "Call " + storedProcName + "(?, ?, ?, ?) ";
           } else {
               sql = "Call " + storedProcName + "(? ? ? ?) ";
           }

            callableStmt = con.prepareCall (sql);

            // register the output parameters
            
            int errCode = 0;
            String msgText = "";
            
            callableStmt.registerOutParameter (3, Types.INTEGER);
            callableStmt.setInt(3, errCode);
            callableStmt.registerOutParameter (4, Types.VARCHAR);
            callableStmt.setString(4, msgText);

            // set all parameters 
  	    callableStmt.setString(1, StringDAD.toString());
  	    callableStmt.setString(2, StringXML.toString());
  	    
            // call the stored procedure
            con.setAutoCommit(false);  // Enable transactions
            try	{   
            	System.out.println ("\n  Calling stored procedure : " + storedProcName );
                callableStmt.execute ();

                // Commit the transaction
                con.commit();
            } 
            catch (Exception e) {   // Rollback the transaction
                e.printStackTrace();
                con.rollback();
                throw e; 
            }
            
            finally {   // Restore initial AutoCommit
                con.setAutoCommit(true);
            }
 
            // retrieve output parameters
            errCode = callableStmt.getInt (3);
            msgText = callableStmt.getString (4);

            // display the information returned from the stored procedure
            System.out.println ("\n errCode = " + errCode);
            System.out.println (" msgText = " + msgText);
      
            callableStmt.close ();
        }
        catch (FileNotFoundException e) {
        	System.err.println (e);
        	return;
        }
        catch (IOException e) {
        	System.out.println ("Error reading input file" + e);
        	return;
        }
        catch (Exception e)	{   
        	System.err.println (e);
        	return;
        }
    }
}
