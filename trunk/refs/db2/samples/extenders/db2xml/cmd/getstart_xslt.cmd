#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2004.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: getstart_xslt.cmd
#*
#* SAMPLE: Transform an XML document into an HTML document
#* 
#* ATTENTION:
#* Before proceeding, you must set the following DB2 registry variables
#* for some of the XML Extender UDFs to execute properly:
#*    DB2_DXX_PATHS_ALLOWED_READ
#*    DB2_DXX_PATHS_ALLOWED_WRITE
#*
#***************************************************************************** 

db2 "connect to SALES_DB"
db2 "create table xslt_tab(doc varchar(2000))"
db2 "insert into xslt_tab (doc) values ( DB2XML.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/getstart.xml'))"

db2 "echo ----- Transform XML document into HTML document -----"
db2 "select DB2XML.XSLTransformToFile( CAST(doc AS CLOB(4k)), '/opt/IBM/db2/V9.1/samples/extenders/db2xml/xslt/getstart.xsl', 0, '/tmp/getstart.html') from xslt_tab"
db2 "drop table xslt_tab"
db2 "terminate"



