#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_enableCol.cmd
#*
#* SAMPLE: Enables the SALES_DB database for XML Column
#***************************************************************************** 

db2 "connect to SALES_DB"

db2 "echo ----- Enabling the SALES_DB for XML column data "
dxxadm enable_column  sales_db  sales_tab order  /opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/getstart_xcolumn.dad  -v sales_order_view  -r invoice_num

db2 "terminate"

