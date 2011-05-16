-- Sample script to demonstrate the use of XML Extender storage UDFs
--   Usage: db2 -tf import.clp

-- ATTENTION:
-- Before proceeding, you must set the following DB2 registry variables
-- for some of the XML Extender UDFs to execute properly:
--    DB2_DXX_PATHS_ALLOWED_READ
--    DB2_DXX_PATHS_ALLOWED_WRITE

connect to mydb;
-- UDF  returns a XMLVarchar.
values db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/order.xml');

-- UDF returns a XMLClob.
values db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/order.xml');

connect reset;
terminate;

