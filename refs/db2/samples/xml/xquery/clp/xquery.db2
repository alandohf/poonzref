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
-- SOURCE FILE NAME: xquery.db2
--
-- SAMPLE: Simple FLWOR expression Queries
--
-- SQL/XML FUNCTIONS USED
--          xmlcolumn
--          sqlquery
--
-- XQUERY FUNCTIONS/EXPRESSIONS USED
--          distinct-values
--          concat
--          upper-case
--          flwor expression
--          conditional expression
--          arithmatic expression
--
-- SAMPLE EXECUTION:
-- Run the samples with following command
--    db2 -td! -vf xquery.db2
--
-- OUTPUT FILE: xquery.out (available in the online documentation)
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
CONNECT TO SAMPLE!

-- Find out all the purchaseorders city wise
XQUERY for $city in fn:distinct-values(db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo/addr/city)
              return
                <city name='{$city}'>
              {
                  for  $cust in db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo[addr/city=$city]
                  let $po:=db2-fn:sqlquery("SELECT XMLELEMENT( NAME ""pos"",
                                               (XMLCONCAT( XMLELEMENT(NAME ""custid"", c.custid),
                                                           XMLELEMENT(NAME ""order"", c.porder)
                                                         ) ))
                                    FROM purchaseorder AS c")
          let $id:=$cust/@Cid,
              $order:=$po[custid=$id]/order
          return
          <customer id='{$id}'>
           {$cust/name}
           {$cust/addr}
           {$order}
          </customer>}
         </city>!

-- Find out all the customer product wise
XQUERY let $po:=db2-fn:sqlquery("SELECT XMLELEMENT( NAME ""pos"", 
                                                        ( XMLCONCAT( XMLELEMENT(NAME ""custid"", c.custid),
                                                                     XMLELEMENT(NAME ""order"", c.porder)
                                                        ) ))
                                      FROM purchaseorder AS c" )
                   for $partid in fn:distinct-values(db2-fn:xmlcolumn('PURCHASEORDER.PORDER')/PurchaseOrder/item/partid)
                     return
                     <Product name='{$partid}'>
                      <Customers>
                        {
                          for  $id in fn:distinct-values($po[order/PurchaseOrder/item/partid=$partid]/custid)
                          let  $order:=<quantity>
                          {fn:sum($po[custid=$id]/order/PurchaseOrder/item[partid=$partid]/quantity)}
                          </quantity>,
                        $cust:=db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo[@Cid=$id]
                      return
                      <customer id='{$id}'>
                        {$order}
                        {$cust}
                      </customer>
                      }
                   </Customers>
                 </Product>!


-- Find out all the purchaseorders province wise, then city wise and then street wise.
XQUERY let $po:=db2-fn:sqlquery("SELECT XMLELEMENT( NAME ""pos"",
                                          ( XMLCONCAT( XMLELEMENT(NAME ""custid"", c.custid),
                                          XMLELEMENT(NAME ""order"", c.porder)
                                                       ) ))
                                            FROM PURCHASEORDER as c"),
        $addr:=db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo/addr
        for $prov in distinct-values($addr/prov-state)
        return
        <province name='{$prov}'>
        {
          for $city in fn:distinct-values($addr[prov-state=$prov]/city)
          return
          <city name='{$city}'>
          {
            for $s in fn:distinct-values($addr/street) where $addr/city=$city
            return
            <street name='{$s}'>
            {
              for $info in $addr[prov-state=$prov and city=$city and street=$s]/..
              return
              <customer id='{$info/@Cid}'>
              {$info/name}
              {
                let $id:=$info/@Cid, $order:=$po[custid=$id]/order
                return $order
              }
             </customer>
            }
           </street>
          }
           </city>
        }
        </province>!


-- Combine XML data from customer.info and product.description to for the customer id 1000.
XQUERY <PurchaseOrder>
                    {
                         for $ns1_customerinfo0 in db2-fn:xmlcolumn('CUSTOMER.INFO')/customerinfo
                         where ($ns1_customerinfo0/@Cid=1001)
                         return
                         <customer customerid='{ fn:string( $ns1_customerinfo0/@Cid)}'>
                         {$ns1_customerinfo0/name}
                             <address>
                               {$ns1_customerinfo0/addr/street}
                               {$ns1_customerinfo0/addr/city}
                               {
                                  if($ns1_customerinfo0/addr/@country="US")
                                  then
                                  $ns1_customerinfo0/addr/prov-state
                                   else()
                               }
                                {
                    fn:concat ($ns1_customerinfo0/addr/pcode-zip/text(),",",fn:upper-case($ns1_customerinfo0/addr/@country
))}
                            </address>
                           </customer>
                         }
                         {
                          for $ns2_product0 in db2-fn:xmlcolumn('PRODUCT.DESCRIPTION')/product
                          where ($ns2_product0/@pid="100-100-01")
                          return
                          $ns2_product0
                      }
                    </PurchaseOrder>!

-- Reset the connection
CONNECT RESET!

