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
-- SOURCE FILE NAME: sqlxquery.db2
--
-- SAMPLE: SQL/XML Queries 
--
-- SQL/XML FUNCTIONS USED
--          sqlquery
--          xmlexists
--          xmlquery 
--
-- SQL STATEMETNS USED
--          SELECT 
--
-- SAMPLE EXECUTION:
-- Run the samples with following command
--    db2 -td@ -vf sqlxquery.db2
--
-- OUTPUT FILE: xpath.out (available in the online documentation)
-----------------------------------------------------------------------------
--
-- For more information about the command line processor (CLP) scripts,
-- see the README file.
--
-- For information on using XQUERY statements, see the XQUERY Reference.
--
-- For information on using SQL statements, see the SQL Reference.

-- For the latest information on programming, building, and running DB2
-- applications, visit the DB2 application development website:
--     http://www.software.ibm.com/data/db2/udb/ad
-----------------------------------------------------------------------------

-- Connect to sample database
CONNECT TO SAMPLE@

-- Find out first purchaseorders of the customer with name Robert Shoemaker 
SELECT XMLQUERY('$p/PurchaseOrder/item[1]' PASSING p.porder AS "p") 
     FROM purchaseorder AS p, customer AS c
     WHERE XMLEXISTS('$custinfo/customerinfo[name="Robert Shoemaker" and @Cid = $cid]'  
                     PASSING c.info AS "custinfo", p.custid AS "cid")@
 
-- Return the first item in the purchaseorder and the history of all the customer 
-- when the following conditions are met
-- 1. Customer ID in the sequence (1000,1002,1003) or
-- 2. Name is sequece (X,Y,Z)
SELECT XMLQUERY('$p/PurchaseOrder/item[1]' passing p.porder as "p"),XMLQUERY('$x/history' passing c.history as "x") 
       FROM purchaseorder as p,customer as c  
       WHERE XMLEXISTS('$custinfo/customerinfo[name=(X,Y,Z) or @Cid=(1000,1002,1003) and @Cid=$cid ]'
                        PASSING c.info AS "custinfo", p.custid AS "cid")@

-- Find out all the customer names and sort them according to number of orders
WITH count_table AS ( SELECT count(poid) AS c,custid 
                FROM purchaseorder,customer 
                WHERE cid=custid GROUP BY custid ) 
     SELECT c,custid, XMLQUERY('$s/customerinfo[@Cid=$id]/name' 
                                PASSING customer.info AS "s", count_table.custid AS "id") 
     FROM customer,count_table 
     WHERE custid=cid ORDER BY c@

-- Find out the number of purchaseorder having item with partid 100-101-01 for customer Robert Shoemaker 
WITH cid_table AS (SELECT Cid FROM customer 
                   WHERE XMLEXISTS('$custinfo/customerinfo[name="Robert Shoemaker"]' PASSING customer.info AS "custinfo")) 
     SELECT count(poid) FROM purchaseorder,cid_table 
     WHERE XMLEXISTS('$po/itemlist/item[partid="100-101-01"]' PASSING purchaseorder.porder AS "po") 
                 AND purchaseorder.custid=cid_table.cid@ 

-- Reset the connection
CONNECT RESET@


