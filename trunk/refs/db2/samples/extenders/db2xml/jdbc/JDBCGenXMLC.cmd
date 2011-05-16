#************************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#************************************************************************************
#* SOURCE FILE NAME: JDBCGenXMLC.cmd
#*
#* SAMPLE: Testing calling dxxGenXMLClob stored procedure from JDBC
#*         
#*          Notice:
#*            1. make sure that database sample is created via db2sampl 
#*            2. make sure that sample database is binded with XML Extender and CLI 
#*            3. see GenerateC.java for the way to call dxxGenXMLClob() from JDBC
#*            4. enter:
#*               "javac GenerateC.java" to generate GenerateC.class
#* 
#*************************************************************************************

dxxadm enable_db sample

db2 "echo -------- Calling the SQL-to-XML mapping stored procedure --------"
# If you are running a 32-bit instance, uncomment the following line.
# java GenerateC sample /opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/department.dad
# And comment the following line.
java -d64 GenerateC sample /opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/department.dad

dxxadm disable_db sample

db2 "terminate"
