--********************************************************************/
--                                                                   */
--     IBM DB2 Information Integrator Replication Edition            */
--      Version 9.1 for Linux, UNIX AND Windows                      */
--                                                                   */
--     Sample Q Replication control tables for UNIX AND NT           */
--     Licensed Materials - Property of IBM                          */
--                                                                   */
--     (C) Copyright IBM Corp. 1993, 2006. All Rights Reserved       */
--                                                                   */
--     US Government Users Restricted Rights - Use, duplication      */
--     or disclosure restricted by GSA ADP Schedule Contract         */
--     with IBM Corp.                                                */
--                                                                   */
--********************************************************************/

------------------------------------------------------------------
--    Create QReplication Control Tables
--    (UDB edition)
------------------------------------------------------------------

-- BEGIN asnqctlw.sql

-- UDB -- For the UDB platform, follow the directions given in the comments
-- UDB -- prefixed with "-- UDB --" (if any).

-- UDB -- TABLESPACE CONSIDERATIONS:

-- UDB -- Uncomment the drop statements below only if you are sure that they do
-- UDB -- not contain any important user tables!!!

--DROP TABLESPACE TSQCAP1;
--DROP TABLESPACE TSQAPP1;

-- UDB -- We recommend the use of two tablespaces to contain Q replication
-- UDB -- control tables, with one tablespace containing the Capture control tables
-- UDB -- and another to contain the Apply control tables.

-- UDB -- For each database, customize the following tablespace parameters:
-- UDB -- 1. File container must be different for each database.  You must
-- UDB --    change the sample file container when running this script on
-- UDB --    Unix platforms, for example: "FILE '/tmp/TSQCAP1.f1'".
-- UDB -- 2. Increase page allocation for large replication installations.
-- UDB -- 3. After making the customization changes, uncomment the
-- UDB --    CREATE TABLESPACE statements below as well as the IN clause
-- UDB --    from the CREATE TABLE statements later in this script.

-- UDB -- Note: tablespace parameters correspond to "FILE 'C:\TSQCAP1.F1'"
-- UDB -- and "2000", respectively, in the following sample statement.

--CREATE TABLESPACE TSQCAP1 MANAGED BY DATABASE
--USING (FILE 'C:\TSQCAP1.F1' 2000);

-- UDB -- Note: tablespace parameters correspond to "FILE 'C:\TSQAPP1.F1'"
-- UDB -- and "2000", respectively, in the following sample statement.

--CREATE TABLESPACE TSQAPP1 MANAGED BY DATABASE
--USING (FILE 'C:\TSQAPP1.F1' 2000);


--********************************************************************/
-- Create Capture Control tables                                     */
-- In this sample the Capture_schema is QASN.
--********************************************************************/

-- connect to capture_server

------------------------------------------------------------------
--    CAPPARMS Table                 (All IBM platforms  )
------------------------------------------------------------------

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
)  IN TSQCAP1;

ALTER TABLE QASN.IBMQREP_CAPPARMS
 VOLATILE CARDINALITY;

CREATE UNIQUE INDEX QASN.IX1CQMGRCOL ON QASN.IBMQREP_CAPPARMS
( QMGR ASC);

------------------------------------------------------------------
--    SENDQUEUES Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_SENDQUEUES
( PUBQMAPNAME VARCHAR(128) NOT NULL,
 SENDQ VARCHAR(48) NOT NULL,
 RECVQ VARCHAR(48),
 MESSAGE_FORMAT CHARACTER(1) NOT NULL WITH DEFAULT 'C',
 MSG_CONTENT_TYPE CHARACTER(1) NOT NULL WITH DEFAULT 'T',
 STATE CHARACTER(1) NOT NULL WITH DEFAULT 'A',
 STATE_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
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
)  IN TSQCAP1;

ALTER TABLE QASN.IBMQREP_SENDQUEUES
 VOLATILE CARDINALITY;

CREATE UNIQUE INDEX QASN.IX1PUBMAPCOL ON QASN.IBMQREP_SENDQUEUES
( PUBQMAPNAME ASC);

------------------------------------------------------------------
--    SUBS Table                 (All IBM platforms  )
------------------------------------------------------------------

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
 STATE_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
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
)  IN TSQCAP1;

ALTER TABLE QASN.IBMQREP_SUBS
 VOLATILE CARDINALITY;

------------------------------------------------------------------
--    SRC_COLS Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_SRC_COLS
( SUBNAME VARCHAR(132) NOT NULL,
 SRC_COLNAME VARCHAR(128) NOT NULL,
 IS_KEY SMALLINT NOT NULL WITH DEFAULT 0,
 COL_OPTIONS_FLAG CHARACTER(10) NOT NULL WITH DEFAULT 'NNNNNNNNNN',
 PRIMARY KEY(SUBNAME, SRC_COLNAME),
 CONSTRAINT FKSUBS FOREIGN KEY(SUBNAME) REFERENCES
 QASN.IBMQREP_SUBS(SUBNAME)
)  IN TSQCAP1;

ALTER TABLE QASN.IBMQREP_SRC_COLS
 VOLATILE CARDINALITY;

------------------------------------------------------------------
--    SEARCH CONDITION Table      (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_SRCH_COND
( ASNQREQD INTEGER)  IN TSQCAP1;

------------------------------------------------------------------
--    SIGNAL Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_SIGNAL
( SIGNAL_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 SIGNAL_TYPE VARCHAR(30) NOT NULL,
 SIGNAL_SUBTYPE VARCHAR(30),
 SIGNAL_INPUT_IN VARCHAR(500),
 SIGNAL_STATE CHARACTER(1) NOT NULL WITH DEFAULT 'P',
 SIGNAL_LSN CHARACTER(10) FOR BIT DATA
)  DATA CAPTURE CHANGES   IN TSQCAP1;

ALTER TABLE QASN.IBMQREP_SIGNAL
 VOLATILE CARDINALITY;

------------------------------------------------------------------
--    CAPTRACE Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_CAPTRACE
( OPERATION CHARACTER(8) NOT NULL,
 TRACE_TIME TIMESTAMP NOT NULL,
 DESCRIPTION VARCHAR(1024) NOT NULL
)   IN TSQCAP1;

------------------------------------------------------------------
--    CAPMON Table                 (All IBM platforms  )
------------------------------------------------------------------

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
)  IN TSQCAP1;

ALTER TABLE QASN.IBMQREP_CAPMON
 VOLATILE CARDINALITY;

------------------------------------------------------------------
--    CAPQMON Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_CAPQMON
( MONITOR_TIME TIMESTAMP NOT NULL,
 SENDQ VARCHAR(48) NOT NULL,
 ROWS_PUBLISHED INTEGER NOT NULL,
 TRANS_PUBLISHED INTEGER NOT NULL,
 CHG_ROWS_SKIPPED INTEGER NOT NULL,
 DELROWS_SUPPRESSED INTEGER NOT NULL,
 ROWS_SKIPPED INTEGER NOT NULL,
 PRIMARY KEY(MONITOR_TIME, SENDQ)
)  IN TSQCAP1;

ALTER TABLE QASN.IBMQREP_CAPQMON
 VOLATILE CARDINALITY;

------------------------------------------------------------------
--    CAPENQ Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_CAPENQ
( LOCKNAME INTEGER)  IN TSQCAP1;

CREATE TABLE QASN.IBMQREP_ADMINMSG
( MQMSGID CHARACTER(24) FOR BIT DATA NOT NULL,
 MSG_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 PRIMARY KEY(MQMSGID)
)  IN TSQCAP1;

------------------------------------------------------------------
--    ADMINMSG Table                 (All IBM platforms  )
------------------------------------------------------------------

ALTER TABLE QASN.IBMQREP_ADMINMSG
 VOLATILE CARDINALITY;

------------------------------------------------------------------
--   Tables to ignore transactions    (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_IGNTRAN
( AUTHID CHARACTER(128),
 AUTHTOKEN CHARACTER(30),
 PLANNAME CHARACTER(8),
 IGNTRANTRC CHAR(1) NOT NULL DEFAULT 'Y'
)  IN TSQCAP1;

CREATE TABLE QASN.IBMQREP_IGNTRANTRC
( AUTHID CHARACTER(128),
 AUTHTOKEN CHARACTER(30),
 PLANNAME CHARACTER(8),
 TRANSID CHARACTER(10) FOR BIT DATA NOT NULL,
 COMMITLSN CHARACTER(10) FOR BIT DATA NOT NULL
)  IN TSQCAP1;

------------------------------------------------------------------
--   New version tables for V9         (All platforms)
--   Tables names start with IBMQREP
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_COLVERSION
( LSN            CHAR(10)     FOR BIT DATA NOT NULL,
  TABLEID1       SMALLINT                  NOT NULL,
  TABLEID2       SMALLINT                  NOT NULL,
  POSITION       SMALLINT                  NOT NULL,
  NAME           VARCHAR(128)              NOT NULL,
  TYPE           SMALLINT                  NOT NULL,
  LENGTH         INTEGER                   NOT NULL,
  NULLS          CHAR(1)                   NOT NULL,
  DEFAULT        VARCHAR(1536)
) IN TSQCAP1;

CREATE UNIQUE INDEX QASN.IBMQREP_COLVERSIOX
  ON QASN.IBMQREP_COLVERSION(
  LSN, TABLEID1, TABLEID2, POSITION);

CREATE TABLE QASN.IBMQREP_TABVERSION
(  LSN            CHAR(10)     FOR BIT DATA NOT NULL,
  TABLEID1       SMALLINT                  NOT NULL,
  TABLEID2       SMALLINT                  NOT NULL,
  VERSION        INTEGER                   NOT NULL,
  SOURCE_OWNER   VARCHAR(128)              NOT NULL,
  SOURCE_NAME    VARCHAR(128)              NOT NULL
) IN TSQCAP1;

CREATE UNIQUE INDEX QASN.IBMQREP_TABVERSIOX
  ON QASN.IBMQREP_TABVERSION(
  LSN, TABLEID1, TABLEID2, VERSION);


------------------------------------------------------------------
--    Insert to CAPPARMS table                (All IBM platforms  )
------------------------------------------------------------------

INSERT INTO QASN.IBMQREP_CAPPARMS
 (qmgr, restartq, adminq, startmode, memory_limit, commit_interval,
 autostop, monitor_interval, monitor_limit, trace_limit, signal_limit,
 prune_interval, sleep_interval, logreuse, logstdout, term, arch_level
, compatibility)  VALUES
 ('QM1', 'IBMQREP.ASN.RESTARTQ', 'IBMQREP.ASN.ADMINQ', 'WARMSI', 500, 500, 'N',
 300000, 10080, 10080, 10080, 300, 5000, 'N', 'N', 'Y', '0901', '0901'
);


--********************************************************************/
-- Create Apply Control tables                                       */
-- Apply schema for this sample is QASN.
-- You can use different schema name for QApply than QCapture.       */
--********************************************************************/

-- connect to apply_server

------------------------------------------------------------------
--    APPLYPARMS Table                 (All IBM platforms  )
------------------------------------------------------------------

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
)  IN TSQAPP1;

ALTER TABLE QASN.IBMQREP_APPLYPARMS
 VOLATILE CARDINALITY;

CREATE UNIQUE INDEX QASN.IX1AQMGRCOL ON QASN.IBMQREP_APPLYPARMS
( QMGR ASC);

------------------------------------------------------------------
--    RECVQUEUES Table                 (All IBM platforms  )
------------------------------------------------------------------

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
 STATE_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 STATE_INFO CHARACTER(8),
 DESCRIPTION VARCHAR(254),
 SOURCE_TYPE CHARACTER(1) WITH DEFAULT ' ',
 PRIMARY KEY(RECVQ)
)  IN TSQAPP1;

ALTER TABLE QASN.IBMQREP_RECVQUEUES
 VOLATILE CARDINALITY;

CREATE UNIQUE INDEX QASN.IX1REPMAPCOL ON QASN.IBMQREP_RECVQUEUES
( REPQMAPNAME ASC);

------------------------------------------------------------------
--    TARGETS Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_TARGETS
( SUBNAME VARCHAR(132) NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 SUB_ID INTEGER WITH DEFAULT NULL,
 SOURCE_SERVER VARCHAR(18) NOT NULL,
 SOURCE_ALIAS VARCHAR(8) NOT NULL,
 SOURCE_OWNER VARCHAR(128) NOT NULL,
 SOURCE_NAME VARCHAR(128) NOT NULL,
 SRC_NICKNAME_OWNER VARCHAR(128),
 SRC_NICKNAME VARCHAR(128),
 TARGET_OWNER VARCHAR(128) NOT NULL,
 TARGET_NAME VARCHAR(128) NOT NULL,
 TARGET_TYPE INTEGER NOT NULL WITH DEFAULT 1,
 FEDERATED_TGT_SRVR VARCHAR(18) WITH DEFAULT NULL,
 STATE CHARACTER(1) NOT NULL WITH DEFAULT 'I',
 STATE_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
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
 SOURCE_TYPE CHARACTER(1) WITH DEFAULT ' '
)  IN TSQAPP1;

ALTER TABLE QASN.IBMQREP_TARGETS
 VOLATILE CARDINALITY;

CREATE UNIQUE INDEX QASN.IX1TARGETS ON QASN.IBMQREP_TARGETS
( SUBNAME ASC, RECVQ ASC);

CREATE UNIQUE INDEX QASN.IX2TARGETS ON QASN.IBMQREP_TARGETS
( TARGET_OWNER ASC,
 TARGET_NAME ASC,
 RECVQ ASC,
 SOURCE_OWNER ASC,
 SOURCE_NAME ASC);

CREATE INDEX QASN.IX3TARGETS ON QASN.IBMQREP_TARGETS
( RECVQ ASC, SUB_ID ASC);

------------------------------------------------------------------
--    TRG_COLS Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_TRG_COLS
( RECVQ VARCHAR(48) NOT NULL,
 SUBNAME VARCHAR(132) NOT NULL,
 SOURCE_COLNAME VARCHAR(254) NOT NULL,
 TARGET_COLNAME VARCHAR(128) NOT NULL,
 TARGET_COLNO INTEGER WITH DEFAULT NULL,
 MSG_COL_CODEPAGE INTEGER WITH DEFAULT NULL,
 MSG_COL_NUMBER SMALLINT WITH DEFAULT NULL,
 MSG_COL_TYPE SMALLINT WITH DEFAULT NULL,
 MSG_COL_LENGTH INTEGER WITH DEFAULT NULL,
 IS_KEY CHARACTER(1) NOT NULL,
 MAPPING_TYPE CHARACTER(1) WITH DEFAULT NULL,
 SRC_COL_MAP VARCHAR(2000) WITH DEFAULT NULL,
 BEF_TARG_COLNAME VARCHAR(128) WITH DEFAULT NULL
)  IN TSQAPP1;

ALTER TABLE QASN.IBMQREP_TRG_COLS
 VOLATILE CARDINALITY;

CREATE UNIQUE INDEX QASN.IX1TRGCOL ON QASN.IBMQREP_TRG_COLS
( RECVQ ASC, SUBNAME ASC, TARGET_COLNAME ASC);

------------------------------------------------------------------
--    SPILLQS Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_SPILLQS
( SPILLQ VARCHAR(48) NOT NULL,
 SUBNAME VARCHAR(132) NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 PRIMARY KEY(SPILLQ)
)  IN TSQAPP1;

ALTER TABLE QASN.IBMQREP_SPILLQS
 VOLATILE CARDINALITY;

------------------------------------------------------------------
--    EXCEPTIONS Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_EXCEPTIONS
( EXCEPTION_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 RECVQ VARCHAR(48) NOT NULL,
 SRC_COMMIT_LSN VARCHAR(48) FOR BIT DATA NOT NULL,
 SRC_TRANS_TIME TIMESTAMP NOT NULL,
 SUBNAME VARCHAR(132) NOT NULL,
 REASON CHARACTER(12) NOT NULL,
 SQLCODE INTEGER,
 SQLSTATE CHARACTER(5),
 SQLERRMC VARCHAR(70) FOR BIT DATA,
 OPERATION VARCHAR(18) NOT NULL,
 TEXT CLOB(32768) NOT LOGGED NOT COMPACT NOT NULL,
 IS_APPLIED CHARACTER(1) NOT NULL,
 CONFLICT_RULE CHARACTER(1)
)  IN TSQAPP1;

------------------------------------------------------------------
--    APPLYTRACE Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_APPLYTRACE
( OPERATION CHARACTER(8) NOT NULL,
 TRACE_TIME TIMESTAMP NOT NULL,
 DESCRIPTION VARCHAR(1024) NOT NULL
)  IN TSQAPP1;

ALTER TABLE QASN.IBMQREP_APPLYTRACE
 VOLATILE CARDINALITY;

CREATE INDEX QASN.IX1TRCTMCOL ON QASN.IBMQREP_APPLYTRACE
( TRACE_TIME ASC);

------------------------------------------------------------------
--    APPLYMON Table                 (All IBM platforms  )
------------------------------------------------------------------

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
)  IN TSQAPP1;

ALTER TABLE QASN.IBMQREP_APPLYMON
 VOLATILE CARDINALITY;

------------------------------------------------------------------
--    DONEMSG Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_DONEMSG
(RECVQ VARCHAR(48) NOT NULL,
 MQMSGID CHARACTER(24) FOR BIT DATA NOT NULL,
 PRIMARY KEY(RECVQ, MQMSGID)
)  IN TSQAPP1;

ALTER TABLE QASN.IBMQREP_DONEMSG
 VOLATILE CARDINALITY  APPEND ON;

------------------------------------------------------------------
--    SPILLEDROW Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_SPILLEDROW
( SPILLQ VARCHAR(48) NOT NULL,
 MQMSGID CHARACTER(24) FOR BIT DATA NOT NULL,
 PRIMARY KEY(SPILLQ, MQMSGID)
)  IN TSQAPP1;

ALTER TABLE QASN.IBMQREP_SPILLEDROW
 VOLATILE CARDINALITY;

------------------------------------------------------------------
--    SAVERI Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_SAVERI
( SUBNAME VARCHAR(132) NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 CONSTNAME VARCHAR(128) NOT NULL,
 TABSCHEMA VARCHAR(128) NOT NULL,
 TABNAME VARCHAR(128) NOT NULL,
 REFTABSCHEMA VARCHAR(128) NOT NULL,
 REFTABNAME VARCHAR(128) NOT NULL,
 ALTER_RI_DDL VARCHAR(1680) NOT NULL,
 TYPE_OF_LOAD CHARACTER(1) NOT NULL,
 DELETERULE CHARACTER(1),
 UPDATERULE CHARACTER(1)
)  IN TSQAPP1;

ALTER TABLE QASN.IBMQREP_SAVERI
 VOLATILE CARDINALITY;

------------------------------------------------------------------
--    APPLYENQ Table                 (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE QASN.IBMQREP_APPLYENQ
( LOCKNAME INTEGER)  IN TSQAPP1;


------------------------------------------------------------------
--    Insert to APPLYPARMS Table            (All IBM platforms  )
--    Please change the QMGR name from QM2 to your QMGR name
------------------------------------------------------------------


INSERT INTO QASN.IBMQREP_APPLYPARMS
 (qmgr, monitor_limit, trace_limit, monitor_interval, prune_interval,
 autostop, logreuse, logstdout, arch_level, term, deadlock_retries)
 VALUES
 ('QM2', 10080, 10080, 300000, 300, 'N', 'N', 'N', '0901', 'Y', 3);

------------------------------------------------------------------
 -- Internal table used to record conflicting deletes in P2P.
 -- You need to create this table only for P2P setup.
 -- This table needs to be in a 8K bufferpool or higher.
 --
 ------------------------------------------------------------------
--create bufferpool BP8K0  size 500  pagesiZe 8K;

--CREATE TABLESPACE TSQDELT PAGESIZE 8K MANAGED BY DATABASE
--USING (FILE 'C:\TSQDELT.F1' 500 ) BUFFERPOOL BP8K0;

CREATE TABLE QASN.IBMQREP_DELTOMB
( TARGET_OWNER          VARCHAR(30) NOT NULL,
  TARGET_NAME           VARCHAR(18) NOT NULL,
  VERSION_TIME          TIMESTAMP NOT NULL,
  VERSION_NODE          SMALLINT NOT NULL,
  KEY_HASH              INTEGER NOT NULL,
  PACKED_KEY            VARCHAR(4096) FOR BIT DATA NOT NULL
) IN TSQDELT;

CREATE INDEX QASN.IX492306260 ON QASN.IBMQREP_DELTOMB
( TARGET_NAME ASC,
  TARGET_OWNER ASC,
  VERSION_TIME DESC,
  VERSION_NODE ASC,
  KEY_HASH ASC);

ALTER TABLE QASN.IBMQREP_DELTOMB VOLATILE CARDINALITY;


--********************************************************************/
-- Create Monitor Control tables                                     */
-- Monitor schema must be ASN and the tables are IBMSNAP             */
-- not IBMQREP, like the other Qrep  tables                          */
-- In this sample the monitor tables are created in the default      */
-- tablespace                                                        */
--********************************************************************/


CREATE TABLE ASN.IBMSNAP_CONTACTS(
CONTACT_NAME                    VARCHAR(127) NOT NULL,
EMAIL_ADDRESS                   VARCHAR(128) NOT NULL,
ADDRESS_TYPE                    CHAR(1) NOT NULL,
DELEGATE                        VARCHAR(127),
DELEGATE_START                  DATE,
DELEGATE_END                    DATE,
DESCRIPTION                     VARCHAR(1024));

CREATE UNIQUE INDEX ASN.IBMSNAP_CONTACTSX
ON ASN.IBMSNAP_CONTACTS(
CONTACT_NAME                    ASC);

ALTER TABLE ASN.IBMSNAP_CONTACTS VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_GROUPS(
GROUP_NAME                      VARCHAR(127) NOT NULL,
DESCRIPTION                     VARCHAR(1024));

CREATE UNIQUE INDEX ASN.IBMSNAP_GROUPSX
ON ASN.IBMSNAP_GROUPS(
GROUP_NAME                      ASC);

ALTER TABLE ASN.IBMSNAP_GROUPS VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_CONTACTGRP(
GROUP_NAME                      VARCHAR(127) NOT NULL,
CONTACT_NAME                    VARCHAR(127) NOT NULL);

CREATE UNIQUE INDEX ASN.IBMSNAP_CONTACTGRPX
ON ASN.IBMSNAP_CONTACTGRP(
GROUP_NAME                      ASC,
CONTACT_NAME                    ASC);

ALTER TABLE ASN.IBMSNAP_CONTACTGRP VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_MONSERVERS(
MONITOR_QUAL                    CHAR(18) NOT NULL,
SERVER_NAME                     CHAR(18) NOT NULL,
SERVER_ALIAS                    CHAR( 8),
LAST_MONITOR_TIME               TIMESTAMP NOT NULL,
START_MONITOR_TIME              TIMESTAMP,
END_MONITOR_TIME                TIMESTAMP,
LASTRUN                         TIMESTAMP NOT NULL,
LASTSUCCESS                     TIMESTAMP,
STATUS                          SMALLINT NOT NULL);

CREATE UNIQUE INDEX ASN.IBMSNAP_MONSERVERSX
ON ASN.IBMSNAP_MONSERVERS(
MONITOR_QUAL                    ASC,
SERVER_NAME                     ASC);

ALTER TABLE ASN.IBMSNAP_MONSERVERS VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_CONDITIONS(
MONITOR_QUAL                    CHAR(18) NOT NULL,
SERVER_NAME                     CHAR(18) NOT NULL,
COMPONENT                       CHAR( 1) NOT NULL,
SCHEMA_OR_QUAL                  VARCHAR(128) NOT NULL,
SET_NAME                        CHAR(18) NOT NULL WITH DEFAULT ' ',
SERVER_ALIAS                    CHAR( 8),
ENABLED                         CHAR( 1) NOT NULL,
CONDITION_NAME                  CHAR(18) NOT NULL,
PARM_INT                        INT,
PARM_CHAR                       VARCHAR(128),
CONTACT_TYPE                    CHAR( 1) NOT NULL,
CONTACT                         VARCHAR(127) NOT NULL);

CREATE UNIQUE INDEX ASN.IBMSNAP_CONDITIONSX
ON ASN.IBMSNAP_CONDITIONS(
MONITOR_QUAL                    ASC,
SERVER_NAME                     ASC,
COMPONENT                       ASC,
SCHEMA_OR_QUAL                  ASC,
SET_NAME                        ASC,
CONDITION_NAME                  ASC);

ALTER TABLE ASN.IBMSNAP_CONDITIONS VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_ALERTS(
MONITOR_QUAL                    CHAR(18) NOT NULL,
ALERT_TIME                      TIMESTAMP NOT NULL,
COMPONENT                       CHAR( 1) NOT NULL,
SERVER_NAME                     CHAR(18) NOT NULL,
SERVER_ALIAS                    CHAR( 8),
SCHEMA_OR_QUAL                  VARCHAR(128) NOT NULL,
SET_NAME                        CHAR(18) NOT NULL WITH DEFAULT ' ',
CONDITION_NAME                  CHAR(18) NOT NULL,
OCCURRED_TIME                   TIMESTAMP NOT NULL,
ALERT_COUNTER                   SMALLINT NOT NULL,
ALERT_CODE                      CHAR( 10) NOT NULL,
RETURN_CODE                     INT NOT NULL,
NOTIFICATION_SENT               CHAR(1) NOT NULL,
ALERT_MESSAGE                   VARCHAR(1024) NOT NULL);

CREATE  INDEX ASN.IBMSNAP_ALERTSX
ON ASN.IBMSNAP_ALERTS(
MONITOR_QUAL                    ASC,
COMPONENT                       ASC,
SERVER_NAME                     ASC,
SCHEMA_OR_QUAL                  ASC,
SET_NAME                        ASC,
CONDITION_NAME                  ASC,
ALERT_CODE                      ASC);

ALTER TABLE ASN.IBMSNAP_ALERTS VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_MONTRACE(
MONITOR_QUAL                    CHAR(18) NOT NULL,
TRACE_TIME                      TIMESTAMP NOT NULL,
OPERATION                       CHAR( 8) NOT NULL,
DESCRIPTION                     VARCHAR(1024) NOT NULL);

CREATE  INDEX ASN.IBMSNAP_MONTRACEX
ON ASN.IBMSNAP_MONTRACE(
MONITOR_QUAL                    ASC,
TRACE_TIME                      ASC);

ALTER TABLE ASN.IBMSNAP_MONTRACE VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_MONTRAIL(
MONITOR_QUAL                    CHAR(18) NOT NULL,
SERVER_NAME                     CHAR(18) NOT NULL,
SERVER_ALIAS                    CHAR( 8),
STATUS                          SMALLINT NOT NULL,
LASTRUN                         TIMESTAMP NOT NULL,
LASTSUCCESS                     TIMESTAMP,
ENDTIME                         TIMESTAMP NOT NULL WITH DEFAULT ,
LAST_MONITOR_TIME               TIMESTAMP NOT NULL,
START_MONITOR_TIME              TIMESTAMP,
END_MONITOR_TIME                TIMESTAMP,
SQLCODE                         INT,
SQLSTATE                        CHAR(5),
NUM_ALERTS                      INT NOT NULL,
NUM_NOTIFICATIONS               INT NOT NULL,
SUSPENSION_NAME                 VARCHAR(128));

CREATE TABLE ASN.IBMSNAP_MONENQ(
MONITOR_QUAL                    CHAR( 18) NOT NULL);

CREATE TABLE ASN.IBMSNAP_MONPARMS(
MONITOR_QUAL                    CHAR( 18) NOT NULL,
ALERT_PRUNE_LIMIT               INT WITH DEFAULT 10080,
AUTOPRUNE                       CHAR(  1) WITH DEFAULT 'Y',
EMAIL_SERVER                    VARCHAR(128),
LOGREUSE                        CHAR(  1) WITH DEFAULT 'N',
LOGSTDOUT                       CHAR(  1) WITH DEFAULT 'N',
NOTIF_PER_ALERT                 INT WITH DEFAULT 3,
NOTIF_MINUTES                   INT WITH DEFAULT 60,
MONITOR_ERRORS                  VARCHAR(128),
MONITOR_INTERVAL                INT WITH DEFAULT 300000,
MONITOR_PATH                    VARCHAR(1040),
RUNONCE                         CHAR(  1) WITH DEFAULT 'N',
TERM                            CHAR(  1) WITH DEFAULT 'N',
TRACE_LIMIT                     INT WITH DEFAULT 10080,
ARCH_LEVEL                      CHAR(  4) WITH DEFAULT '0901');

CREATE UNIQUE INDEX ASN.IBMSNAP_MONPARMSX
ON ASN.IBMSNAP_MONPARMS(
MONITOR_QUAL                    ASC);

ALTER TABLE ASN.IBMSNAP_MONPARMS VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_TEMPLATES(
TEMPLATE_NAME                   VARCHAR(128) NOT NULL PRIMARY KEY,
START_TIME                      TIME NOT NULL,
WDAY                            SMALLINT DEFAULT null,
DURATION                        INT NOT NULL);

ALTER TABLE ASN.IBMSNAP_TEMPLATES VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_SUSPENDS(
SUSPENSION_NAME                 VARCHAR(128) NOT NULL PRIMARY KEY,
SERVER_NAME                     CHAR( 18) NOT NULL,
SERVER_ALIAS                    CHAR(  8),
TEMPLATE_NAME                   VARCHAR(128),
START                           TIMESTAMP NOT NULL,
STOP                            TIMESTAMP NOT NULL);

CREATE UNIQUE INDEX ASN.IBMSNAP_SUSPENDSX
ON ASN.IBMSNAP_SUSPENDS(
SERVER_NAME                     ASC,
START                           ASC,
TEMPLATE_NAME                   ASC);

ALTER TABLE ASN.IBMSNAP_SUSPENDS VOLATILE CARDINALITY;
