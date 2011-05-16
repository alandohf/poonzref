-- Sample script to demonstrate the use of XML Extender extract UDFs
--   Usage: db2 -tf extract2.clp

-- ATTENTION:
-- Before proceeding, you must set the following DB2 registry variables
-- for some of the XML Extender UDFs to execute properly:
--    DB2_DXX_PATHS_ALLOWED_READ
--    DB2_DXX_PATHS_ALLOWED_WRITE


connect to mydb;
-- UDF extractChar returns a scalar.
values cast(db2xml.extractChar(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price') as char(254));

values cast(db2xml.extractChar(db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price') as char(254));

values cast(db2xml.extractChar(db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price') as char(254));

-- UDF extractChars returns a single-column table.
select cast(returnedchar as char(254)) from table(db2xml.extractChars(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/chapter/@id')) as x;

select cast(returnedchar as char(254)) from table(db2xml.extractChars(db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/chapter/@id')) as x;


select cast(returnedchar as char(254)) from table(db2xml.extractChars(db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/chapter/@id')) as x;

values cast(db2xml.extractSmallint(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price') as smallint);

values cast(db2xml.extractSmallint(db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price') as smallint);

values cast(db2xml.extractSmallint(db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price') as smallint);

select cast(returnedSmallint as smallint) from table(db2xml.extractSmallints(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/chapter/@id')) as x;

select cast(returnedSmallint as smallint) from table(db2xml.extractSmallints(db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/chapter/@id')) as x;


select cast(returnedSmallint as smallint) from table(db2xml.extractSmallints(db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/chapter/@id')) as x;

values (db2xml.extractReal(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price'));

values (db2xml.extractReal(db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price'));

values (db2xml.extractReal(db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price'));

select cast(returnedReal as real) from table(db2xml.extractReals(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/chapter/@id')) as x;

select cast(returnedReal as real) from table(db2xml.extractReals(db2xml.XMLClobFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/chapter/@id')) as x;


select cast(returnedReal as real) from table(db2xml.extractReals(db2xml.XMLVarcharFromFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/chapter/@id')) as x;


connect reset;
terminate;

