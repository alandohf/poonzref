#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: genxml_rdb.cmd
#*
#* SAMPLE: Testing RDB-node XML retrieval stored procedure
#* 
#***************************************************************************** 

db2 "connect to mydb"

db2 "echo -------- Setting up the database mydb --------"

db2 "create table order_tab(order_key varchar(4), customer_name varchar(16), customer_email varchar(16), customer_phone varchar(16))"

db2 "create table part_tab(part_key integer, color char(6), qty integer, price decimal(10,2), tax real, order_key varchar(4))"

db2 "create table ship_tab(date date, mode char(6), comment varchar(128), part_key integer)"

db2 "create table result_tab(doc varchar(2000))"

db2 "insert into order_tab values('1', 'American Motors', 'parts@am.com', '800-AM-PARTS')"

db2 "insert into part_tab values(156, 'red', 17, 17954.55, 0.02, '1')"
db2 "insert into part_tab values(68, 'black', 36, 34850.16, 0.06, '1')"
db2 "insert into part_tab values(128, 'red', 28, 38000.00, 0.07, '1')"

db2 "insert into ship_tab values('1998-03-13', 'TRUCK', 'This is the first shipment to service of AM.', 156)"
db2 "insert into ship_tab values('1999-01-16', 'FEDEX', 'This the second shipment to service of AM.', 156)"
db2 "insert into ship_tab values('1998-08-19', 'BOAT', 'This shipment is requested by a call. from AM marketing.', 68)"
db2 "insert into ship_tab values('1998-08-19', 'AIR', 'This shipment is ordered by an email.', 68)"
db2 "insert into ship_tab values('1998-12-30', 'TRUCK', NULL, 128)"

db2 "echo -------- Calling the RDB-node XML retrieval stored procedure --------"
dxxgenx mydb /opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/order_rdb.dad result_tab

db2 "echo -------- Displaying the resulting XML documents --------"
db2 "select * from result_tab"

db2 "echo -------- Cleaning up the database mydb --------"

db2 "connect to mydb"
db2 "drop table order_tab"
db2 "drop table part_tab"
db2 "drop table ship_tab"
db2 "drop table result_tab"

db2 "terminate"
