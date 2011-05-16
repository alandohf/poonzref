      ***********************************************************************
      ** Licensed Materials - Property of IBM
      ** 
      ** Governed under the terms of the International
      ** License Agreement for Non-Warranted Sample Code.
      **
      ** (C) COPYRIGHT International Business Machines Corp. 1995 - 2002  
      ** All Rights Reserved.
      **
      ** US Government Users Restricted Rights - Use, duplication or
      ** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
      ***********************************************************************
      **
      ** SOURCE FILE NAME: d_dbmcon.cbl 
      **
      ** SAMPLE: Get database manager configuration defaults 
      **
      ** DB2 APIs USED:
      **         sqlgdsys -- GET DATABASE MANAGER CONFIGURATION DEFAULTS
      **         sqlgaddr -- GET ADDRESS
      **
      ** OUTPUT FILE: d_dbmcon.out (available in the online documentation)
      ***********************************************************************
      **
      ** For more information on the sample programs, see the README file. 
      **
      ** For information on developing COBOL applications, see the 
      ** Application Development Guide.
      **
      ** For information on DB2 APIs, see the Administrative API Reference.
      **
      ** For the latest information on programming, compiling, and running
      ** DB2 applications, visit the DB2 application development website: 
      **     http://www.software.ibm.com/data/db2/udb/ad
      ***********************************************************************

       Identification Division.
       Program-Id. "d_dbmcon".

       Data Division.
       Working-Storage Section.
       copy "sqlutil.cbl".
       copy "sqlca.cbl".
      

      * Local Variables

       77 rc                  pic s9(9) comp-5.
       77 errloc              pic x(80).

       01 dbname              pic x(8) value "sample".
       01 dbname-len          pic s9(4) comp-5 value 6.

       01 numbdb              pic s9(4) comp-5.
      
      * variables for GET ADDRESS
       01 max-agents          pic 9(9) comp-5.
       01 tokenlist.
          05 tokens occurs 2 times.
             10 token         pic 9(4) comp-5.
             $IF P64 SET
	        10 filler        pic x(6). 
	     $ELSE
	        10 filler        pic x(2).
              $END 
	     10 tokenptr      usage is pointer.

      * variables for GET DATABASE MANAGER CONFIGURATION DEFAULTS
       01 listnumber          pic s9(4) comp-5 value 2.
      

       Procedure Division.
       dbmcon-pgm section.

           display "Sample COBOL Program : D_DBMCON.CBL".

           move SQLF-KTN-MAXAGENTS  to token(1).
           move SQLF-KTN-NUMDB to token(2).
           move "GET ADDRESS" to errloc.
      
      **************************
      * GET ADDRESS API called *
      **************************
           call "sqlgaddr" using by reference max-agents
                                 by reference tokenptr(1)
                           returning rc.
      
           call "sqlgaddr" using by reference numbdb
                                 by reference tokenptr(2)
                           returning rc.
      
      **************************************************
      * GET DATABASE CONFIGURATION DEFAULTS API called *
      **************************************************
           call "sqlgdsys" using by value     listnumber
                                 by reference tokenlist
                                 by reference sqlca
                           returning rc.
      

           move "GET DB CFG DEFAULTS" to errloc.
           call "checkerr" using SQLCA errloc.

           display "Max. number of Agents                  : ",
                    max-agents.
           display "Number of concurrent active DB allowed : ",
                    numbdb.

       end-dbmcon. stop run.
