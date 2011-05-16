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
      ** SOURCE FILE NAME: monsz.cbl 
      **
      ** SAMPLE: How to get a database monitor snapshot
      **
      **         This program first requests for the buffer size that would
      **         required for issuing a snapshot for locks, tables, and 
      **         database level information.
      **
      **         This testcase will return SQL1611, no data was returned
      **         by Database System Monitor. Some activity must be done to
      **         generate data for the snapshot: connect to database, 
      **         manipulate data, etc
      **
      ** DB2 APIs USED:
      **         sqlgmnsz -- ESTIMATE BUFFER SIZE
      **         sqlgmnss -- GET SNAPSHOT
      **
      ** OUTPUT FILE: monsz.out (available in the online documentation)
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
       Program-Id. "monsz".

       Data Division.
       Working-Storage Section.

       copy "sqlca.cbl".
       copy "sqlmon.cbl".
       copy "sqlmonct.cbl".

      * Local Variables
       77 rc                  pic s9(9) comp-5.
       77 errloc              pic x(80).

       77 rezerv1             pic 9(9) comp-5 value 0.
       77 rezerv2             pic 9(9) comp-5 value 0.
       77 current-version     pic 9(9) comp-5 value 0.

      * variables for ESTIMATE DATABASE SYSTEM MONITOR BUFFER SIZE
      *  and for DATABASE SYSTEM MONITOR SNAPSHOT
       01 buff.
          05 buffer-sz        pic 9(9) comp-5 value 0.
          05 buffer           occurs 0 to 100000 times 
                              depending on buffer-sz.
             10 element       pic x.

       01 database-name.
         05 pic x(6) value "sample".
         05 pic x    value x"00".
 
       Procedure Division.
       monsz-pgm section.

           display "Sample COBOL Program : MONSZ.CBL".

      * Request SQLMA-DBASE, SQLM-DBASE-TABLES, and SQLMA-DBASE-LOCKS 
      * in sqlma

      * set the input to SQLMA structure to monitor 3 objects
           move 3 to OBJ-NUM of SQLMA.
           move SQLMA-DBASE to OBJ-TYPE of OBJ-VAR(1).
           move SQLMA-DBASE-LOCKS to OBJ-TYPE of OBJ-VAR(2).
           move SQLMA-DBASE-TABLES to OBJ-TYPE of OBJ-VAR(3).

      * monitor the sample database
           move database-name to SQLMA-OBJECT of OBJ-VAR(1).
           move database-name to SQLMA-OBJECT of OBJ-VAR(2).
           move database-name to SQLMA-OBJECT of OBJ-VAR(3).

           move SQLM-CURRENT-VERSION to current-version.

      ***********************************************************
      * ESTIMATE DATABASE SYSTEM MONITOR BUFFER SIZE API called *
      ***********************************************************
           call "sqlgmnsz" using
                                 by value     rezerv1
                                 by reference sqlca
                                 by reference buffer-sz
                                 by reference SQLMA
                                 by reference rezerv2
                                 by value     current-version
                           returning rc.

           move "ESTIMATE BUFFER SIZE" to errloc.
           call "checkerr" using SQLCA errloc.

           display "Buffer size required for this snapshot is ", 
                    buffer-sz.

      ***********************************************
      * DATABASE SYSTEM MONITOR SNAPSHOT API called *
      ***********************************************
           call "sqlgmnss" using
                                 by value     rezerv1
                                 by reference sqlca
                                 by reference SQLM-COLLECTED
                                 by reference buffer(1)
                                 by value     buffer-sz
                                 by reference SQLMA
                                 by reference rezerv2
                                 by value     current-version
                           returning rc.

           move "TAKING SNAPSHOT" to errloc.
           call "checkerr" using SQLCA errloc.

       end-monsz. stop run.
