#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2002.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_prep.cmd
#*
#* SAMPLE: Getting started with administration tasks
#* 
#*         This samples shows how to bind the database with XML Extender 
#*         stored procedures and how to enable database with XML
#*         Extender.
#***************************************************************************** 

db2 "connect to SALES_DB"

db2 "bind /opt/IBM/db2/V9.1/bnd/@dxxbind.lst"

db2 "terminate"

dxxadm enable_db SALES_DB
