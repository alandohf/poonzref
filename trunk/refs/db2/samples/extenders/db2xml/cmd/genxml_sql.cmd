#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2004.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: genxml_sql.cmd
#*
#* SAMPLE: Test SQL-to-XML mapping stored procedure 
#*         
#*         Result column type: varchar
#*         Database: sample
#*
#* ATTENTION:
#* Before proceeding:
#*    1.  Set the following DB2 registry variables to insure that the XML Extender
#*        UDFs execute properly:
#*           DB2_DXX_PATHS_ALLOWED_READ
#*           DB2_DXX_PATHS_ALLOWED_WRITE
#*    2.  Bind the database mydb with the XML Extender package
#*
#***************************************************************************** 

db2 "connect to mydb"

db2 "insert into db2xml.dtd_ref values('getstart.dtd', db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/dtd/getstart.dtd'), 0, 'user', 'user','user')"

db2 "echo -------- Setting up the database mydb. --------"

db2 "create table order_tab(order_key integer, customer_name varchar(16), customer_email varchar(16), customer_phone varchar(16))"

db2 "create table part_tab(part_key integer, color char(6), qty integer, price decimal(10,2), tax real, order_key integer)"

db2 "create table ship_tab(date date, mode char(6), comment varchar(128), part_key integer)"

db2 "create table result_tab(doc varchar(3000))"

db2 "insert into order_tab values(1, 'General Motor', 'parts@gm.com', '800-GM-PARTS')"

db2 "insert into part_tab values(156, 'red', 17, 17954.55, 0.02, 1)"
db2 "insert into part_tab values(68, 'black', 36, 34850.16, 0.06, 1)"
db2 "insert into part_tab values(128, 'red', 28, 38000.00, 0.07, 1)"

db2 "insert into ship_tab values('1998-03-13', 'TRUCK', 'This is the first shipment to service of GM.', 156)"
db2 "insert into ship_tab values('1999-01-16', 'FEDEX', 'This the second shipment to service of GM.', 156)"
db2 "insert into ship_tab values('1998-08-19', 'BOAT', 'This shipment is requested by a call. from GM marketing.', 68)"
db2 "insert into ship_tab values('1998-08-19', 'AIR', 'This shipment is ordered by an email.', 68)"
db2 "insert into ship_tab values('1998-12-30', 'TRUCK', NULL, 128)"

db2 "echo -------- Calling the SQL-to-XML mapping stored procedure --------"
dxxgenx mydb /opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/order_sql.dad result_tab

db2 "echo -------- Displaying the composed XML documents --------"
db2 "select * from result_tab"

db2 "echo -------- Cleaning up --------"
db2 "drop table result_tab"
db2 "drop table order_tab"
db2 "drop table part_tab"
db2 "drop table ship_tab"

db2 "delete from db2xml.dtd_ref where dtdid='getstart.dtd'"

db2 "terminate"
