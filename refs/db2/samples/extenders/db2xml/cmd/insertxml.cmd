#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2004.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: insertxml.cmd
#*
#* SAMPLE:  Sample invocation of dxxInsertXML stored procedure
#*
#* ATTENTION:
#* Before proceeding, you must set the following DB2 registry variables
#* for some of the XML Extender UDFs to execute properly:
#*    DB2_DXX_PATHS_ALLOWED_READ
#*    DB2_DXX_PATHS_ALLOWED_WRITE
#* 
#***************************************************************************** 

db2 "connect to mydb"

db2 "insert into db2xml.dtd_ref values('neworder.dtd', db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/dtd/neworder.dtd'), 0, 'anita', 'anita','anita')"

db2 "echo -------- Enabling collection abc. --------"
dxxadm enable_collection mydb abc /opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/neworder1.dad

db2 "echo -------- Calling the dxxInsertXML stored procedure. --------"
dxxisrt mydb abc /opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/neworder1.xml
db2 "select * from order_tab"
db2 "select * from part_tab"
db2 "select * from ship_tab"

db2 "echo -------- Cleaning up the database mydb. --------"
db2 drop table order_tab
db2 drop table part_tab
db2 drop table ship_tab

dxxadm disable_collection mydb abc
db2 "delete from db2xml.dtd_ref where dtdid='neworder.dtd'"

db2 terminate
