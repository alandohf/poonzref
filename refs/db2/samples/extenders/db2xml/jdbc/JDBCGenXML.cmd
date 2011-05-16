#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: JDBCGenXML.cmd
#*
#* SAMPLE: Test calling dxxGenXML stored procedure from JDBC
#*         
#*         Notice:
#*          1. make sure that database sample is created via db2sampl 
#*          2. make sure that sample database is binded with XML Extender and CLI 
#*          3. see Generate.java for the way to call dxxGenXML() from JDBC
#*          4. enter:
#*             "javac Generate.java" to generate Generate.class
#* 
#***************************************************************************** 

dxxadm enable_db sample

db2 "connect to sample"

db2 "echo -------- Creating result_tab --------"
db2 "create table result_tab(doc varchar(3000))"

db2 "echo -------- Calling the SQL-to-XML mapping stored procedure --------"
# If you are running a 32-bit instance, uncomment the following line.
# java Generate sample /opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/department.dad result_tab
# And comment the following line.
java -d64 Generate sample /opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/department.dad result_tab

db2 "echo -------- Displaying the resulting XML documents --------"
db2 "select * from result_tab"

db2 "echo -------- Cleaning up --------"
db2 "drop table result_tab"

dxxadm disable_db sample

db2 "terminate"
