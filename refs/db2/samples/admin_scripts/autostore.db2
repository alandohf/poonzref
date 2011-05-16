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
-- SOURCE FILE NAME: autostore.db2
--    
-- SAMPLE: How to create, backup & restore databases enabled with 
--         automatic storage. 
--
-- SQL STATEMENT USED:
--          ALTER DATABASE
--          ALTER TABLESPACE
--          BACKUP DATABASE
--          CONNECT RESET
--          CONNECT TO  
--          CREATE DATABASE
--          CREATE TABLESPACE
--          DROP DATABASE
--          DROP TABLESPACE
--          GET SNAPSHOT FOR
--          RESTORE DATABASE         
-- 
-- OUTPUT FILE: autostore.out (available in the online documentation)
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

-- If automatic storage option is set as NO, then only one storage path can be
-- specified to be used for creation of database
-- The storage paths must exist before CREATE DATABASE command is executed

-- Create the storage paths

-- Below commands are specific to Unix platforms
-- Comment them if executing on Windows 
!mkdir $HOME/storpath1;
!mkdir $HOME/storpath2;
!mkdir $HOME/storpath3;
!mkdir $HOME/dbpath;

-- Remove the comments for following group of commands when running on Windows
-- !mkdir %DB2PATH%\storpath1;
-- !mkdir %DB2PATH%\storpath2;
-- !mkdir %DB2PATH%\storpath3;
-- !mkdir %DB2PATH%\dbpath;

-- Create a database enabled for automatic storage with two storage paths and
-- on a specified database path 
-- The storage paths used are: $HOME/storpath1, $HOME/storpath2
-- The database path use is  : $HOME/dbpath
-- (Uncomment one of the below two statements based on the platform it is run)

! db2 CREATE DATABASE autodb AUTOMATIC STORAGE YES ON 
        $HOME/storpath1, $HOME/storpath2 DBPATH ON $HOME/dbpath;

--! db2 CREATE DATABASE autodb AUTOMATIC STORAGE YES ON 
--        %DB2PATH%\storpath1, %DB2PATH%\storpath2 DBPATH ON %DB2PATH%\dbpath;

CONNECT TO autodb;

-- Create a tablespace enabled for automatic storage. If no MANAGED BY clause 
-- is specified the tablespace is, by default, managed by automatic storage.
CREATE TABLESPACE TS1;

-- Create another tablespace enabled to auto-resize
-- TS2 is created with an initial size of 100 MB and with a maximum size of 1 GB
-- (By default AUTORESIZE is set to YES)
CREATE TABLESPACE TS2 INITIALSIZE 100 M MAXSIZE 1 G; 

-- Create tablespace without auto-resize enabled 
CREATE TABLESPACE TS3 AUTORESIZE NO;

-- Create tablespace enabled to auto-resize without any upper bound on 
-- maximum size 
CREATE TABLESPACE TS4
  MANAGED BY DATABASE
  USING (FILE 'TS3File' 1000)
  AUTORESIZE YES
  MAXSIZE NONE;

-- Alter tablespace to increase its size by 5 percent
ALTER TABLESPACE TS4 INCREASESIZE 5 PERCENT;

-- Alter database to add one more storage path, $HOME/storpath3, to the
-- existing space for automatic storage table spaces
-- Running the ALTER DATABASE statement in a shell as path substitution
-- can be done inside a sheell
-- Uncomment one of the below statements based on the platform it is run

!db2 "CONNECT TO AUTODB"; 
!db2 "ALTER DATABASE autodb ADD STORAGE ON '$HOME/storpath3'";

--!db2 "ALTER DATABASE autodb ADD STORAGE ON '%DB2PATH%\storpath3'";

-- Check the status information of tablespaces for database AUTODB
GET SNAPSHOT FOR TABLESPACES ON autodb;

-- Disconnect from database
!db2 "CONNECT RESET";

-- Backup the database
BACKUP DATABASE autodb;

-- Connect to database
CONNECT TO autodb;

-- Drop the tablespaces
DROP TABLESPACE TS1;
DROP TABLESPACE TS2;
DROP TABLESPACE TS3;
DROP TABLESPACE TS4;

-- Disconnect from database
CONNECT RESET;

-- Drop the database
-- DROP DATABASE autodb;

-- Restore the database to a set of storage paths
-- Uncomment one of the below two statements based on the platform it is run

! db2 "RESTORE DATABASE autodb ON '$HOME/storpath2', '$HOME/storpath3'
        DBPATH ON '$HOME/dbpath' WITHOUT PROMPTING";

--! db2 "RESTORE DATABASE autodb ON '%DB2PATH%\storpath2', '%DB2PATH%\storpath3'
--        DBPATH ON '%DB2PATH%\dbpath' WITHOUT PROMPTING";

-- Drop the database 'AUTODB'
DROP DB AUTODB;

-- Remove the directories.
-- Below commands are specific to Unix platforms
-- Comment them if executing on Windows

!rm -rf $HOME/storpath1;
!rm -rf $HOME/storpath2;
!rm -rf $HOME/storpath3;
!rm -rf $HOME/dbpath;

-- Remove the comments for following group of commands when running on Windows
-- !rd %DB2PATH%\storpath1;
-- !rd %DB2PATH%\storpath2;
-- !rd %DB2PATH%\storpath3;
-- !rd %DB2PATH%\dbpath;

TERMINATE;
