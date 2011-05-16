-----------------------------------------------------------------------------
-- Licensed Materials - Property of IBM
-- 
-- Governed under the terms of the International
-- License Agreement for Non-Warranted Sample Code.
--
-- (C) COPYRIGHT International Business Machines Corp. 1995 - 2002        
-- All Rights Reserved.
--
-- US Government Users Restricted Rights - Use, duplication or
-- disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
-----------------------------------------------------------------------------
--
-- SOURCE FILE NAME: stock.db2
--    
-- SAMPLE: How to use triggers
--
-- SQL STATEMENTS USED:
--         DROP TABLE
--         CREATE TABLE
--         INSERT
--         CREATE TRIGGER
--         SELECT
--         UPDATE
--         DROP TRIGGER
--
-- OUTPUT FILE: stock.out (available in the online documentation)
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

create table currentquote (symbol char(3) not null,
                           quote  decimal(6,2),
                           status varchar(8));

create table quotehistory (symbol char(3) not null,
                           quote  decimal(6,2),  timestamp timestamp);

insert into currentquote values ('IBM',68.5,null);

CREATE TRIGGER STOCK_STATUS                                    
       NO CASCADE BEFORE UPDATE OF QUOTE ON CURRENTQUOTE       
       REFERENCING NEW AS NEWQUOTE OLD AS OLDQUOTE             
       FOR EACH ROW MODE DB2SQL                                
          SET NEWQUOTE.STATUS =                                
             CASE                                              
                WHEN NEWQUOTE.QUOTE >=                         
                      (SELECT MAX(QUOTE) FROM QUOTEHISTORY     
                       WHERE SYMBOL = NEWQUOTE.SYMBOL              
                       AND YEAR(TIMESTAMP) = YEAR(CURRENT DATE) )  
                   THEN 'High'                                    
                WHEN NEWQUOTE.QUOTE <=                            
                      (SELECT MIN(QUOTE) FROM QUOTEHISTORY        
                       WHERE SYMBOL = NEWQUOTE.SYMBOL             
                       AND YEAR(TIMESTAMP) = YEAR(CURRENT DATE) ) 
                   THEN 'Low'                                     
                WHEN NEWQUOTE.QUOTE > OLDQUOTE.QUOTE              
                   THEN 'Rising'                                  
                WHEN NEWQUOTE.QUOTE < OLDQUOTE.QUOTE              
                   THEN 'Dropping'                                
                WHEN NEWQUOTE.QUOTE = OLDQUOTE.QUOTE              
                   THEN 'Steady'                                  
             END;                                                 
      

CREATE TRIGGER RECORD_HISTORY                            
       AFTER UPDATE OF QUOTE ON CURRENTQUOTE             
       REFERENCING NEW AS NEWQUOTE                       
       FOR EACH ROW MODE DB2SQL                          
          INSERT INTO QUOTEHISTORY                                  
          VALUES (NEWQUOTE.SYMBOL,NEWQUOTE.QUOTE,CURRENT TIMESTAMP);

update currentquote set quote =68.25 where symbol='IBM';

select * from currentquote;

update currentquote set quote =68.75 where symbol='IBM';

select * from currentquote;

update currentquote set quote =68.5 where symbol='IBM';

select * from currentquote;

update currentquote set quote =68.5 where symbol='IBM';

select * from currentquote;

update currentquote set quote =68.62 where symbol='IBM';

select * from currentquote;

update currentquote set quote =68 where symbol='IBM';

select * from currentquote;

select * from quotehistory;

drop trigger record_history;

drop trigger stock_status;

drop table currentquote;

drop table quotehistory;

