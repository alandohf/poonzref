#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2004.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_insertXML.cmd
#*
#* SAMPLE: Inserts an XML document into the XML column of the sales_tab table
#*
#* ATTENTION:
#* Before proceeding, you must set the following DB2 registry variables
#* for some of the XML Extender UDFs to execute properly:
#*    DB2_DXX_PATHS_ALLOWED_READ
#*    DB2_DXX_PATHS_ALLOWED_WRITE
#*
#***************************************************************************** 

db2 "connect to SALES_DB"

db2 "echo ----- Inserting the XML document into sales_tab "
db2 "insert into sales_tab(invoice_num, sales_person, order) values('123456', 'Sriram Srinivasan', db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/getstart.xml'))"

db2 "terminate"

