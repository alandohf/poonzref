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
-- SOURCE FILE NAME: xmldb2batch.db2
--
-- SAMPLE: How to perform db2batch with a new datatype XML
--
-- PREREQUISITE: Copy "xmldb2batch_in.sql" to the current working directory.
--
-- SYSTEM COMMANDS USED:
--         DB2BATCH
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

-- This sample will use a flat file called xmldb2batch_in.sql as input file

-- Invoke db2batch from command line with the following options:

-- -d    Database against which SQL statements are to be applied "SAMPLE"
-- -f    Name of an input file containing SQL statements "xmldb2batch_in.sql"
-- -s    Provides a summary table for each query or block of queries,
--       containing elapsed time, CPU times, the rows fetched, and the rows printed
-- -w    To set maximum result set column width "400"
-- -r    An output file that will contain the query results. "xmldb2batch_out.sql"

!db2batch -d sample -f xmldb2batch_in.sql -w 400 -s on -r xmldb2batch_out.sql;
