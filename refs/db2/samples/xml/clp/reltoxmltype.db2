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
-- SOURCE FILE NAME: reltoxmltype.db2
--
-- SAMPLE: Purchase order database uses relational tables to store the orders of
--         different customers. This data can be returned as an XML object to the
--         application. The XML object can be created using the XML constructor
--         functions on the server side.
--         To achieve this, the user can
--            1. Create new tables having XML columns. (Done in setup script)
--            2. Change the relational data to XML type using constructor functions.
--            3. Insert the data in XML columns.
--            4. Use the query to select all PO data.
--
-- PREREQUISITE:
--         The relational tables that store the purchase order data will have to
--         be created before this sample is executed. For this the file
--         setupscript.db2 will have to be run using the command
--            db2 -tvf setupscript.db2
--         Please make sure that you run the cleanup script after running the
--         sample using following command
--            db2 -tvf cleanupscript.db2
--
-- SAMPLE EXECUTION
--         After successfull execution of the script, this sample can be executed using
--            db2 -tvf reltoxmltype.db2
--
-- SQL STATEMENT USED:
--         CREATE
--         SELECT
--         INSERT
--
-- OUTPUT FILE: reltoxmltype.out (available in the online documentation)
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
  
-- CONNECT TO DATABASE
  CONNECT TO sample;

-- Insert data from the relational table into the XML tables. 
  INSERT INTO Customerinfo_New (Custid, Address) 
    (SELECT Custid, 
    XMLDOCUMENT( 
    XMLELEMENT(NAME "Address",
    XMLELEMENT(NAME "Name", c.Name),
    XMLELEMENT(NAME "Street", c.Street),
    XMLELEMENT(NAME "City", c.City),
    XMLELEMENT(NAME "Province", c.Province),
    XMLELEMENT(NAME "PostalCode", c.PostalCode)))
    FROM CustomerInfo_relational AS C);

-- Insert data from the relational table into the XML tables. 
  INSERT INTO purchaseorder_new(PoNum, OrderDate, CustID, Status, LineItems) 
    (SELECT Po.PoNum, OrderDate, CustID, Status, 
    XMLDOCUMENT(
    XMLELEMENT(NAME "itemlist", 
    XMLELEMENT(NAME "PartID", l.ProdID),  
    XMLELEMENT(NAME "Description", p.Description ), 
    XMLELEMENT(NAME "Quantity", l.Quantity),
    XMLELEMENT(NAME "Price", p.Price)))        
    FROM purchaseorder_relational AS po, lineitem_relational AS l, 
         products_relational AS P 
    WHERE l.PoNum=po.PoNum AND l.ProdID=P.ProdID);

-- Select the Purchase order. 
  SELECT po.PoNum, po.CustId, po.OrderDate,
    XMLELEMENT(NAME "PurchaseOrder",
    XMLATTRIBUTES(po.CustID AS "CustID", po.PoNum AS "PoNum",
                  po.OrderDate AS "OrderDate", po.Status AS "Status")),
    XMLELEMENT(NAME "Address", c.Address),
    XMLELEMENT(NAME "lineitems", po.LineItems)
    FROM PurchaseOrder_new AS po, CustomerInfo_new AS c 
    WHERE  po.custid = c.custid
    ORDER BY po.custID;

-- Disconnect from the database  
  CONNECT RESET;
