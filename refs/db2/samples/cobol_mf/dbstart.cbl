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
      ** SOURCE FILE NAME: dbstart.cbl 
      **
      ** SAMPLE: How to start a database manager
      **
      ** DB2 API USED:
      **          sqlgpstart -- START DATABASE MANAGER
      **
      ** OUTPUT FILE: dbstart.out (available in the online documentation)
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
       Program-ID. "dbstart".

       Data Division.
       Working-Storage Section.

           copy "sqlenv.cbl".
           copy "sqlca.cbl".

      * Local variables
       77 rc            pic s9(9) comp-5.
       77 errloc        pic x(80).

       Procedure Division.
       Main Section.
           display "Sample COBOL program: DBSTART.CBL".

      **************************
      * START DATABASE MANAGER *
      **************************

           call "sqlgpstart" using
                                  by value 0         
                                  by reference sqlca
                             returning rc.
           if rc equal SQLE-RC-INVSTRT
              display "The database manager is already active"
              go to End-Main.

           move "START DATABASE MANAGER" to errloc.
           call "checkerr" using SQLCA errloc.

           display "The database has been successfully STARTED".
       End-Main.
           stop run.
