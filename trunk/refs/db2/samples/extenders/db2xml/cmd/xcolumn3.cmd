#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2004.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: xcolumn3.cmd
#*
#* SAMPLE: Sample of enable column with and without validation 
#*
#*         DAD: valid.dad and novalid.dad
#*         
#*         - Turn on validation by enabling a column with valid.dad
#*         - Attempt to insert some valid and invalid documents.
#*         - Verify that only the valid XML documents are inserted.
#*
#*         - Turn off validation by enabling a column with novalid.dad
#*         - Attempt to insert an invalid document.
#*         - Verify that the invalid document is inserted.
#*     
#* ATTENTION:
#* Before proceeding, you must set the following DB2 registry variables
#* for some of the XML Extender UDFs to execute properly:
#*    DB2_DXX_PATHS_ALLOWED_READ
#*    DB2_DXX_PATHS_ALLOWED_WRITE
#*
#*****************************************************************************

db2 "connect to mydb"

db2 "create table app1 (id int NOT NULL, name char(20), Order db2xml.xmlvarchar)"

db2 "insert into db2xml.dtd_ref values('Order.dtd', db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/dtd/Order.dtd'), 0, 'anita', 'anita', 'anita')"

echo -------- Enable XML column with validation --------

dxxadm enable_column mydb app1 Order "/opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/valid.dad"

db2 "insert into app1 (id, name, Order) values(11, 'order1', db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/order1.xml'))"

db2 "insert into app1 (id, name, Order) values(111, 'invalid1', db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/invalid1.xml'))"

db2 "insert into app1 (id, name, Order) values(22, 'order2', db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/order2.xml'))"

db2 "insert into app1 (id, name, Order) values(122, 'invalid2', db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/invalid2.xml'))"

db2 "insert into app1 (id, name, Order) values(133, 'invalid3', db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/invalid3.xml'))"

db2 "select customer_num,price,date from order"

db2 "update app1 set Order = db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/invalid1.xml') where id=11"

db2 "select customer_num,price,date from order"

dxxadm disable_column mydb app1 Order

db2 "delete from app1"

echo -------- Enable XML column with no validation --------

dxxadm enable_column mydb app1 Order "/opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/novalid.dad"

db2 "insert into app1 (id, name, Order) values(111, 'invalid1', db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/invalid1.xml'))"

db2 "select customer_num,price,date from order"

dxxadm disable_column mydb app1 Order

echo -------- Clean up --------

db2 "drop table app1"

db2 "delete from db2xml.dtd_ref where dtdid='Order.dtd'"

db2 terminate

