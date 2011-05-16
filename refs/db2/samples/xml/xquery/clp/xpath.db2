-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
--
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
--
-- (C) COPYRIGHT International Business Machines Corp. 2006
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: xpath.db2
--
-- SAMPLE: Simple XPath Queries 
--
-- SQL/XML FUNCTIONS USED
--          xmlcolumn
--          sqlquery
-- NOTE : Both the above functions are case sensitive.
--
-- XQUERY FUNCTIONS USED
--          count
--          avg
--          start-with
--          distinct-values
-- NOTE : All the xquery functions are case  sensitive

-- SAMPLE EXECUTION:
-- Run the samples with following command
--    db2 -td@ -vf xpath.db2
--
-- OUTPUT FILE: xpath.out (available in the online documentation)
-----------------------------------------------------------------------------
--
-- For more information about the command line processor (CLP) scripts,
-- see the README file.
--
-- For information on using XQUERY statements, see the XQUERY Reference.
--
-- For the latest information on programming, building, and running DB2
-- applications, visit the DB2 application development website:
--     http://www.software.ibm.com/data/db2/udb/ad
-----------------------------------------------------------------------------

-- Connect to sample database
CONNECT TO SAMPLE@

-- Find out the information of all the customer
-- Both the queries below will give the same result
XQUERY db2-fn:xmlcolumn("CUSTOMER.INFO")@
XQUERY db2-fn:sqlquery("select info from customer")@ 

-- Find out the customers information from Toronto city
-- Both the queries below will give the same result 
XQUERY db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo[addr/city="Toronto"]/name@

XQUERY db2-fn:xmlcolumn('CUSTOMER.INFO')//city[text()="Toronto"]/../../name@

-- Find out all the customer cities from country Canada
XQUERY fn:distinct-values(db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo/addr[@country="Canada"]/city)@

-- Find out number of customer in Toronto city
XQUERY fn:count(db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo[addr/city="Toronto"])@

-- Find out all the customer names whose mobile number starts with 905
XQUERY db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo[phone[@type="cell" and fn:starts-with(text(),"905")]]@

-- Find out the average price for all the products in 100 series
XQUERY let $prod_price := db2-fn:xmlcolumn('PRODUCT.DESCRIPTION')/product[fn:starts-with(@pid,"100")]/description/price
       return avg($prod_price)@
 
-- Reset the connection
CONNECT RESET@
