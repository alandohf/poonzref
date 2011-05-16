----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
-- Governed under the terms of the IBM Public License
--
-- (C) COPYRIGHT International Business Machines Corp. 1995, 2002        
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: soapsample.sql
--    
-- SAMPLE: How to define and invoke DB2 Web Service functions.
--
-- SQL STATEMENTS USED:
--         CREATE FUNCTION
--         VALUES
--         SELECT
--
-- For more information about the command line processor (CLP) scripts, 
-- see the README file.
--
-- For more information about SQL, see the "SQL Reference".
--
-- For the latest information on programming, compiling, and running DB2 
-- applications, refer to the DB2 application development website at 
--     http://www.software.ibm.com/data/db2/udb/ad
--
-- List of Examples (for DB2 Version UDB Version 8)
-- * getTemp         - retrieve temperature in Fahrenheit
--                     (UDB Version 7 and Version 8)
-- * getRate         - returns the exchange rate between any two currencies 
-- * getTranslation  - interface to Altavista's Babelfish Translation Service
--
-- Due to the nature of these web services being changed, we cannot guarantee 
-- them working all the time. 

----------------------------------------------------------------------------

-- ***************************************************************************
--
-- getTemp: for ZIP code retrieve temperature in Fahrenheit.
--
-- ***************************************************************************

-- for DB2 UDB Version 7:

VALUES substr(DB2XML.SOAPHTTPV ('http://services.xmethods.net/soap/servlet/rpcrouter', '', 
    '<rns:getTemp xmlns:rns="urn:xmethods-Temperature"><zipcode>95120</zipcode></rns:getTemp>'), 1, 200);


-- for DB2 UDB Version 8.2 using SQL/XML: 

VALUES substr(DB2XML.SOAPHTTPV ('http://services.xmethods.net/soap/servlet/rpcrouter', '',
   XML2CLOB(
      XMLELEMENT(NAME "nrs:getTemp", 
         XMLNAMESPACES('urn:xmethods-Temperature' as "nrs", 
                       'http://schemas.xmlsoap.org/soap/encoding/' AS "SOAP-ENV_encodingStyle"),
			XMLELEMENT(NAME "zipcode", 95120)))), 1, 200);


-- Create a SOAP UDF

DROP FUNCTION gettemp;

CREATE FUNCTION GetTemp (zipcode VARCHAR(5))
    RETURNS DECIMAL (5,2)
  LANGUAGE SQL CONTAINS SQL
  EXTERNAL ACTION NOT DETERMINISTIC
  RETURN
    WITH 

--1. Perform type conversions and prepare SQL input parameters for SOAP envelope

         soap_input (in)
              AS 
           (VALUES VARCHAR(XML2CLOB(
             XMLELEMENT(NAME "ns:getTemp", 
                 XMLNAMESPACES('urn:xmethods-Temperature' as "ns"),
		 XMLELEMENT(NAME "zipcode", zipcode))))),

--2. Submit SOAP request with input parameter and receive SOAP response

         soap_output (out) 
              AS
            (VALUES DB2XML.SOAPHTTPV ('http://services.xmethods.net/soap/servlet/rpcrouter','',
                             (SELECT in FROM soap_input)))

--3. Shred SOAP response and perform type conversions to get SQL output parameters

         SELECT CAST(SUBSTR (CAST(out AS VARCHAR(3000)),
			POSSTR(CAST(out AS VARCHAR(3000)),'float">')+7,
			POSSTR(CAST(out AS VARCHAR(3000)),'</ret') - 
                                     POSSTR(CAST(out AS VARCHAR(2000)),'float">') - 7)
                AS DECIMAL(5,2))
         FROM soap_output;


DROP TABLE CITY;
CREATE TABLE CITY (zipcode VARCHAR(5), name VARCHAR(20), airport VARCHAR(3), state VARCHAR(2));
INSERT INTO CITY 
    VALUES ('95120', 'San Jose',      'SJC', 'CA'), 
           ('95030', 'Los Gatos',     'SJC', 'CA'),
           ('94102', 'San Francisco', 'SFO', 'CA'), 
           ('94609', 'Oakland',       'OAK', 'CA');


SELECT zipcode, name, CURRENT TIMESTAMP AS TIME, GetTemp(zipcode) AS current_temp
FROM city;


-- ***************************************************************************
--
-- getRate        - returns the exchange rate between any two currencies 
-- 
-- ***************************************************************************


VALUES substr(DB2XML.SOAPHTTPV ('http://services.xmethods.net:80/soap', '', 
    XML2CLOB( XMLELEMENT(NAME "ns:getRate", 
                  XMLNAMESPACES('urn:xmethods-CurrencyExchange' as "ns"), 
                XMLELEMENT(NAME "country1", 'united states'), 
                XMLELEMENT(NAME "country2", 'korea')))), 1, 160); 

-- Create SOAP UDF

DROP FUNCTION getrate;

CREATE FUNCTION GetRate (from VARCHAR(32), to VARCHAR(32))
  RETURNS VARCHAR(40)
  LANGUAGE SQL READS SQL DATA
  EXTERNAL ACTION NOT DETERMINISTIC
  RETURN
    WITH 

--1. Perform type conversions and prepare SQL input parameters for SOAP envelope
      soap_input (in)
           AS 
         (VALUES VARCHAR(XML2CLOB(
	    XMLELEMENT(NAME "ns:getRate", XMLNAMESPACES('urn:xmethods-CurrencyExchange' as "ns"),
		XMLELEMENT(NAME "country1", from),
		XMLELEMENT(NAME "country2", to))))),

--2. Submit SOAP request with input parameter and receive SOAP response

      soap_output (out) 
              AS
     (VALUES DB2XML.SOAPHTTPV('http://services.xmethods.net:80/soap','',
                (SELECT in FROM soap_input)))


--3. Shred SOAP response and perform type conversions to get SQL output parameters

    SELECT SUBSTR (out,
			POSSTR(out,'float">')+7,
			POSSTR(out,'</') - posstr(out,'float">') -7)
    FROM soap_output;


VALUES GetRate('united states', 'korea');


