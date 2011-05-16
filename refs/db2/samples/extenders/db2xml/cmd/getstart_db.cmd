#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_db.cmd
#*
#* SAMPLE: Creates and populates a database
#***************************************************************************** 

db2 "create database SALES_DB"

db2 "connect to SALES_DB"

db2 "echo -------- Setting up the database SALES_DB --------"

db2 "create table order_tab(order_key integer, customer_name varchar(16), customer_email varchar(16), customer_phone varchar(16))"

db2 "create table part_tab(part_key integer, color char(6), quantity integer, price decimal(10,2), tax real, order_key integer)"

db2 "create table ship_tab(date date, mode char(6), comment varchar(64), part_key integer)"

db2 "create table result_tab(doc varchar(2000))"

db2 "insert into order_tab values(1, 'American Motors', 'parts@am.com', '800-AM-PARTS')"

db2 "insert into part_tab values(156, 'red', 17, 17954.55, 0.02, 1)"
db2 "insert into part_tab values(68, 'black', 36, 34850.16, 0.06, 1)"
db2 "insert into part_tab values(128, 'red', 28, 38000.00, 0.07, 1)"

db2 "insert into ship_tab values('1998-03-13', 'TRUCK', 'This is the first shipment to service of AM.', 156)"
db2 "insert into ship_tab values('1999-01-16', 'FEDEX', 'This the second shipment to service of AM.', 156)"
db2 "insert into ship_tab values('1998-08-19', 'BOAT', 'This shipment is requested by a call. from AM marketing.', 68)"
db2 "insert into ship_tab values('1998-08-19', 'AIR', 'This shipment is ordered by an email.', 68)"
db2 "insert into ship_tab values('1998-12-30', 'TRUCK', NULL, 128)"


db2 "terminate"
