#************************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2004.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#************************************************************************************
#* SOURCE FILE NAME: JDBCRetrieveXMLC.cmd
#*
#* SAMPLE: Script that calls RetrieveC Java program which executes dxxRetrieveXMLClob stored procedure
#*         
#* ATTENTION:
#* Before proceeding:
#*    1.  Set the following DB2 registry variables to insure that the XML Extender
#*        UDFs execute properly:
#*           DB2_DXX_PATHS_ALLOWED_READ
#*           DB2_DXX_PATHS_ALLOWED_WRITE
#*    2.  Bind the database mydb with the XML Extender package
#*
#*************************************************************************************

dxxadm enable_db mydb

db2  connect to mydb

db2 "insert into db2xml.dtd_ref values('neworder.dtd', db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/dtd/neworder.dtd'), 0, 'anita', 'anita','anita')"

#  create collection "abc"  with validation check
dxxadm enable_collection mydb abc /opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/neworder.dad 

#  insert data to tables
db2 "insert into order_tab values(1, 'General Motor', 'parts@gm.com')"
db2 "insert into part_tab values('red',  156, 1795.4, 0.02, 17, 1)"
db2 "insert into part_tab values('black', 68, 3485.16, 0.06, 36, 1)"
db2 "insert into part_tab values('red',  128, 3800.00, 0.07, 28, 1)"
db2 "insert into ship_tab values('1998-03-13', 'TRUCK', 'This is the first shipment to service of GM.', 156)"
db2 "insert into ship_tab values('1999-01-16', 'FEDEX', 'This the second shipment to service of GM.', 156)"
db2 "insert into ship_tab values('1998-08-19', 'BOAT', 'This shipment is requested by a call. from GM marketing.', 68)"
db2 "insert into ship_tab values('1998-07-23', 'AIR', 'This shipment is ordered by an email.', 68)"
db2 "insert into ship_tab values('1998-12-30', 'TRUCK', NULL, 128)"

#  retrieve collection "abc"
# If you are running a 32-bit instance, uncomment the following line.
# java RetrieveC mydb abc
# And comment the following line.
java -d64 RetrieveC mydb abc

# cleanup
db2 drop table order_tab
db2 drop table part_tab
db2 drop table ship_tab

dxxadm disable_collection mydb abc
db2 "delete from db2xml.dtd_ref where dtdid='neworder.dtd'"

dxxadm disable_db mydb

db2 terminate

