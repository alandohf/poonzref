---------------------------------------------------------------------------
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
-- SOURCE FILE NAME: flwor.db2
--
-- SAMPLE: Simple FLWOR expression Queries
--
-- SQL/XML FUNCTIONS USED
--          xmlcolumn
--
-- XQUERY FUNCTIONS/EXPRESSIONS USED
--          flwor expression
--          conditional expression 
--          arithmatic expression
-- 
-- SAMPLE EXECUTION:
-- Run the samples with following command
--    db2 -td@ -vf flwor.db2
--
-- OUTPUT FILE: flwor.out (available in the online documentation)
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

-- List down the name of customer in Canada in alphabetical order
XQUERY for $custinfo in db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo[addr/@country="Canada"] 
       order by $custinfo/name
       return $custinfo/name @

-- List down the name and the address of the customer having cid greater then 1000 
-- and wrap the result in an element customer.
XQUERY for $customer in db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo where ($customer/@Cid gt 1002)
       return 
 
     <element>
          {$customer/name}
          {$customer/addr}
       </element>@

-- List down the street and city of the customers when the following conditions are met
-- Cid > 1000 
-- Country attribute is not equal to US.
XQUERY for $customer in db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo 
       where ($customer/@Cid gt 1002) and ($customer/addr/@country !="US")
       return
      <customer customerid='{fn:string($customer/@Cid)}'>
        {$customer/name}
        <address>
          {$customer/addr/street}
          {$customer/addr/city}
        </address>
      </customer>@

-- Find the product with highest price. 
-- The following Query will give the first product as output if their are 2 products wit same max price
XQUERY  let $prod := for $product in db2-fn:xmlcolumn('PRODUCT.DESCRIPTION')/product/description 
        order by $product/price
        return $product 
        return
        <product>
           {$prod[1]/name}
        </product>@ 

-- The following Query will give all the product with the same max price 
XQUERY let $prod :=  db2-fn:xmlcolumn('PRODUCT.DESCRIPTION')/product/description 
       let $price := max($prod/price)
       return
       <product>
         {$prod[price=$price]/name}
       </product>@
 
-- Find names of all the products wrap it in product element 
-- having an attribute "basic" with value true if the price < 10 otherwise false
XQUERY for $prod in db2-fn:xmlcolumn('PRODUCT.DESCRIPTION')/product/description 
        return ( 
	if ($prod/price < 10) 
	then <product basic = "true">{fn:data($prod/name)}</product> 
	else <product basic = "false">{fn:data($prod/name)}</product>)@

-- Reset the connection
CONNECT RESET@
 
