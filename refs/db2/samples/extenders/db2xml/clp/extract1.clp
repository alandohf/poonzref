-- Sample script to demonstrate the use of XML Extender extract UDFs
--   Usage: db2 -tf extract1.clp

connect to mydb;

echo -------- location path syntax of the form /tag1/tag2/..../tagn --------;
values cast (db2xml.extractDouble(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price') as decimal(6,2));

select cast(x.returnedVarchar as char(35)) from table(db2xml.extractVarchars(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/chapter/section')) as x;

echo -------- location path syntax of the form /tag1/tag2/@attr1 --------;
values db2xml.extractDate(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/price/@date');

select * from table(db2xml.extractIntegers(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book.xml'), '/book/chapter/@id')) as x;

connect reset;
terminate;

