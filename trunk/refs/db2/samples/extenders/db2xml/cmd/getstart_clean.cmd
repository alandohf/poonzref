#****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_clean.cmd
#*
#* SAMPLE: Cleans up database after doing the Getting Started tutorial
#***************************************************************************** 

db2 "connect to SALES_DB"

echo --- Cleaning up ......

db2 "drop table order_tab"

db2 "drop table part_tab"

db2 "drop table ship_tab"

db2 "drop table result_tab"

dxxadm disable_column sales_db sales_tab order

db2 "delete from db2xml.dtd_ref where dtdid='getstart.dtd'"

db2 "drop table sales_tab"

db2 "terminate"
