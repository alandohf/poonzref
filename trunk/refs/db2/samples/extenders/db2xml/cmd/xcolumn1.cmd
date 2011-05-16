#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2004.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: xcolumnl.cmd
#*
#* SAMPLE: Sample of XML Extender administration function enable column
#*
#*         DAD: order.dad
#* 
#*
#* ATTENTION:
#* Before proceeding, you must set the following DB2 registry variables
#* for some of the XML Extender UDFs to execute properly:
#*    DB2_DXX_PATHS_ALLOWED_READ
#*    DB2_DXX_PATHS_ALLOWED_WRITE
#*
#*****************************************************************************

db2  connect to mydb

db2 "create table app1 (id int NOT NULL, name char(20), Order db2xml.xmlclob not logged)"

db2 "insert into db2xml.dtd_ref values('order_dtd', db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/dtd/Order.dtd'), 0, 'anita', 'anita','anita')"

db2 "select * from db2xml.dtd_ref"

# make sure your current running path is right.
dxxadm enable_column mydb app1 Order "/opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/order.dad" 

dxxadm disable_column mydb app1 Order

db2 drop table app1

db2 "delete from db2xml.dtd_ref where dtdid='order_dtd'"

#dxxadm disable_db mydb

db2 terminate

