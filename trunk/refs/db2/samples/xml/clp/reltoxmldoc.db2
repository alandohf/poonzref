----------------------------------------------------------------------------
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
-- SOURCE FILE NAME: reltoxmldoc.db2
--
-- SAMPLE: Purchase order database uses relational tables to store the orders of
--         different customers. This data can be returned as an XML object to the
--         application. The XML object can be created using the XML constructor
--         functions on the server side.
--         To achieve this, the user can
--           1. Create a stored procedure to implement the logic to create the XML 
--              object using XML constructor functions.
--           2. Register the above stored procedure to the database.
--           3. Call the procedure whenever all the PO data is needed instead of using complex joins.
--
-- PREREQUISITE:
--         The relational tables that store the purchase order data will have to
--         be created before this sample is executed. For this the file
--         setupscript.db2 will have to be run using the command
--            db2 -tvf setupscript.db2
--         The stored procedure will have to be registered before this sample is executed.
--         The command to register the stored procedure is
--            db2 -td@ -f reltoxmlproc.db2
--
-- SQL STATEMENT USED:
--         SELECT
--         CALL
--         CONNECT RESET
--
-- OUTPUT FILE: reltoxmldoc.out (available in the online documentation)
-----------------------------------------------------------------------------

-- CONNECT TO DATABSE
  CONNECT TO sample;

-- Select purchase order data from the relational tables.
  SELECT po.CustID, po.PoNum, po.OrderDate, po.Status, 
         count(l.ProdID) as Items, sum(p.Price) as total,
         po.Comment, c.Name, c.Street, c.City, c.Province, c.PostalCode
     FROM PurchaseOrder_relational as po, CustomerInfo_relational as c, 
          Lineitem_relational as l, Products_relational as p 
     WHERE po.CustID = c.CustID and po.PoNum = l.PoNum and l.ProdID = p.ProdID
     GROUP BY po.PoNum,po.CustID,po.OrderDate,po.Status,c.Name,c.Street,c.City,c.Province,    
              c.PostalCode,po.Comment
     ORDER BY  po.CustID,po.OrderDate;

-- Call the stored procedure. This stored procedure will convert all the relational 
-- purchase order data into an well formed XML document. Thus all the relational data is 
-- stored in the XML document.
  CALL reltoxmlproc();

-- Reset Database connection
  CONNECT RESET;
