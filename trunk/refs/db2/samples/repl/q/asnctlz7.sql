--****************************************************************
--*                                                              *
--*    IBM DB2 Information Integrator Replication Version 9.1    *
--*    for zOS (5655-I60)                                        *
--*                                                              *
--*    Sample Q Replication control tables for zOS               *
--*    Licensed Materials - Property of IBM                      *
--*                                                              *
--*    (C) Copyright IBM Corp. 1993, 2006. All Rights Reserved   *
--*                                                              *
--*    US Government Users Restricted Rights - Use, duplication  *
--*    or disclosure restricted by GSA ADP Schedule Contract     *
--*    with IBM Corp.                                            *
--****************************************************************
--* This is an example of creating Q Replication
--* control tables.
--* Connect to DB2 z/OS sub system and run the script
--*
--************************************************************
--*Note:
--*
--*  This SQL script is created with the assumption that the
--*  databases in which the control tables are defined are running
--*  under DB2 Universal Database for OS/390 and z/OS Version 7 or
--*  Version 8 in Compatibility Mode (CM).
--*
--*  In Version 8 DB2 Universal Database for OS/390 and z/OS running
--*  in New-Function Mode (NFM), the maximum lengths of some of the
--*  database identifiers have been increased. If this script is
--*  used to create replication control tables on a subsystem under
--*  the New-Function Mode and you want the support of long names
--*  in DB2 Replication, some of the control table columns need to
--*  be modified according to the information provided in the
--*  following table.
--*
--*  Table Name
--*          Column                   V8 NFM          V7, V8 CM
--*  ------------------------------------------------------------
--*  IBMQREP_SRC_COLS
--*          SRC_COLNAME              VARCHAR(128)    VARCHAR(30)
--*
--*  IBMQREP_TARGETS
--*          SOURCE_OWNER             VARCHAR(128)    VARCHAR(30)
--*          SOURCE_NAME              VARCHAR(128)    VARCHAR(18)
--*          TARGET_OWNER             VARCHAR(128)    VARCHAR(30)
--*          TARGET_NAME              VARCHAR(128)    VARCHAR(18)
--*
--*  IBMQREP_TRG_COLS
--*          TARGET_COLNAME           VARCHAR(128)    VARCHAR(30)
--*
--*  IBMQREP_SAVERI
--*          TABSCHEMA                VARCHAR(128)    VARCHAR(30)
--*          TABNAME                  VARCHAR(128)    VARCHAR(18)
--*          REFTABSCHEMA             VARCHAR(128)    VARCHAR(30)
--*          REFTABNAME               VARCHAR(128)    VARCHAR(18)
--*
--*  If you are on Version 8 New-Function Mode or later release,
--*  you can change the script to use the keyword VOLATILE
--*  CARDINALITY in the CREATE TABLE statements for the control
--*  tables with index defined. By declaring the control tables
--*  VOLATILE, you can avoid possible table scan on the control
--*  tables due to outdated statistics on the tables.
--*
--*
--*  Create database QCNTL for Q Control tables.
--*  Locate and change all occurrences of QCNTL
--*  if you want to use a different database name.
--*  Locate and change all occurrences of STOGROUP DPROSTG
--*  to a stogroup name of your choice.
--*
--************************************************************
--DROP DATABASE QCNTL;

COMMIT;

CREATE DATABASE QCNTL
                CCSID EBCDIC
                BUFFERPOOL BP0
                STOGROUP DPROSTG;

CREATE TABLESPACE QCNTLP IN QCNTL
  USING STOGROUP DPROSTG
  PRIQTY 100
  SECQTY 100
  SEGSIZE 4
  BUFFERPOOL BP4
  LOCKSIZE PAGE
  CLOSE NO
  CCSID EBCDIC;

CREATE TABLESPACE QCNTLR IN QCNTL
  USING STOGROUP DPROSTG
  PRIQTY 100
  SECQTY 100
  SEGSIZE 4
  BUFFERPOOL BP4
  LOCKSIZE ROW
  CLOSE NO
  CCSID EBCDIC;


-- In this example Capture schema name is QASN
-- Pl change the schema name to your Capture schema name

CREATE TABLE QASN.IBMQREP_CAPPARMS
( QMGR VARCHAR(48) NOT NULL,
 REMOTE_SRC_SERVER VARCHAR(18),
 RESTARTQ VARCHAR(48) NOT NULL,
 ADMINQ VARCHAR(48) NOT NULL,
 STARTMODE VARCHAR(6) NOT NULL WITH DEFAULT 'WARMSI',
 MEMORY_LIMIT INTEGER NOT NULL WITH DEFAULT 500,
 COMMIT_INTERVAL INTEGER NOT NULL WITH DEFAULT 500,
 AUTOSTOP CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 MONITOR_INTERVAL INTEGER NOT NULL WITH DEFAULT 300000,
 MONITOR_LIMIT INTEGER NOT NULL WITH DEFAULT 10080,
 TRACE_LIMIT INTEGER NOT NULL WITH DEFAULT 10080,
 SIGNAL_LIMIT INTEGER NOT NULL WITH DEFAULT 10080,
 PRUNE_INTERVAL INTEGER NOT NULL WITH DEFAULT 300,
 SLEEP_INTERVAL INTEGER NOT NULL WITH DEFAULT 5000,
 LOGREUSE CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 LOGSTDOUT CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 TERM CHARACTER(1) NOT NULL WITH DEFAULT 'Y',
 CAPTURE_PATH VARCHAR(1040) WITH DEFAULT NULL,
 ARCH_LEVEL CHARACTER(4) NOT NULL WITH DEFAULT '0901',
 COMPATIBILITY CHARACTER(4) NOT NULL WITH DEFAULT '0901'
)  IN QCNTL.QCNTLP;


CREATE UNIQUE INDEX QASN.IX1CQMGRCOL ON QASN.IBMQREP_CAPPARMS
( QMGR ASC);

CREATE TABLE QASN.IBMQREP_SENDQUEUES
( PUBQMAPNAME VARCHAR(128) NOT NULL,
 SENDQ VARCHAR(48) NOT NULL,
 RECVQ VARCHAR(48),
 MESSAGE_FORMAT CHARACTER(1) NOT NULL WITH DEFAULT 'C',
 MSG_CONTENT_TYPE CHARACTER(1) NOT NULL WITH DEFAULT 'T',
 STATE CHARACTER(1) NOT NULL WITH DEFAULT 'A',
 STATE_TIME TIMESTAMP NOT NULL WITH DEFAULT,
 STATE_INFO CHARACTER(8),
 ERROR_ACTION CHARACTER(1) NOT NULL WITH DEFAULT 'S',
 HEARTBEAT_INTERVAL INTEGER NOT NULL WITH DEFAULT 60,
 MAX_MESSAGE_SIZE INTEGER NOT NULL WITH DEFAULT 64,
 APPLY_SERVER VARCHAR(18),
 APPLY_ALIAS VARCHAR(8),
 APPLY_SCHEMA VARCHAR(128),
 DESCRIPTION VARCHAR(254),
 MESSAGE_CODEPAGE INTEGER,
 PRIMARY KEY(SENDQ)
)  IN QCNTL.QCNTLR;

CREATE UNIQUE INDEX QASN.IX1PUBMAPCOL ON QASN.IBMQREP_SENDQUEUES
( PUBQMAPNAME ASC);

CREATE UNIQUE INDEX QASN.PKIBMQREP_SENDQUE ON
 QASN.IBMQREP_SENDQUEUES
( SENDQ);

CREATE TABLE QASN.IBMQREP_SUBS
( SUBNAME VARCHAR(132) NOT NULL,
 SOURCE_OWNER VARCHAR(128) NOT NULL,
 SOURCE_NAME VARCHAR(128) NOT NULL,
 TARGET_SERVER VARCHAR(18),
 TARGET_ALIAS VARCHAR(8),
 TARGET_OWNER VARCHAR(128),
 TARGET_NAME VARCHAR(128),
 TARGET_TYPE INTEGER,
 APPLY_SCHEMA VARCHAR(128),
 SENDQ VARCHAR(48) NOT NULL,
 SEARCH_CONDITION VARCHAR(2048) WITH DEFAULT NULL,
 SUB_ID INTEGER WITH DEFAULT NULL,
 SUBTYPE CHARACTER(1) NOT NULL WITH DEFAULT 'U',
 ALL_CHANGED_ROWS CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 BEFORE_VALUES CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 CHANGED_COLS_ONLY CHARACTER(1) NOT NULL WITH DEFAULT 'Y',
 HAS_LOADPHASE CHARACTER(1) NOT NULL WITH DEFAULT 'I',
 STATE CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 STATE_TIME TIMESTAMP NOT NULL WITH DEFAULT,
 STATE_INFO CHARACTER(8),
 STATE_TRANSITION VARCHAR(256) FOR BIT DATA,
 SUBGROUP VARCHAR(30) WITH DEFAULT NULL,
 SOURCE_NODE SMALLINT NOT NULL WITH DEFAULT 0,
 TARGET_NODE SMALLINT NOT NULL WITH DEFAULT 0,
 GROUP_MEMBERS CHARACTER(254) FOR BIT DATA WITH DEFAULT NULL,
 OPTIONS_FLAG CHARACTER(4) NOT NULL WITH DEFAULT 'NNNN',
 SUPPRESS_DELETES CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 DESCRIPTION VARCHAR(200),
 TOPIC VARCHAR(256),
 PRIMARY KEY(SUBNAME),
 CONSTRAINT FKSENDQ FOREIGN KEY(SENDQ) REFERENCES
 QASN.IBMQREP_SENDQUEUES(SENDQ)
)  IN QCNTL.QCNTLR;

CREATE UNIQUE INDEX QASN.PKIBMQREP_SUBS ON QASN.IBMQREP_SUBS
( SUBNAME);

CREATE TABLE QASN.IBMQREP_SRC_COLS
( SUBNAME VARCHAR(132) NOT NULL,
 SRC_COLNAME VARCHAR(30) NOT NULL,
 IS_KEY SMALLINT NOT NULL WITH DEFAULT 0,
 COL_OPTIONS_FLAG CHARACTER(10) NOT NULL WITH DEFAULT 'NNNNNNNNNN',
 PRIMARY KEY(SUBNAME, SRC_COLNAME),
 CONSTRAINT FKSUBS FOREIGN KEY(SUBNAME) REFERENCES
 QASN.IBMQREP_SUBS(SUBNAME)
)  IN QCNTL.QCNTLP;

CREATE UNIQUE INDEX QASN.PKIBMQREP_SRC_COLS ON
 QASN.IBMQREP_SRC_COLS
( SUBNAME, SRC_COLNAME);

CREATE TABLE QASN.IBMQREP_SRCH_COND
( ASNQREQD INTEGER
)  IN QCNTL.QCNTLP;

CREATE TABLE QASN.IBMQREP_SIGNAL
( SIGNAL_TIME TIMESTAMP NOT NULL WITH DEFAULT,
 SIGNAL_TYPE VARCHAR(30) NOT NULL,
 SIGNAL_SUBTYPE VARCHAR(30),
 SIGNAL_INPUT_IN VARCHAR(500),
 SIGNAL_STATE CHARACTER(1) NOT NULL WITH DEFAULT 'P',
 SIGNAL_LSN CHARACTER(10) FOR BIT DATA
)  IN QCNTL.QCNTLR
 DATA CAPTURE CHANGES;

CREATE TABLE QASN.IBMQREP_CAPTRACE
( OPERATION CHARACTER(8) NOT NULL,
 TRACE_TIME TIMESTAMP NOT NULL,
 DESCRIPTION VARCHAR(1024) NOT NULL
)  IN QCNTL.QCNTLR;

CREATE TABLE QASN.IBMQREP_CAPMON
( MONITOR_TIME TIMESTAMP NOT NULL,
 CURRENT_LOG_TIME TIMESTAMP NOT NULL,
 CAPTURE_IDLE INTEGER NOT NULL,
 CURRENT_MEMORY INTEGER NOT NULL,
 ROWS_PROCESSED INTEGER NOT NULL,
 TRANS_SKIPPED INTEGER NOT NULL,
 TRANS_PROCESSED INTEGER NOT NULL,
 TRANS_SPILLED INTEGER NOT NULL,
 MAX_TRANS_SIZE INTEGER NOT NULL,
 QUEUES_IN_ERROR INTEGER NOT NULL,
 RESTART_SEQ CHARACTER(10) FOR BIT DATA NOT NULL,
 CURRENT_SEQ CHARACTER(10) FOR BIT DATA NOT NULL,
 LAST_EOL_TIME TIMESTAMP,
 PRIMARY KEY(MONITOR_TIME)
)  IN QCNTL.QCNTLP;


CREATE UNIQUE INDEX QASN.PKIBMQREP_CAPMON ON QASN.IBMQREP_CAPMON
( MONITOR_TIME);

CREATE TABLE QASN.IBMQREP_CAPQMON
( MONITOR_TIME TIMESTAMP NOT NULL,
 SENDQ VARCHAR(48) NOT NULL,
 ROWS_PUBLISHED INTEGER NOT NULL,
 TRANS_PUBLISHED INTEGER NOT NULL,
 CHG_ROWS_SKIPPED INTEGER NOT NULL,
 DELROWS_SUPPRESSED INTEGER NOT NULL,
 ROWS_SKIPPED INTEGER NOT NULL,
 PRIMARY KEY(MONITOR_TIME, SENDQ)
)  IN QCNTL.QCNTLP;


CREATE UNIQUE INDEX QASN.PKIBMQREP_CAPQMON ON
 QASN.IBMQREP_CAPQMON
( MONITOR_TIME, SENDQ);

CREATE TABLE QASN.IBMQREP_CAPENQ
( LOCKNAME INTEGER)  IN QCNTL.QCNTLP;

CREATE TABLE QASN.IBMQREP_ADMINMSG
( MQMSGID CHARACTER(24) FOR BIT DATA NOT NULL,
 MSG_TIME TIMESTAMP NOT NULL WITH DEFAULT,
 PRIMARY KEY(MQMSGID)
)  IN QCNTL.QCNTLP;

CREATE UNIQUE INDEX QASN.PKIBMQREP_ADMINMSG ON
 QASN.IBMQREP_ADMINMSG
( MQMSGID);


------------------------------------------------------------------
--   Tables to ignore transactions    (All IBM platforms)
--   Tables names start with IBMQREP
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_IGNTRAN
( AUTHID CHARACTER(128),
 AUTHTOKEN CHARACTER(30),
 PLANNAME CHARACTER(8)
)  IN QCNTL.QCNTLR;

CREATE TABLE QASN.IBMQREP_IGNTRANTRC
( IGNTRAN_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 AUTHID CHARACTER(128),
 AUTHTOKEN CHARACTER(30),
 PLANNAME CHARACTER(8),
 TRANSID CHARACTER(10) FOR BIT DATA NOT NULL,
 COMMITLSN CHARACTER(10) FOR BIT DATA NOT NULL
)  IN QCNTL.QCNTLR;

------------------------------------------------------------------
--   New version tables for V9         (All platforms)
--   Tables names start with IBMQREP
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_TABVERSION
( LSN CHARACTER(10) FOR BIT DATA NOT NULL,
 TABLEID1 SMALLINT NOT NULL,
 TABLEID2 SMALLINT NOT NULL,
 VERSION INTEGER NOT NULL,
 SOURCE_OWNER VARCHAR(128) NOT NULL,
 SOURCE_NAME VARCHAR(128) NOT NULL
)  IN QCNTL.QCNTLP;

CREATE UNIQUE INDEX QASN.IBMQREP_TABVERSIOX ON
 QASN.IBMQREP_TABVERSION
( LSN, TABLEID1, TABLEID2, VERSION);


CREATE TABLE QASN.IBMQREP_COLVERSION
( LSN CHARACTER(10) FOR BIT DATA NOT NULL,
 TABLEID1 SMALLINT NOT NULL,
 TABLEID2 SMALLINT NOT NULL,
 POSITION SMALLINT NOT NULL,
 NAME     VARCHAR(128) NOT NULL,
 TYPE     SMALLINT NOT NULL,
 LENGTH   INTEGER NOT NULL,
 NULLS    CHARACTER(1) NOT NULL,
 "DEFAULT" VARCHAR(1536)
)  IN QCNTL.QCNTLP;


CREATE UNIQUE INDEX QASN.IBMQREP_COLVERSIOX ON
 QASN.IBMQREP_COLVERSION
( LSN, TABLEID1, TABLEID2, POSITION);

------------------------------------------------------------------
--    Insert to CAPPARMS table          (All platforms)
------------------------------------------------------------------

INSERT INTO QASN.IBMQREP_CAPPARMS
 (QMGR, RESTARTQ, ADMINQ, STARTMODE, MEMORY_LIMIT, COMMIT_INTERVAL,
 AUTOSTOP, MONITOR_INTERVAL, MONITOR_LIMIT, TRACE_LIMIT, SIGNAL_LIMIT,
 PRUNE_INTERVAL, SLEEP_INTERVAL, LOGREUSE, LOGSTDOUT, TERM, ARCH_LEVEL
, COMPATIBILITY)
 VALUES
('CSQ1', 'IBMQREP.QASN.RESTARTQ', 'IBMQREP.QASN.ADMINQ', 'WARMSI', 500, 500, 'N',
 300000, 10080, 10080, 10080, 300, 5000, 'N', 'N', 'Y', '0901', '0901'
);


-- In this example Apply schema name is QASN
-- Pl change the schema name to your Apply schema name

CREATE TABLESPACE QANTLP IN QCNTL
  USING STOGROUP DPROSTG
  PRIQTY 100
  SECQTY 100
  SEGSIZE 4
  BUFFERPOOL BP4
  LOCKSIZE PAGE
  CLOSE NO
  CCSID EBCDIC;

CREATE TABLESPACE QANTLR IN QCNTL
  USING STOGROUP DPROSTG
  PRIQTY 100
  SECQTY 100
  SEGSIZE 4
  BUFFERPOOL BP4
  LOCKSIZE ROW
  CLOSE NO
  CCSID EBCDIC;

CREATE TABLE QASN.IBMQREP_APPLYPARMS
( QMGR VARCHAR(48) NOT NULL,
 MONITOR_LIMIT INTEGER NOT NULL WITH DEFAULT 10080,
 TRACE_LIMIT INTEGER NOT NULL WITH DEFAULT 10080,
 MONITOR_INTERVAL INTEGER NOT NULL WITH DEFAULT 300000,
 PRUNE_INTERVAL INTEGER NOT NULL WITH DEFAULT 300,
 AUTOSTOP CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 LOGREUSE CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 LOGSTDOUT CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 APPLY_PATH VARCHAR(1040) WITH DEFAULT NULL,
 ARCH_LEVEL CHARACTER(4) NOT NULL WITH DEFAULT '0901',
 TERM CHARACTER(1) NOT NULL WITH DEFAULT 'Y',
 PWDFILE VARCHAR(48) WITH DEFAULT NULL,
 DEADLOCK_RETRIES INTEGER NOT NULL WITH DEFAULT 3,
 SQL_CAP_SCHEMA VARCHAR(128) WITH DEFAULT NULL
)  IN QCNTL.QANTLP;

CREATE UNIQUE INDEX QASN.IX1AQMGRCOL ON QASN.IBMQREP_APPLYPARMS
( QMGR ASC);

CREATE TABLE QASN.IBMQREP_RECVQUEUES
( REPQMAPNAME VARCHAR(128) NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 SENDQ VARCHAR(48) WITH DEFAULT NULL,
 ADMINQ VARCHAR(48) NOT NULL,
 NUM_APPLY_AGENTS INTEGER NOT NULL WITH DEFAULT 16,
 MEMORY_LIMIT INTEGER NOT NULL WITH DEFAULT 64,
 CAPTURE_SERVER VARCHAR(18) NOT NULL,
 CAPTURE_ALIAS VARCHAR(8) NOT NULL,
 CAPTURE_SCHEMA VARCHAR(128) NOT NULL WITH DEFAULT 'ASN',
 STATE CHARACTER(1) NOT NULL WITH DEFAULT 'A',
 STATE_TIME TIMESTAMP NOT NULL WITH DEFAULT,
 STATE_INFO CHARACTER(8),
 DESCRIPTION VARCHAR(254), 
 SOURCE_TYPE CHAR(1) WITH DEFAULT ' ',
 PRIMARY KEY(RECVQ) )  IN QCNTL.QANTLR;

CREATE UNIQUE INDEX QASN.IX1REPMAPCOL ON QASN.IBMQREP_RECVQUEUES
( REPQMAPNAME ASC);

CREATE UNIQUE INDEX QASN.PKIBMQREP_RECVQUE ON
 QASN.IBMQREP_RECVQUEUES
( RECVQ);

CREATE TABLE QASN.IBMQREP_TARGETS
( SUBNAME VARCHAR(132) NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 SUB_ID INTEGER WITH DEFAULT NULL,
 SOURCE_SERVER VARCHAR(18) NOT NULL,
 SOURCE_ALIAS VARCHAR(8) NOT NULL,
 SOURCE_OWNER VARCHAR(30) NOT NULL,
 SOURCE_NAME VARCHAR(18) NOT NULL,
 SRC_NICKNAME_OWNER VARCHAR(128),
 SRC_NICKNAME VARCHAR(128),
 TARGET_OWNER VARCHAR(30) NOT NULL,
 TARGET_NAME VARCHAR(18) NOT NULL,
 TARGET_TYPE INTEGER NOT NULL WITH DEFAULT 1,
 FEDERATED_TGT_SRVR VARCHAR(18) WITH DEFAULT NULL,
 STATE CHARACTER(1) NOT NULL WITH DEFAULT 'I',
 STATE_TIME TIMESTAMP NOT NULL WITH DEFAULT,
 STATE_INFO CHARACTER(8),
 SUBTYPE CHARACTER(1) NOT NULL WITH DEFAULT 'U',
 CONFLICT_RULE CHARACTER(1) NOT NULL WITH DEFAULT 'K',
 CONFLICT_ACTION CHARACTER(1) NOT NULL WITH DEFAULT 'I',
 ERROR_ACTION CHARACTER(1) NOT NULL WITH DEFAULT 'Q',
 SPILLQ VARCHAR(48) WITH DEFAULT NULL,
 OKSQLSTATES VARCHAR(128) WITH DEFAULT NULL,
 SUBGROUP VARCHAR(30) WITH DEFAULT NULL,
 SOURCE_NODE SMALLINT NOT NULL WITH DEFAULT 0,
 TARGET_NODE SMALLINT NOT NULL WITH DEFAULT 0,
 GROUP_INIT_ROLE CHARACTER(1) WITH DEFAULT NULL,
 HAS_LOADPHASE CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 LOAD_TYPE SMALLINT NOT NULL WITH DEFAULT 0,
 DESCRIPTION VARCHAR(254),
 SEARCH_CONDITION VARCHAR(2048) WITH DEFAULT NULL,
 MODELQ VARCHAR(36) NOT NULL WITH DEFAULT 'IBMQREP.SPILL.MODELQ',
 CCD_CONDENSED CHARACTER(1) WITH DEFAULT 'Y',
 CCD_COMPLETE CHARACTER(1) WITH DEFAULT 'Y',
 SOURCE_TYPE   CHAR(1) WITH DEFAULT ' ' 
)  IN QCNTL.QANTLR;

CREATE UNIQUE INDEX QASN.IX1TARGETS ON QASN.IBMQREP_TARGETS
( SUBNAME ASC, RECVQ ASC);

CREATE UNIQUE INDEX QASN.IX2TARGETS ON QASN.IBMQREP_TARGETS
( TARGET_OWNER ASC,
 TARGET_NAME ASC,
 RECVQ ASC,
 SOURCE_OWNER ASC,
 SOURCE_NAME ASC);

CREATE INDEX QASN.IX3TARGETS ON QASN.IBMQREP_TARGETS
( RECVQ ASC,
 SUB_ID ASC);

CREATE TABLE QASN.IBMQREP_TRG_COLS
( RECVQ VARCHAR(48) NOT NULL,
 SUBNAME VARCHAR(132) NOT NULL,
 SOURCE_COLNAME VARCHAR(254) NOT NULL,
 TARGET_COLNAME VARCHAR(30) NOT NULL,
 TARGET_COLNO INTEGER WITH DEFAULT NULL,
 MSG_COL_CODEPAGE INTEGER WITH DEFAULT NULL,
 MSG_COL_NUMBER SMALLINT WITH DEFAULT NULL,
 MSG_COL_TYPE SMALLINT WITH DEFAULT NULL,
 MSG_COL_LENGTH INTEGER WITH DEFAULT NULL,
 IS_KEY CHARACTER(1) NOT NULL,
 MAPPING_TYPE CHARACTER(1) WITH DEFAULT NULL,
 SRC_COL_MAP VARCHAR(2000) WITH DEFAULT NULL,
 BEF_TARG_COLNAME VARCHAR(128) WITH DEFAULT NULL
)  IN QCNTL.QANTLP;

CREATE UNIQUE INDEX QASN.IX1TRGCOL ON QASN.IBMQREP_TRG_COLS
( RECVQ ASC,
 SUBNAME ASC,
 TARGET_COLNAME ASC);

CREATE TABLE QASN.IBMQREP_SPILLQS
( SPILLQ VARCHAR(48) NOT NULL,
 SUBNAME VARCHAR(132) NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 PRIMARY KEY(SPILLQ)
)  IN QCNTL.QANTLP;

CREATE UNIQUE INDEX QASN.PKIBMQREP_SPILLQS ON
 QASN.IBMQREP_SPILLQS ( SPILLQ);

CREATE TABLE QASN.IBMQREP_APPLYTRACE
( OPERATION CHARACTER(8) NOT NULL,
 TRACE_TIME TIMESTAMP NOT NULL,
 DESCRIPTION VARCHAR(1024) NOT NULL
)  IN QCNTL.QANTLR;

CREATE INDEX QASN.IX1TRCTMCOL ON QASN.IBMQREP_APPLYTRACE
( TRACE_TIME ASC);

CREATE TABLE QASN.IBMQREP_APPLYMON
( MONITOR_TIME TIMESTAMP NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 QSTART_TIME TIMESTAMP NOT NULL,
 CURRENT_MEMORY INTEGER NOT NULL,
 QDEPTH INTEGER NOT NULL,
 END2END_LATENCY INTEGER NOT NULL,
 QLATENCY INTEGER NOT NULL,
 APPLY_LATENCY INTEGER NOT NULL,
 TRANS_APPLIED INTEGER NOT NULL,
 ROWS_APPLIED INTEGER NOT NULL,
 TRANS_SERIALIZED INTEGER NOT NULL,
 RI_DEPENDENCIES INTEGER NOT NULL,
 RI_RETRIES INTEGER NOT NULL,
 DEADLOCK_RETRIES INTEGER NOT NULL,
 ROWS_NOT_APPLIED INTEGER NOT NULL,
 MONSTER_TRANS INTEGER NOT NULL,
 MEM_FULL_TIME INTEGER NOT NULL,
 APPLY_SLEEP_TIME INTEGER NOT NULL,
 SPILLED_ROWS INTEGER NOT NULL,
 SPILLEDROWSAPPLIED INTEGER NOT NULL,
 OLDEST_TRANS TIMESTAMP NOT NULL,
 OKSQLSTATE_ERRORS INTEGER NOT NULL,
 HEARTBEAT_LATENCY INTEGER NOT NULL,
 KEY_DEPENDENCIES INTEGER NOT NULL,
 UNIQ_DEPENDENCIES INTEGER NOT NULL,
 UNIQ_RETRIES INTEGER NOT NULL,
 OLDEST_INFLT_TRANS TIMESTAMP,
 PRIMARY KEY(MONITOR_TIME, RECVQ)
)  IN QCNTL.QANTLP;

CREATE UNIQUE INDEX QASN.PKIBMQREP_APPLYMON ON
 QASN.IBMQREP_APPLYMON
( MONITOR_TIME, RECVQ);

CREATE TABLE QASN.IBMQREP_DONEMSG
( RECVQ VARCHAR(48) NOT NULL,
 MQMSGID CHARACTER(24) FOR BIT DATA NOT NULL,
 PRIMARY KEY(RECVQ, MQMSGID)
)  IN QCNTL.QANTLP;

CREATE UNIQUE INDEX QASN.PKIBMQREP_DONEMSG ON
 QASN.IBMQREP_DONEMSG
( RECVQ, MQMSGID);

CREATE TABLE QASN.IBMQREP_SPILLEDROW
( SPILLQ VARCHAR(48) NOT NULL,
 MQMSGID CHARACTER(24) FOR BIT DATA NOT NULL,
 PRIMARY KEY(SPILLQ, MQMSGID)
)  IN QCNTL.QANTLR;

CREATE UNIQUE INDEX QASN.PKIBMQREP_SPILLED ON
 QASN.IBMQREP_SPILLEDROW
( SPILLQ, MQMSGID);

CREATE TABLE QASN.IBMQREP_SAVERI
( SUBNAME VARCHAR(132) NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 CONSTNAME VARCHAR(128) NOT NULL,
 TABSCHEMA VARCHAR(30) NOT NULL,
 TABNAME VARCHAR(18) NOT NULL,
 REFTABSCHEMA VARCHAR(30) NOT NULL,
 REFTABNAME VARCHAR(18) NOT NULL,
 ALTER_RI_DDL VARCHAR(1680) NOT NULL,
 TYPE_OF_LOAD CHARACTER(1) NOT NULL,
 DELETERULE CHARACTER(1),
 UPDATERULE CHARACTER(1)
)  IN QCNTL.QANTLP;

CREATE TABLE QASN.IBMQREP_APPLYENQ
( LOCKNAME INTEGER)
 IN QCNTL.QANTLR;

CREATE LOB TABLESPACE LXTIBMQ2 IN QCNTL
  LOG NO;

CREATE TABLE QASN.IBMQREP_EXCEPTIONS
( EXCEPTION_TIME TIMESTAMP NOT NULL WITH DEFAULT,
 RECVQ VARCHAR(48) NOT NULL,
 SRC_COMMIT_LSN VARCHAR(48) FOR BIT DATA NOT NULL,
 SRC_TRANS_TIME TIMESTAMP NOT NULL,
 SUBNAME VARCHAR(132) NOT NULL,
 REASON CHARACTER(12) NOT NULL,
 SQLCODE INTEGER,
 SQLSTATE CHARACTER(5),
 SQLERRMC VARCHAR(70) FOR BIT DATA,
 OPERATION VARCHAR(18) NOT NULL,
 TEXT CLOB(32768) NOT NULL,
 IS_APPLIED CHARACTER(1) NOT NULL,
 CONFLICT_RULE CHARACTER(1),
 REPLROWID ROWID NOT NULL GENERATED BY DEFAULT
)  IN QCNTL.QANTLR;

CREATE UNIQUE INDEX QASN.RIIBMQREP_EXCEPTI ON
 QASN.IBMQREP_EXCEPTIONS ( REPLROWID);

INSERT INTO QASN.IBMQREP_APPLYPARMS
 (QMGR, MONITOR_LIMIT, TRACE_LIMIT, MONITOR_INTERVAL, PRUNE_INTERVAL,
 AUTOSTOP, LOGREUSE, LOGSTDOUT, ARCH_LEVEL, TERM, DEADLOCK_RETRIES)
 VALUES
 ('CSQ1', 10080, 10080, 300000, 300, 'N', 'N', 'N', '0901', 'Y', 3);

CREATE AUXILIARY TABLE QASN.XTIBMQREP_EXCEPTI
 IN QCNTL.LXTIBMQ2
 STORES QASN.IBMQREP_EXCEPTIONS COLUMN TEXT;

CREATE INDEX QASN.XIXTIBMQREP_EXCEP ON QASN.XTIBMQREP_EXCEPTI;

CREATE TABLESPACE QCNTLP2P IN QCNTL                                 
  USING STOGROUP DPROSTG                                            
  PRIQTY 100                                                        
  SECQTY 100                                                        
  BUFFERPOOL BP8K0                                                  
  SEGSIZE 4                                                         
  LOCKSIZE PAGE                                                     
  CCSID EBCDIC;                                                     
                                                                    
CREATE TABLE QASN.IBMQREP_DELTOMB (                                      
  TARGET_OWNER          VARCHAR(30) NOT NULL,                       
  TARGET_NAME           VARCHAR(18) NOT NULL,                       
  VERSION_TIME          TIMESTAMP NOT NULL,                         
  VERSION_NODE          SMALLINT NOT NULL,                          
  KEY_HASH              INT NOT NULL,                               
  PACKED_KEY            VARCHAR(4096) FOR BIT DATA NOT NULL         
) IN QCNTL.QCNTLP2P;                                                
                               
CREATE INDEX QASN.IX492306260               
ON QASN.IBMQREP_DELTOMB                     
( TARGET_NAME ASC,                     
  TARGET_OWNER ASC,                    
  VERSION_TIME DESC,                   
  VERSION_NODE ASC,                    
  KEY_HASH ASC);                                                            
