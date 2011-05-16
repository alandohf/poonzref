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
      ** SOURCE FILE NAME: setact.cbl 
      **
      ** SAMPLE: How to set accounting string
      **
      ** DB2 API USED:
      **         sqlgsact -- SET ACCOUNTING STRING
      **
      ** OUTPUT FILE: setact.out (available in the online documentation)
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
       Program-ID. "setact".

       Data Division.
       Working-Storage Section.

           copy "sqlenv.cbl".
           copy "sql.cbl".
           copy "sqlca.cbl".

      * Local variables
       77 rc            pic s9(9) comp-5.
       77 errloc        pic x(80).

      * Variables for the SET ACCOUNTING STRING API
       77 account-str-len       pic s9(4) comp-5 value 0.
       77 account-str           pic x(200).

       Procedure Division.
       Main Section.
           display "Sample COBOL program: SETACT.CBL".

           move " " to account-str.

      *************************
      * SET ACCOUNTING STRING *
      *************************
           call "sqlgsact" using
                                 by value       account-str-len
                                 by reference   account-str
                                 by reference   sqlca
                           returning rc.
           move "SET ACCOUNTING STRING" to errloc.
           call "checkerr" using SQLCA errloc.

           display "The accounting string has been set".
       End-Main.
           stop run.
