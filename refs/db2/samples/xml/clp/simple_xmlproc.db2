-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
--
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
--
-- (C) COPYRIGHT International Business Machines Corporation 2006
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: simple_xmlproc.db2
--
-- SAMPLE: How to use XML type parameters in a SQL stored procedure.
--
-- DESCRIPTION:
--         This procedure will take Customer Information ( of type XML) as input ,
--         finds whether the customer with Cid in Customer Information exists in the
--         customer table , if not this will insert the customer info with that cid
--         into the customer table, and find out all the customers from the same city
--         of this customer and returns to the caller in XML format.  
--
-- SQL STATEMENTS USED:
--         CREATE PROCEDURE
--         DROP PROCEDURE
--         PREPARE
--         OPEN
--         FETCH
--         INSERT
--         SELECT
--
-- To run this script from the CLP,issue the command 
--                                          "db2 -td@ -vf simple_xmlproc.db2"
-----------------------------------------------------------------------------
--
-- For more information about the command line processor (CLP) scripts,
-- see the README file.
--
-- For information on using SQL statements, see the SQL Reference.
--
-- For the latest information on programming, building, and running DB2
-- applications, visit the DB2 application development website:
--     http://www.software.ibm.com/data/db2/udb/ad
-----------------------------------------------------------------------------

-- connect to the database
CONNECT TO sample@

-- drop the procedure Simple_XML_Proc_SQL if exists
DROP PROCEDURE Simple_XML_Proc_SQL@

-- create the procedure Simple_XML_Proc_SQL with XML type parameters.
CREATE PROCEDURE Simple_XML_Proc_SQL(IN inXML XML, OUT Location XML)
SPECIFIC Simple_XML_Proc_SQL
LANGUAGE SQL
BEGIN
    DECLARE SQLCODE INTEGER;
    DECLARE CustInfo XML;
    DECLARE count INTEGER DEFAULT 0;
    DECLARE city VARCHAR(100);
    DECLARE custid BIGINT;
    DECLARE stmt_text VARCHAR (1024);
    DECLARE stmt STATEMENT;
    DECLARE cur1 CURSOR WITH RETURN FOR stmt;

-- set the parameter inXML to CustInfo 
   SET CustInfo = inXML;

-- use XML function XMLEXISTS to  verify whether customer with
-- Cid exists or not ....
   SELECT COUNT(*) INTO count FROM customer WHERE 
                   XMLEXISTS('$info/customerinfo[@Cid=$id]' PASSING CustInfo AS "info", cid as "id");   

-- if doesn't exists insert into customer table with that customer id
   IF (count < 1)
   THEN
       SELECT XMLCAST( XMLQUERY('$info/customerinfo/@Cid' passing CustInfo as "info") as BIGINT) INTO 
                       custid FROM SYSIBM.SYSDUMMY1;
       INSERT INTO customer(Cid, Info) VALUES(custid, CustInfo);
   END IF;

-- get the city of the customer into an application variable
-- using XMLQUERY 
   SET city = XMLCAST(XMLQUERY('$info/customerinfo//city' passing CustInfo as "info") as VARCHAR(100));

-- get location of the customer
   SET Location = XMLQUERY('let $city := $info/customerinfo//city, 
                                $prov := $info/customerinfo//prov-state 
                            return <Location>{$city, $prov}</Location>' 
                            passing CustInfo as "info");

-- find out all the customers from that location
   SET stmt_text = 'XQUERY for $cust in 
                      db2-fn:xmlcolumn("CUSTOMER.INFO")/customerinfo/addr[city= "' || city ||'"] 
                    return <Customer>{$cust/../@Cid}{$cust/../name}</Customer>';
   PREPARE stmt FROM stmt_text;
   OPEN cur1;

-- end of the procedure 
END@

-- calling the procedure with necessary options
call Simple_XML_Proc_SQL(xmlparse(document '
                                <customerinfo Cid="5002">
                                       <name>Kathy Smith</name>
                                       <addr country="Canada">
                                             <street>25 EastCreek</street>
                                             <city>Markham</city>
                                             <prov-state>Ontario</prov-state>
                                             <pcode-zip>N9C-3T6</pcode-zip>
                                       </addr>
                                       <phone type="work">905-566-7258</phone>
                                </customerinfo>' PRESERVE WHITESPACE),?)@

-- rollback the work to keep database consistent
ROLLBACK@

CONNECT RESET@

