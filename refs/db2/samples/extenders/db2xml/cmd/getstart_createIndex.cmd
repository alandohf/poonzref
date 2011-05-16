#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_createIndex.cmd
#*
#* SAMPLE: Creates the indexes on the side tables for faster searching
#***************************************************************************** 

db2 "connect to SALES_DB"

echo --- Creating an index on the ORDER_KEY column in the side table ORDER_SIDE_TAB
db2 "create index key_idx on order_side_tab(order_key)"

echo --- Creating an index on the CUSTOMER column in the side table ORDER_SIDE_TAB
db2 "create index customer_idx on order_side_tab(customer)"

echo --- Creating an index on the PRICE column in the side table PART_SIDE_TAB
db2 "create index price_idx on part_side_tab(price)"

echo --- Creating an index on the DATE column in the side table SHIP_SIDE_TAB
db2 "create index date_idx on ship_side_tab(date)"

db2 "terminate"

