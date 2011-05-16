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
      ** SOURCE FILE NAME: ebcdicdb.cbl 
      **
      ** SAMPLE: Create a database with EBCDIC 037 standard collating sequence
      **
      **         This program shows how to create a database with EBCDIC
      **         037 standard collating sequence.
      **         
      **         A user-defined collating sequence allows the user to specify
      **         the collating behaviour of the database. This can be used by
      **         applications that require compatibility to the collating
      **         behaviour of host database products. For example, simulating
      **         the collating behaviour, in a DB2/MVS CCSID 500 (EBCDIC
      **         International) database, in a DB2/CS codepage 819
      **         (ISO Latin/1) database, can be achived by specifying
      **         a collating sequence that maps codepage 819 characters
      **         to CCSID 500 characters when the database is created.
      **
      ** DB2 APIs USED:
      **         sqlgcrea -- CREATE DATABASE
      **         sqlgdrpd -- DROP DATABASE
      **
      ** OUTPUT FILE: ebcdicdb.out (available in the online documentation)
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
       Program-Id. "ebcdicdb".

       Data Division.
       Working-Storage Section.

      *--> sqlb0x67.cobol
       copy "sqle850b.cbl".
      * Definition of the collating sequence
       copy "sqlutil.cbl".
       copy "sqlenv.cbl".
       copy "sqlca.cbl".
      *<--

      * Local Variables

       77 rc                  pic s9(9) comp-5.
       77 errloc              pic x(80).

      *-->
      * Variables for Create/Drop database
       77 DBNAME              pic x(10)  value "dbebcdic".
       77 DBNAME-LEN          pic s9(4) comp-5 value 8.
       77 ALIAS               pic x(10)  value "dbebcdic".
       77 ALIAS-LEN           pic s9(4) comp-5 value 8.
       77 PATH                pic x(255).
       77 PATH-LEN            pic s9(4) comp-5 value 0.
       77 reserved1           pic 9(4)  comp-5 value 0.
       77 reserved2           pic s9(4) comp-5 value 0.

      *<--

       Procedure Division.
       ebcdicdb-pgm section.

           display "Sample COBOL Program : EBCDICDB.CBL".

      * setup database description block SQLEDBDESC
           move SQLE-DBDESC-2  to SQLDBDID.
           move 0              to SQLDBCCP.
           move SQL-CS-USER    to SQLDBCSS.
           move SQLE-850-037   to SQLDBUDC.
           move "EBCDIC"       to SQLDBCMT.
           move 0              to SQLDBSGP.
           move 10             to SQLDBNSG.
           move -1             to SQLTSEXT.

           SET SQLCATTS        TO NULLS.
           SET SQLUSRTS        TO NULLS.
           SET SQLTMPTS        TO NULLS.

      * setup database country information
      * structure SQLEDBCOUNTRYINFO
           move "IBM-850" to SQLDBCODESET of SQLEDBCOUNTRYINFO.
           move "En_US"   to SQLDBLOCALE of SQLEDBCOUNTRYINFO.

           display "CREATing the temporary database DBEBCDIC ...".
           display "please wait... this will take a while ...".

      *-->
      ******************************
      * CREATE DATABASE API called *
      ******************************
           call "sqlgcrea" using
                                 by value     PATH-LEN
                                 by value     ALIAS-LEN
                                 by value     DBNAME-LEN
                                 by reference sqlca
                                 by value     0
                                 by value     0
                                 by reference SQLEDBCOUNTRYINFO
                                 by reference SQLEDBDESC
                                 by reference PATH
                                 by reference ALIAS
                                 by reference DBNAME
                           returning rc.
      *<--

           move "creating the database" to errloc.
           call "checkerr" using SQLCA errloc.

           display "Database DBEBCDIC with a user-defined".
           display "collating sequence created successfully".

           display "DROPping the database DBEBCDIC".
      *-->
      ****************************
      * DROP DATABASE API called *
      ****************************
           call "sqlgdrpd" using
                                 by value     reserved1
                                 by value     DBNAME-LEN
                                 by reference sqlca
                                 by value     reserved2
                                 by reference DBNAME
                           returning rc.
      *<--

           move "dropping the database" to errloc.
           call "checkerr" using SQLCA errloc.

       end-ebcdicdb. stop run.
