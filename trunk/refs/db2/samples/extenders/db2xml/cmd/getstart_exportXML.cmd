#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_exportXML.cmd
#*
#* SAMPLE: Exports the contents of the result table as an XML document
#*
#*         This sample shows how to export the XML document from the table to 
#*         a file, assuming you have write permission for /tmp directory.
#*    
#*         For Windows users, you might need to create the /tmp directory or
#*         modify the select statement to '/temp/getstart.xml'.
#***************************************************************************** 

db2 "connect to SALES_DB"

db2 "echo ----- Exporting the XML document "
db2 "select db2xml.Content(db2xml.xmlvarchar(doc), '/tmp/getstart.xml') from result_tab"

db2 "terminate"

