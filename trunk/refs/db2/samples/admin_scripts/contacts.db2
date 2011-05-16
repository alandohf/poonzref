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
-- SOURCE FILE NAME: contacts.db2
--
-- SAMPLE: How to add, update and drop contacts and contactgroups
--
--         This sample shows:
--           1. How to add a contact for a user with e-mail address.
--           2. How to create a contactgroup with contact names.
--           3. How to update the address for the sample user.
--           4. How to update the contactgroup by adding a contact.
--           5. How to read a contact list.
--           6. How to read a contact group list
--           7. How to drop a contact from the list of contacts.
--           8. How to drop a contactgroup from the list of groups
--
-- Note: The Database Administration Server(DAS) should be running.
--
-- SQL STATEMENTS USED:
--           ADD
--           CONNECT
--           DROP
--           GET
--           UPDATE
--           TERMINATE
--
-- OUTPUT FILE: contacts.out (available in the online documentation)
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

-- Connect to sample database
CONNECT  TO sample;

-- Add contacts for a user with e-mail address
ADD CONTACT testuser1 TYPE EMAIL ADDRESS testuser1@test.com;

ADD CONTACT testuser2 TYPE EMAIL ADDRESS testuser2@test.com;

-- Create a contactgroup with a contact name
ADD CONTACTGROUP gname1 CONTACT testuser1;

-- Update the address for the user testuser1
UPDATE CONTACT testuser1 USING ADDRESS address@test.com;

-- Update the contactgroup by adding a contact
UPDATE CONTACTGROUP gname1 ADD CONTACT testuser2;

-- Get the list of contactgroups
GET CONTACTGROUPS;

-- Get the list of contacts
GET CONTACTS;

-- Drop a contactgroup from the list of groups
DROP CONTACTGROUP gname1;

-- Drop contacts from the list of contacts
DROP CONTACT testuser1;

DROP CONTACT testuser2;

-- Disconnect from the database
CONNECT RESET;

TERMINATE;
