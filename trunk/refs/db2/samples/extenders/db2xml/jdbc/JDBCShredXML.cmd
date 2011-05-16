#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: JDBCShredXML.cmd
#*
#* SAMPLE: Testing calling dxxShredXML from JDBC
#*         
#*         Test dxxShredXML for composite primary and foreign keys for 
#*         existing tables.
#*         
#*         Notice:
#*          1. make sure that mydb database is binded with XML Extender and CLI 
#*          2. see Shred.java for the way to call dxxShredXML() from JDBC
#*          3. enter:
#*             "javac Shred.java" to generate Generate.class
#* 
#* 
#***************************************************************************** 

dxxadm enable_db mydb

db2 "connect to mydb"

db2 "echo -------- Setting up the database mydb. --------"
db2 "create table order_tab(order_key1 integer, order_key2 integer, order_key3 integer, customer_name varchar(16), customer_email varchar(16))"

db2 "create table part_tab(part_key1 integer, part_key2 integer, color char(6), qty integer, price decimal(10,2), tax real, o_key1 integer, o_key2 integer, o_key3 integer)"

db2 "create table ship_tab(date date, mode char(6), comment varchar(128), p_key1 integer, p_key2 integer)"

db2 "echo -------- Calling the dxxShredXML stored procedure. --------"
# If you are running a 32-bit instance, uncomment the following line.
# java Shred mydb /opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/neworder2.dad /opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/neworder2.xml
# And comment the following line.
java -d64 Shred mydb /opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/neworder2.dad /opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/neworder2.xml

db2 "echo -------- Displaying the result of the decomposition. --------"
db2 "select * from order_tab"
db2 "select * from part_tab"
db2 "select * from ship_tab"

db2 "echo -------- Cleaning up the database mydb. --------"
db2 "drop table order_tab"
db2 "drop table part_tab"
db2 "drop table ship_tab"

dxxadm disable_db mydb

db2 "terminate"
