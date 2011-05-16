#*****************************************************************************
#* Licensed Materials - Property of IBM
#*
#* (C) COPYRIGHT International Business Machines Corp. 2001 - 2004.
#* All Rights Reserved.
#*
#* US Government Users Restricted Rights - Use, duplication or
#* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#***************************************************************************** 
#* SOURCE FILE NAME: xcolumn2.cmd
#*
#* SAMPLE: Sample of XML Extender administration function enable column
#*         
#*         DAD: litem.dad
#*
#*         1. enable column 
#*         2. insert 3 xml document into XML enabled column (XMLCLOBFromFile)
#*         3. sample query of XML documents in XML enabled column
#*         4. sample update of XML enabled column, show that side table is
#*            updated accordingly
#*         5. sample delete from XML enabled column, show that side table is
#*            updated accordingly
#*
#* ATTENTION:
#* Before proceeding, you must set the following DB2 registry variables
#* for some of the XML Extender UDFs to execute properly:
#*    DB2_DXX_PATHS_ALLOWED_READ
#*    DB2_DXX_PATHS_ALLOWED_WRITE
#*
#*****************************************************************************

db2 "connect to mydb"

db2 "create table app1 (id int NOT NULL primary key, name char(20), Order db2xml.xmlclob not logged)"

db2 "insert into db2xml.dtd_ref values('litem_dtd', db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/dtd/LineItem.dtd'), 0, 'anita', 'anita','anita')"

# make sure your current running path is right.
dxxadm enable_column mydb app1 Order "/opt/IBM/db2/V9.1/samples/extenders/db2xml/dad/litem.dad" -r id

# create index on the discount column in subtable discount
db2 "create index discount_idx on discount(discount)"

# insert 3 xml documents
db2 "insert into app1 (id, name, Order) values(11, 'order1', db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/litem1.xml'))"

db2 "insert into app1 (id, name, Order) values(22, 'order2', db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/litem2.xml'))"

db2 "insert into app1 (id, name, Order) values(33, 'order3', db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/litem3.xml'))"

db2 "select * from part_key order by id, dxx_seqno asc"

# get a discount element which is > 0.05
db2 "select returneddouble from app1 a, table(db2xml.extractDoubles(a.Order, '/Order/Part/Discount')) as x where returneddouble > 0.05"

# replace litem3.xml with litem5.xml
db2 "update app1 set Order = db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/litem5.xml') where id=33"

db2 "select * from part_key order by id, dxx_seqno asc"

db2 "select returneddouble from app1 a, table(db2xml.extractDoubles(a.Order, '/Order/Part/Discount')) as x where returneddouble > 0.05"

# delete litem1.xml 
db2 "delete from app1 where name='order1'"

db2 "select * from part_key order by id, dxx_seqno asc"

db2 "select returneddouble from app1 a, table(db2xml.extractDoubles(a.Order, '/Order/Part/Discount')) as x where returneddouble > 0.05"

#cleanup
dxxadm disable_column mydb app1 Order

db2 drop table app1

db2 "delete from db2xml.dtd_ref where dtdid='litem_dtd'"

db2 terminate

