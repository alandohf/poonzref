#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_queryCol.cmd
#*
#* SAMPLE: Searches the SALES_DB database XML Column 
#*          
#*         This sample shows how to search the SALES_DB database XML Column
#*         for orders with a price over $2500
#***************************************************************************** 

db2 "connect to SALES_DB"

db2 "echo ---------- Querying SALES_DB XML documents.... "

db2 "select distinct sales_person from sales_tab S, part_side_tab P where price > 2500.00 and S.invoice_num = P.invoice_num"

db2 "terminate"

