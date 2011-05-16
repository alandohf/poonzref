#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_stp.cmd
#*
#* SAMPLE: Runs the stored procedure to compose the XML documents
#*
#*         This sample shows how to call the stored procedure to compose the 
#*         XML documents and display the result XML documents.
#*         
#*         tests2x is an executable file which is compiled from the source
#*         ../c/tests2x.sqx. 
#*         See ../c/tests2x.sqc for how to call dxxGenXML() stored procedure.
#*         Notice:
#*         1.Make sure that getstart_db has been run to create database 
#*           SALES_DB
#*         2.Make sure that getstart_prep has been run to 
#*           * bind the SALES_DB database with UDB CLI and  XML Extender 
#*             stored procedures.
#*           * enable the SALES_DB database with XML Extender by running 
#*             dxxadm enable_db SALES_DB.
#* 
#***************************************************************************** 

db2 "connect to SALES_DB"

db2 "echo -------- Calling the SQL-to-XML mapping stored procedure. --------"
dxxgenx SALES_DB /opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/getstart_xcollection.dad result_tab

db2 "echo -------- Displaying the resulting XML documents. --------"
db2 "select * from result_tab"

db2 "terminate"
