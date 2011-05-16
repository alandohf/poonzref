#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_createTabCol.cmd
#*
#* SAMPLE: Creates the SALES_TAB table for XML column
#***************************************************************************** 

db2 "connect to SALES_DB"

db2 "create table sales_tab(invoice_num char(6) not null primary key, sales_person varchar(20))"

db2 "terminate"

