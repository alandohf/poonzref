-- Sample script to demonstrate the use of XML Extender extract UDFs
--   Dependency: book1.xml
--   Usage: db2 -tf extract3.clp


connect to mydb;

echo -------- Use of wildcard (*) as element tag  --------;

echo Chapter IDs should show up.;
echo location path = '/book/*/@id';
echo The result should be (1, 2).;
select * from table(db2xml.extractIntegers(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book1.xml'), '/book/*/@id')) as x;

echo Section IDs should show up.;
echo location path = '/*/*/*/@id';
echo The result should be (3, 4).;
select * from table(db2xml.extractIntegers(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book1.xml'), '/*/*/*/@id')) as x;

echo All IDs should show up: both chapter and section IDs.;
echo location path = '//*/@id';
echo The result should be (1, 3, 2, 4).;
select * from table(db2xml.extractIntegers(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book1.xml'), '//*/@id')) as x;

echo All dates should show up.;
echo location path = '//*/@date';
echo The result should be (07/01/1997, 01/02/1997, 12/22/1998).;

select * from table(db2xml.extractDates(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book1.xml'), '//*/@date')) as x;

echo -------- Use of wildcard (*) as attribute tag  --------;
echo location path = '//*/@*';
echo The result is all the attributes in the document.;
select cast(returnedVarchar as varchar(28)) as attribute from table(db2xml.extractVarchars(db2xml.XMLFile('/opt/IBM/db2/V9.1/samples/extenders/db2xml/xml/book1.xml'), '//*/@*')) as x;
