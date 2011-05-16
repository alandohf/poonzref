-- Sample script to demonstrate the use of XML Extender update UDFs
--   Usage: db2 -tf update.clp

-- ATTENTION:
-- Before proceeding, you must set the following DB2 registry variables
-- for some of the XML Extender UDFs to execute properly:
--    DB2_DXX_PATHS_ALLOWED_READ
--    DB2_DXX_PATHS_ALLOWED_WRITE

connect to mydb;

echo ------- Simple update XMLVarchar '/book/price' --> '60.02' -------;
values cast(db2xml.update(db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price', '60.02') as varchar(500));

echo ------- Large update XMLVarchar '//chapter[@id="2"]/@id' --> '888...' -------;
values cast(db2xml.update(db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '//chapter[@id="2"]/@id', '8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888') as varchar(600));

echo ------- Simple update XMLClob '/book/price' --> '60.02' -------;
values cast(cast(db2xml.update(db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price', '60.02') as clob(1k)) as varchar(500));

echo ------- Large update XMLClob '//chapter[@id="2"]/@id' --> '888...' -------;
values cast(cast(db2xml.update(db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '//chapter[@id="2"]/@id', '8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888') as clob(1k)) as varchar(600));

connect reset;
terminate;
