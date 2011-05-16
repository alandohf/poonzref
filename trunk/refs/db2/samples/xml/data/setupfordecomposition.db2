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
-- SOURCE FILE NAME: setupfordecomposition.db2
--
-- SAMPLE: This is the set up script for the sample xmldecompostion.db2,
--         xmldecomposition.sqc, xmldecomposition.java.
--         The tables are created that are needed for the decomposition 
--         of the XML document bookdetail.xml.
--
-- SQL STATEMENTS USED:
--         CREATE
--
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

--CONNET TO DATABASE
CONNECT TO SAMPLE;

-- CREATE the table XDB.BOOK_CONTENTS
CREATE TABLE XDB.BOOK_CONTENTS (
			        ISBN VARCHAR(13),
				CHPTNUM INTEGER, 
				CHPTTITTLE VARCHAR(50), 
				CHPTCONTENT VARCHAR(1000));

-- CREATE the table ADMIN.BOOK_CONTENTS
CREATE TABLE ADMIN.BOOK_AUTHOR (
   			         AUTHID INTEGER NOT NULL,
 		                 ISBN VARCHAR(13) NOT NULL,
        		         BOOK_TITLE VARCHAR(50),
                                 PRIMARY KEY (AUTHID, ISBN));

-- COMMIT
COMMIT;

-- RESET CONNECTION
CONNECT RESET;
