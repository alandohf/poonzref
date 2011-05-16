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
      ** SOURCE FILE NAME: monreset.cbl
      **
      ** SAMPLE: How to reset database system monitor data areas
      **
      ** DB2 API USED:
      **         sqlgmrst -- RESET MONITOR
      **
      ** OUTPUT FILE: monreset.out (available in the online documentation)
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
       Program-Id. "monreset".

       Data Division.
       Working-Storage Section.

       copy "sqlutil.cbl".
       copy "sqlca.cbl".
       copy "sqlmonct.cbl".

      * Local Variables
       77 rc                  pic s9(9) comp-5.
       77 errloc              pic x(80).

      * variables for RESET DATABASE SYSTEM MONITOR DATA
       01 database.
         05 database-length   pic s9(4) comp-5 value 6.
         05 database-name     pic x(8) value "sample".

       Procedure Division.
       reset-pgm section.

           display "Sample COBOL Program : MONRESET.CBL".

           display "Reset Database Monitor Data for sample database".

      *******************************************************
      * RESET DATABASE SYSTEM MONITOR DATA AREAS API called *
      *******************************************************
           call "sqlgmrst" using
                                 by value   database-length
                                 by value   0
                                 by reference SQLCA
                                 by reference database-name
                                 by value   SQLM-OFF
                                 by value   0
                                 by value   SQLM-DBMON-VERSION2
                           returning rc.

           move "RESET DB MONITOR" to errloc.
           call "checkerr" using SQLCA errloc.

           display "Database Monitor Reset for sample was successful".
       end-reset. stop run.
