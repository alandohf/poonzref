#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2004.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_insertDTD.cmd
#*
#* SAMPLE: Inserts the DTD into db2xml.dtd_ref table of the SALES_DB database
#*
#* ATTENTION:
#* Before proceeding, you must set the following DB2 registry variables
#* for some of the XML Extender UDFs to execute properly:
#*    DB2_DXX_PATHS_ALLOWED_READ
#*    DB2_DXX_PATHS_ALLOWED_WRITE
#*
#***************************************************************************** 

db2 "connect to SALES_DB"

db2 "echo ----- Inserting the DTD into db2xml.dtd_ref table of SALES_DB  "
db2 "insert into db2xml.dtd_ref values('getstart.dtd', db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/dtd/getstart.dtd'), 0, 'user1', 'user1', 'user1')"

db2 "terminate"

