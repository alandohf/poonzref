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
-- SOURCE FILE NAME: xmldecomposition.db2
--
-- SAMPLE: This sample demonstrates XML Decomposition functionality. Using 
--         this functionality, information from a XML document can be 
--         stored in relational tables. 
--
-- USER SCENARIO:
--
--         Consider the user scenario below:
--
--	   A bookstore owner has some XML documents which contains descriptive 
--         information about a book which he has for sale. The owner needs to 
--         store these details in a relational table for easy retrival of information. 
--         He/She can easily do it using the Decomposition function. 
--
-- SOLUTION:
--         The user must have an annotated schema based on which the instance document 
--         can be decomposed. Once a valid annotated schema for the instance document  
--         is ready , it needs to be registered with the XML Schema repository with 
--         decomposition option enabled. Also the tables in which the data will be 
--         decomposed should exist before the schema is registered. Now using the new 
--         XMLDecomp function, the user can decompose the instance document and put the 
--         data in the relational tables.
--
--	   Here the tables that we need are 
--		a) ADMIN.BOOK_AUTHOR
--		b) XDB.BOOK_CONTENTS
--	   
-- 	  As per the schema document BOOKDETAIL.XSD, the data in the instance document
--        BOOKDETAIL.XML will be put into these two tables. As per the annotations in
--        the xmlschema, the schema for the table BOOK_AUTHOR will be ADMIN. While for
--        the other tables it will be the value assigned by the annotation
--           defaultSQLSchema which is XDB.
--        This annotation can be used only once in the xmlschema.
--
--        The text within the tag "authorId" will be of type integer and will be inserted
--        in the column "AUTHID" of the TABLE "BOOK_AUTHOR". A condition annotation has
--        been put here to check if the "AUTHID" is a number between 1 and 999. If the 
--        value passes the CONDITION check, then it is inserted in the table.
--        
--        The text in the "chapter" tag is inserted in different tables and different 
--        columns. The contents of tag "chaptercontents" is inserted in the column  
--        "CHPTCONTENT" of TABLE "BOOK_CONTENTS". The annoatation truncate indicates
--        that the value to be inserted into the column will be trucated if its size is larger 
--        than the column size. Another annotation that is used for this element is
--        contenthandling, which indicates that the concatenation of this element's character 
--        data (including character content of CDATA sections) with the character data in this 
--        element's descendants, in document order will be inserted into the table.
--   
-- PRE-REQUISTES
--        The instance document i,e. "bookdetail.xml" and the annotated schema that will be
--        registered to the XSR "bookdetail.xsd" have to exist in the same directory as the 
--        sample itself. The Schema document needs to be properly annotated to ensure that
--        the right data is inserted into the right table.
--
-- EXECUTION 
--        The sample can be executed by first running the setup script which creates
--        the required tables. The script can be run using the command
--             db2 -tvf setupfordecomposition.db2
--        Execute the sample using the command
--             db2 -tvf xmldecomposition.db2
--        The clean up script will have to be executed to drop all the tables that
--        were create by the setupscript.
--             db2 -tvf cleanupfordecomposition.db2
--
-- SQL STATEMENTS USED:
--         REGISTER XMLSCHEMA
--         COMPLETE XMLSCHEMA
--         SELECT
--	   DECOMPOSE
--         DROP
--
-- OUTPUT FILE: xmldecomposition.out (available in the online documentation)
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

-- Connect to database
CONNECT TO SAMPLE;

--Register the schema documents.
REGISTER XMLSCHEMA 'http://bookdetailschema.com/book_schema1.xsd' FROM 'bookdetail.xsd' as xdb.bookdetail;

--Complete schema registration
COMPLETE XMLSCHEMA xdb.bookdetail ENABLE DECOMPOSITION;

--Check catalog tables for information regarding registered schema.
SELECT status, decomposition, decomposition_version FROM SYSIBM.SYSXSROBJECTS where XSROBJECTNAME = 'BOOKDETAIL';

--Perform a select on the relational table to see if it has any records (should return zero records here).
SELECT * FROM XDB.BOOK_CONTENTS;
SELECT * FROM ADMIN.BOOK_AUTHOR;

--Decompose the XML document
DECOMPOSE XML DOCUMENT bookdetail.xml
		       XMLSCHEMA xdb.bookdetail
	               VALIDATE;	

-- Check Decomposition result
SELECT * FROM XDB.BOOK_CONTENTS;
SELECT * FROM ADMIN.BOOK_AUTHOR;

-- Perform Commit
COMMIT;

-- Reset connection
CONNECT RESET;

