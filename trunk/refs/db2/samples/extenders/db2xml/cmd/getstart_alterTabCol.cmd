#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_alterTabCol.cmd
#*
#* SAMPLE: Adds the XML column to the SALES_TAB
#*  
#*         This sample shows how to alter the table by adding the column that
#*         will be enabled for XML. 
#***************************************************************************** 

db2 "connect to SALES_DB"

db2 "alter table sales_tab add order db2xml.xmlvarchar"

db2 "terminate"

