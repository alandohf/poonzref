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
-- SOURCE FILE NAME: impexpxml.db2
--
-- SAMPLE: How to use IMPORT and EXPORT with new options for XML data
--
-- PREREQUISITES:
--         1. Copy xmldata.del to the Present Working Directory (PWD) 
--         2. Create a directory "xmldatadir" in PWD and copy "xmlfiles.001.xml" 
--            to the "xmldatadir" directory
--
-- SQL STATEMENT USED:
--         CREATE TABLE
--         INSERT INTO
--         SELECT
--         DROP TABLE
--         IMPORT
--         EXPORT
--         TERMINATE
--
-- OUTPUT FILE: impexpxml.out (available in the online documentation)
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

-- connect to the SAMPLE database
CONNECT TO sample;

-- create a table CUSTOMER_XML with XML an column to import the data
CREATE TABLE customer_xml(Cid INT, Info XML);

-- import the data to the table using XMLVALIDATE USING XDS clause
IMPORT FROM xmldata.del OF DEL XML FROM xmldatadir 
  MODIFIED BY XMLCHAR
  XMLVALIDATE using XDS DEFAULT customer
  IGNORE (supplier) MAP((product,customer))
  INSERT INTO customer_xml;

-- select the data from the table to show that data is inserted successfully
SELECT * FROM customer_xml;

-- delete the inserted data from CUSTOMER_XML
DELETE FROM customer_xml;

-- import the data to the table using XMLVALIDATE USING SCHEMA clause
IMPORT FROM xmldata.del OF DEL XML FROM xmldatadir
  MODIFIED BY XMLCHAR 
  XMLVALIDATE using SCHEMA customer 
  INSERT INTO customer_xml;

-- Select the data from the table to show that data is inserted successfully
SELECT * FROM customer_xml;

-- Export the data back using XMLSAVESCHEMA option
EXPORT TO xmldata_exp.del OF DEL XML TO xmldatadir XMLFILE xmlfiles_exp 
  MODIFIED BY XMLCHAR XMLINSEPFILES XMLSAVESCHEMA 
  SELECT * FROM customer_xml;

-- drop the table CUSTOMER_XML
DROP TABLE customer_xml;

CONNECT RESET;

