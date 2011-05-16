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
      ** SOURCE FILE NAME: restart.cbl 
      **
      ** SAMPLE: How to restart a database
      **
      **         This program shows how to restart a database after it 
      **         has been abnormally terminated.
      **
      ** DB2 API USED:
      **         sqlgrstd -- RESTART DATABASE
      **
      ** OUTPUT FILE: restart.out (available in the online documentation)
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
       Program-ID. "restart".

       Data Division.
       Working-Storage Section.

           copy "sqlenv.cbl".
           copy "sql.cbl".
           copy "sqlca.cbl".

      * Local variables
       77 rc            pic s9(9) comp-5.
       77 errloc        pic x(80).

      * Variables used for the RESTART DATABASE API
       77 dbname-len    pic s9(4) comp-5 value 0.
       77 passwd-len    pic s9(4) comp-5 value 0.
       77 userid-len    pic s9(4) comp-5 value 0.
       77 dbname        pic x(9).
       77 passwd        pic x(19).
       77 userid        pic x(9).

       Procedure Division.
       Main Section.
           display "Sample COBOL program: RESTART.CBL".

           display "Enter in the database name to restart :" with
              no advancing.
           accept dbname.

           display "Enter in your user id :" with no advancing.
           accept userid.

           display "Enter in your password :" with no advancing.
           accept passwd.

           inspect dbname tallying dbname-len for characters before
              initial " ".

           inspect userid tallying userid-len for characters before
              initial " ".

           inspect passwd tallying passwd-len for characters before
              initial " ".

      ****************************
      * RESTART DATABASE MANAGER *
      ****************************
           call "sqlgrstd" using
                                 by value       passwd-len
                                 by value       userid-len
                                 by value       dbname-len
                                 by reference   sqlca
                                 by reference   passwd
                                 by reference   userid
                                 by reference   dbname
                           returning rc.
           move "RESTART DATABASE" to errloc.
           call "checkerr" using SQLCA errloc.

           display "The database has been successfully RESTARTED".
       End-Main.
           stop run.
