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
      ** SOURCE FILE NAME: migrate.cbl 
      **
      ** SAMPLE: Demonstrates how to migrate to a database
      **
      ** DB2 API USED:
      **         sqlgmgdb -- MIGRATE DATABASE
      **
      ** OUTPUT FILE: migrate.out (available in the online documentation)
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
       Program-Id. "migrate".

       Data Division.
       Working-Storage Section.

       copy "sqlenv.cbl".
       copy "sqlca.cbl".

      * variables used for MIGRATE API
       01 database.
         49 database-length       pic s9(4) comp-5 value 0.
         49 database-name         pic x(9).

       01 usr.
         49 usrid-length   pic s9(4) comp-5 value 0.
         49 usrid-name     pic x(19).

       01 passwd.
         49 passwd-length   pic s9(4) comp-5 value 0.
         49 passwd-name     pic x(19).

      * Local Variables

       77 rc                  pic s9(9) comp-5.
       77 errloc              pic x(80).

       Procedure Division.
       migrate-pgm section.

           display "Sample COBOL Program : MIGRATE.CBL".

           display "Enter the name of the database : " with no advancing.
           accept database-name.
           inspect database-name tallying database-length for characters
              before initial " ".
           display " ".

           display "Enter in your user id : " with no advancing.
           accept usrid-name.

           inspect usrid-name tallying usrid-length for characters
              before initial " ".
           display " ".

           display "Enter in your password : " with no advancing.
           accept passwd-name.

           inspect passwd-name tallying passwd-length for characters
              before initial " ".
           display " ".

      *********************************
      * MIGRATE DATABASE API called   *
      *********************************
           call "sqlgmgdb" using
                                 by value     passwd-length
                                 by value     usrid-length
                                 by value     database-length
                                 by reference sqlca
                                 by reference passwd-name
                                 by reference usrid-name
                                 by reference database-name
                           returning rc.
           if sqlcode equal SQLE-RC-MIG-OK
              go to migrate-complete.
           move "MIGRATE DATABASE" to errloc.
           call "checkerr" using SQLCA errloc.

       migrate-complete.
           display "Migrate Database completed successfully".

       end-migrate. stop run.
