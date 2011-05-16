--
-- File: db2sampl_XML.db2
--
-- Note:
--
--    - Execute this script using command "db2 -tvf db2sampl_XML.db2"
--
--    - This script assumes that a SAMPLE database already exists.
--
--    - Existing copies of the XML tables will be dropped before they are created.
--       If they did not previously exist, the DROP TABLE commands will return SQLCODE -204.
--       This is expected.
--
--    - The XML tables will be created using the default schema for the current connection.
--
--    - The "XML" datatype is not supported on Partitioned Database environments.  Therefore,
--       this script should not be run on those environments.
--     
--    - The following schema files are required for the script
--                1. porder.xsd
--                2. customer.xsd
--                3. supplier.xsd
--                4. product.xsd
--      These files can be found in sqllib/samples/xml and sqllib/samples/db2sampl directory.

CONNECT TO sample;

---------------------------------------------
--  XML - Non-Partitioned databases only.
---------------------------------------------

  -- XML Tables

  DROP TABLESPACE IBMDB2SAMPLEXML ;
  CREATE TABLESPACE IBMDB2SAMPLEXML; 


  DROP TABLE Product;
  CREATE TABLE Product ( Pid         VARCHAR(10) NOT NULL,
                         Name        VARCHAR(128),
                         Price       DECIMAL(30,2),
                         PromoPrice  DECIMAL(30,2),
                         PromoStart  DATE,
                         PromoEnd    DATE,
                         Description XML, 
                         CONSTRAINT  PK_PRODUCT PRIMARY KEY (Pid)) in IBMDB2SAMPLEXML;

  DROP TABLE Inventory;
  CREATE TABLE Inventory ( Pid        VARCHAR(10) NOT NULL,
                           Quantity   INTEGER,
                           Location   VARCHAR(128), 
                           CONSTRAINT PK_INVENTORY PRIMARY KEY (Pid)) in IBMDB2SAMPLEXML;

  DROP TABLE Customer;
  CREATE TABLE Customer ( Cid        BIGINT NOT NULL,
                          info       XML,
                          History    XML,
                          CONSTRAINT PK_CUSTOMER PRIMARY KEY (Cid)) in IBMDB2SAMPLEXML;

  DROP TABLE PurchaseOrder;
  CREATE TABLE PurchaseOrder ( POid   BIGINT NOT NULL,
                               Status VARCHAR(10) NOT NULL WITH DEFAULT 'Unshipped',
                               custid BIGINT,
                               orderdate DATE,
                               POrder XML,
                               comments VARCHAR(1000),
                               CONSTRAINT PK_PURCHASEORDER PRIMARY KEY (POid),
                               CONSTRAINT FK_PO_CUST FOREIGN KEY (custid) REFERENCES CUSTOMER(Cid) ON DELETE CASCADE)
                               in IBMDB2SAMPLEXML;

  DROP TABLE Catalog;
  CREATE TABLE Catalog ( Name   VARCHAR(128) NOT NULL,
                         Catlog XML, CONSTRAINT PK_CATALOG PRIMARY KEY (Name) ) in IBMDB2SAMPLEXML;

  DROP TABLE Suppliers;
  CREATE TABLE Suppliers ( Sid    VARCHAR(10) NOT NULL,
                           Addr   XML, CONSTRAINT PK_PRODUCTSUPPLIER PRIMARY KEY (Sid) ) in IBMDB2SAMPLEXML;

  DROP TABLE ProductSupplier;
  CREATE TABLE ProductSupplier ( Pid VARCHAR(10) NOT NULL,
                                 Sid VARCHAR(10) NOT NULL,
                                 CONSTRAINT PK_PRODUCTSUPPLIER PRIMARY KEY (Pid, Sid ) ) in IBMDB2SAMPLEXML;

-- Register schemas
DROP XSROBJECT customer;
REGISTER XMLSCHEMA http://posample.org FROM customer.xsd AS customer ;
COMPLETE XMLSCHEMA custOmer ;

DROP XSROBJECT product;
REGISTER XMLSCHEMA http://posample.org FROM product.xsd AS product ;
COMPLETE XMLSCHEMA product ;

DROP XSROBJECT porder;
REGISTER XMLSCHEMA http://posample.org FROM porder.xsd AS porder;
COMPLETE XMLSCHEMA porder;

DROP XSROBJECT supplier;
REGISTER XMLSCHEMA http://posample.org FROM supplier.xsd AS supplier;

-- Create Index
CREATE UNIQUE INDEX cust_cid_xmlidx ON customer(info) 
  GENERATE KEY USING XMLPATTERN 'declare default element namespace "http://posample.org"; /customerinfo/@cid' 
  AS SQL DOUBLE;

CREATE INDEX cust_name_xmlidx ON customer(info) 
   GENERATE KEY USING XMLPATTERN 'declare default element namespace "http://posample.org"; /customerinfo/name' 
   AS SQL VARCHAR(50);

CREATE INDEX cust_phones_xmlidx ON customer(info) 
   GENERATE KEY USING  XMLPATTERN 'declare default element namespace "http://posample.org"; /customerinfo//phone' 
   AS SQL VARCHAR(25);

CREATE INDEX cust_phonet_xmlidx on customer(info) 
   GENERATE KEY USING  XMLPATTERN 'declare default element namespace "http://posample.org";/customerinfo/phone/@type'
   AS SQL VARCHAR(25);

CREATE INDEX prod_name_xmlidx ON product(description)  
   GENERATE KEY USING  XMLPATTERN 'declare default element namespace "http://posample.org";/product/description/name' 
   AS SQL VARCHAR(128);

CREATE INDEX prod_detail_xmlidx ON product(description) 
   GENERATE KEY USING XMLPATTERN 'declare default element namespace "http://posample.org"; /product/description/detail'
   AS SQL VARCHAR HASHED;

CREATE INDEX PO_prods_xmlidx ON purchaseorder(POrder) 
   GENERATE KEY USING XMLPATTERN 'declare default element namespace "http://posample.org"; /PurchaseOrder/itemlist/item/product/@pid'
   AS SQL DOUBLE;

CREATE INDEX PO_Cid_xmlidx ON purchaseorder(POrder) 
  GENERATE KEY USING XMLPATTERN 'declare default element namespace "http://posample.org"; /PurchaseOrder/@Cid' 
  AS SQL DOUBLE;

CREATE INDEX PO_zip_xmlidx ON purchaseorder(POrder) 
    GENERATE KEY USING XMLPATTERN 'declare default element namespace "http://posample.org"; /PurchaseOrder/customerAdr/addr/pcode-zip'
    AS SQL VARCHAR(16);

-- Insert XML Data
-- c1.xml
INSERT INTO CUSTOMER ( Cid, Info ) VALUES ( 1000,XMLVALIDATE(
                                       XMLPARSE ( DOCUMENT '<customerinfo xmlns="http://posample.org" Cid=''1000''>
                                                                        <name>Kathy Smith</name>
                                                                        <addr country="Canada">
                                                                        <street>5 Rosewood</street>
                  						        <city>Toronto</city>
									<prov-state>Ontario</prov-state>
									<pcode-zip>M6W 1E6</pcode-zip>
									</addr>
									<phone type="work">416-555-1358</phone>
									</customerinfo>' PRESERVE WHITESPACE ) 
                                       ACCORDING TO XMLSCHEMA ID customer ));

-- c2.xml
INSERT INTO CUSTOMER ( Cid, Info ) VALUES ( 1001,XMLVALIDATE(
                                       XMLPARSE ( DOCUMENT '<customerinfo xmlns="http://posample.org" Cid=''1001''>
                                                            <name>Kathy Smith</name>
									<addr country="Canada">
									<street>25 EastCreek</street>
									<city>Markham</city>
									<prov-state>Ontario</prov-state>
									<pcode-zip>N9C 3T6</pcode-zip>
									</addr>
									<phone type="work">905-555-7258</phone>
									</customerinfo>' PRESERVE WHITESPACE ) 
                                       ACCORDING TO XMLSCHEMA ID customer ));
  

-- c3.xml
INSERT INTO CUSTOMER ( Cid, Info ) VALUES ( 1002,XMLVALIDATE(
                                        XMLPARSE ( DOCUMENT '<customerinfo xmlns="http://posample.org" Cid=''1002''>
        		                                      <name>Jim Noodle</name>
									<addr country="Canada">
									<street>25 EastCreek</street>
									<city>Markham</city>
									<prov-state>Ontario</prov-state>
									<pcode-zip>N9C 3T6</pcode-zip>
									</addr>
									<phone type="work">905-555-7258</phone>
                                              				</customerinfo>' PRESERVE WHITESPACE )
                                       ACCORDING TO XMLSCHEMA ID customer ));

-- c4.xml
INSERT INTO CUSTOMER ( Cid, Info ) VALUES ( 1003,XMLVALIDATE(
                                            XMLPARSE ( DOCUMENT '<customerinfo xmlns="http://posample.org" Cid=''1003''>
                                                              <name>Robert Shoemaker</name>
									<addr country="Canada">
									<street>1596 Baseline</street>
									<city>Aurora</city>
									<prov-state>Ontario</prov-state>
									<pcode-zip>N8X 7F8</pcode-zip>
									</addr>
									<phone type="work">905-555-7258</phone>
									<phone type="home">416-555-2937</phone>
									<phone type="cell">905-555-8743</phone>
									<phone type="cottage">613-555-3278</phone>
									</customerinfo>' PRESERVE WHITESPACE )
                                       ACCORDING TO XMLSCHEMA ID customer ));

-- c5.xml
INSERT INTO CUSTOMER ( Cid, Info ) VALUES ( 1004,XMLVALIDATE(
                                           XMLPARSE ( DOCUMENT '<customerinfo xmlns="http://posample.org" Cid=''1004''>
                                                              <name>Matt Foreman</name>
									<addr country="Canada">
									<street>1596 Baseline</street>
									<city>Toronto</city>
									<prov-state>Ontario</prov-state>
									<pcode-zip>M3Z 5H9</pcode-zip>
									</addr>
									<phone type="work">905-555-4789</phone>
									<phone type="home">416-555-3376</phone>
									<assistant>
									<name>Gopher Runner</name>
									<phone type="home">416-555-3426</phone>
									</assistant>
									</customerinfo>' PRESERVE WHITESPACE )
                                       ACCORDING TO XMLSCHEMA ID customer));

-- c6.xml
INSERT INTO CUSTOMER ( Cid, Info ) VALUES ( 1005,XMLVALIDATE(
                                           XMLPARSE ( DOCUMENT '<customerinfo xmlns="http://posample.org" Cid=''1005''>
                                                               <name>Larry Menard</name>
									<addr country="Canada">
									<street>223 NatureValley Road</street>
									<city>Toronto</city>
									<prov-state>Ontario</prov-state>
									<pcode-zip>M4C 5K8</pcode-zip>
									</addr>
									<phone type="work">905-555-9146</phone>
									<phone type="home">416-555-6121</phone>
									<assistant>
									<name>Goose Defender</name>
									<phone type="home">416-555-1943</phone>
									</assistant>
                                                     			</customerinfo>' PRESERVE WHITESPACE)
                                         ACCORDING TO XMLSCHEMA ID customer ));



INSERT INTO PRODUCT ( pid, name, Price, PromoPrice, PromoStart, PromoEnd, description ) 
       VALUES ( '100-100-01','Snow Shovel, Basic 22 inch', 9.99, 7.25, '11-19-2004','12-19-2004', XMLVALIDATE(
                            XMLPARSE ( DOCUMENT '<product xmlns="http://posample.org" pid=''100-100-01'' >
                                        <description>
					<name>Snow Shovel, Basic 22 inch</name>
					<details>Basic Snow Shovel, 22 inches wide, straight handle with D-Grip</details>
					<price>9.99</price>
					<weight>1 kg</weight>
					</description>
					</product>'
                            PRESERVE WHITESPACE ) ACCORDING TO XMLSCHEMA ID product));

INSERT INTO PRODUCT ( pid,name, Price, PromoPrice, PromoStart, PromoEnd, description )
       VALUES ( '100-101-01','Snow Shovel, Deluxe 24 inch',19.99,15.99,'12-18-2005','02-28-2006', XMLVALIDATE( 
                            XMLPARSE ( DOCUMENT '<product xmlns="http://posample.org" pid=''100-101-01''>
                                        <description>
					<name>Snow Shovel, Deluxe 24 inch</name>
					<details>A Deluxe Snow Shovel, 24 inches wide, ergonomic curved handle with D-Grip</details>
					<price>19.99</price>
					<weight>2 kg</weight>
					</description>
					</product>'
                            PRESERVE WHITESPACE ) ACCORDING TO XMLSCHEMA ID product));

INSERT INTO PRODUCT ( pid, name, Price, PromoPrice, PromoStart, PromoEnd,description ) 
       VALUES ( '100-103-01','Snow Shovel, Super Deluxe 26 inch',49.99,39.99,'12-22-2005','02-22-2006', XMLVALIDATE( 
                            XMLPARSE ( DOCUMENT '<product xmlns="http://posample.org"  pid=''100-103-01''>
                                        <description>
					<name>Snow Shovel, Super Deluxe 26 inch</name>
					<details>Super Deluxe Snow Shovel, 26 inches wide, ergonomic battery heated curved handle with upgraded D-Grip</details>
					<price>49.99</price>
					<weight>3 kg</weight>
					</description>
					</product>'
                            PRESERVE WHITESPACE ) ACCORDING TO XMLSCHEMA ID product));

INSERT INTO PRODUCT ( pid, name, Price,description ) 
      VALUES ( '100-201-01', 'Ice Scraper, Windshield 4 inch',3.99,XMLVALIDATE( 
                            XMLPARSE ( DOCUMENT '<product xmlns="http://posample.org" pid=''100-201-01''>
					<description>
					<name>Ice Scraper, Windshield 4 inch</name>
					<details>Basic Ice Scraper 4 inches wide, foam handle</details>
					<price>3.99</price>
					</description>
					</product>'
                            PRESERVE WHITESPACE ) ACCORDING TO XMLSCHEMA ID product));


INSERT INTO PURCHASEORDER(poid, status, porder, orderdate, comments, custid) 
         values(5000,'Unshipped',XMLPARSE(DOCUMENT('
                       <PurchaseOrder xmlns="http://posample.org"  PoNum="5000" OrderDate="2006-02-18" Status="Unshipped" >
			   <item>
    		       	  	 <partid>100-100-01</partid>
    			  	 <name>Snow Shovel, Basic 22 inch</name>
    		           	 <quantity>3</quantity>
			   	 <price>9.99</price>
    			   </item>
   		    	   <item>
     				<partid>100-103-01</partid>
     				<name>Snow Shovel, Super Deluxe 26 inch</name>
     				<quantity>5</quantity>
    				<price>49.99</price>
   		     	   </item>
			</PurchaseOrder>
			')), '2006-02-18','THIS IS A NEW PURCHASE ORDER',1002);

INSERT INTO PURCHASEORDER(poid, status, porder, orderdate, comments, custid) 
        values(5001,'Shipped',XMLPARSE(DOCUMENT('
                      <PurchaseOrder  xmlns="http://posample.org" PoNum="5001" OrderDate="2005-02-03" Status="Shipped" >
  			  <item>
    				<partid>100-101-01</partid>
    				<name>Snow Shovel, Deluxe 24 inch</name>
    				<quantity>1</quantity>
    				<price>19.99</price>
   			  </item>
   			  <item>
    				<partid>100-103-01</partid>
    				<name>Snow Shovel, Super Deluxe 26 inch</name>
    				<quantity>2</quantity>
    				<price>49.99</price>
   		      	  </item>
   			  <item>
    				<partid>100-201-01</partid>
    				<name>Ice Scraper, Windshield 4 inch</name>
    				<quantity>1</quantity>
    				<price>3.99</price>
    			  </item>
			</PurchaseOrder>
			')) ,'2005-02-03','THIS IS A NEW PURCHASE ORDER',1003);

INSERT INTO PURCHASEORDER(poid, status, porder, orderdate, comments, custid) 
         VALUES(5002,'Shipped', XMLPARSE(DOCUMENT('
                <PurchaseOrder xmlns="http://posample.org" PoNum="5002" OrderDate="2004-02-29" Status="Shipped" >
  			<item>
    				<partid>100-100-01</partid>
    				<name>Snow Shovel, Basic 22 inch</name>
    				<quantity>3</quantity>
    				<price>9.99</price>
  			</item>
  			<item>
    				<partid>100-101-01</partid>
 			        <name>Snow Shovel, Deluxe 24 inch</name>
    				<quantity>5</quantity>
    				<price>19.99</price>
  			</item>
  			<item>
    				<partid>100-201-01</partid>
    				<name>Ice Scraper, Windshield 4 inch</name>
    				<quantity>5</quantity>
    				<price>3.99</price>
   			 </item>
		</PurchaseOrder>
		')),'2004-02-29','THIS IS A NEW PURCHASE ORDER',1001);

INSERT INTO PURCHASEORDER(poid, status, porder, orderdate,comments, custid) VALUES(
             5003,'UnShipped', XMLPARSE(DOCUMENT('
                <PurchaseOrder PoNum="5003" xmlns="http://posample.org" OrderDate="2005-02-28" Status="UnShipped" >
  			<item>
    				<partid>100-100-01</partid>
    				<name>Snow Shovel, Basic 22 inch</name>
    				<quantity>1</quantity>
    				<price>9.99</price>
  			</item>
		</PurchaseOrder>
		')) ,'2005-02-28','THIS IS A NEW PURCHASE ORDER',1002);

INSERT INTO PURCHASEORDER(poid, status, porder, orderdate, comments, custid) 
               VALUES(5004,'Shipped',XMLPARSE(DOCUMENT('
                <PurchaseOrder xmlns="http://posample.org"  PoNum="5004" OrderDate="2005-11-18" Status="Shipped" >
  			<item>
    				<partid>100-100-01</partid>
   			        <name>Snow Shovel, Basic 22 inch</name>
    				<quantity>4</quantity>
    				<price>9.99</price>
  			</item>
  			<item>
    				<partid>100-103-01</partid>
    				<name>Snow Shovel, Super Deluxe 26 inch</name>
    				<quantity>2</quantity>
    				<price>49.99</price>
  			</item>
		</PurchaseOrder>
		')) ,'2005-11-18','THIS IS A NEW PURCHASE ORDER',1005);

INSERT INTO PURCHASEORDER(poid, status, porder, orderdate, comments, custid) 
            VALUES(5006,'Shipped', XMLPARSE(
                  DOCUMENT('<PurchaseOrder xmlns="http://posample.org" PoNum="5006" OrderDate="2006-03-01" Status="Shipped" >
	                <item>
    				<partid>100-100-01</partid>
    				<name>Snow Shovel, Basic 22 inch</name>
    				<quantity>3</quantity>
    				<price>9.99</price>
  			</item>
 		        <item>
    				<partid>100-101-01</partid>
    				<name>Snow Shovel, Deluxe 24 inch</name>
    				<quantity>5</quantity>
    				<price>19.99</price>
  			</item>
  			<item>
    				<partid>100-201-01</partid>
    				<name>Ice Scraper, Windshield 4 inch</name>
    				<quantity>5</quantity>
    				<price>3.99</price>
  			</item>
			</PurchaseOrder>
		')) ,'2006-03-01','THIS IS A NEW PURCHASE ORDER',1002);


INSERT INTO INVENTORY VALUES ('100-100-01', 5,  NULL);

INSERT INTO INVENTORY VALUES ('100-101-01', 25, 'Store');

INSERT INTO INVENTORY VALUES ('100-103-01', 55, 'Store');

INSERT INTO INVENTORY VALUES ('100-201-01', 99, 'Warehouse');


CONNECT RESET;
TERMINATE;
