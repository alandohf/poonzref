--********************************************************************/
--                                                                   */
--     IBM DB2 Information Integrator Replication Edition            */
--      Version 9.1 for Linux, UNIX and Windows                      */
--                                                                   */
--     Sample SQL Replication control tables                         */
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
--    Create SQL Replication Control Tables
--    (Linux, UNIX, and Windows edition)
------------------------------------------------------------------

-- BEGIN asnctlw.sql

-- UDB -- For the UDB platform, follow the directions given in the comments
-- UDB -- prefixed with "-- UDB --" (if any).

-- UDB -- TABLESPACE CONSIDERATIONS:

-- UDB -- Uncomment the drop statements below only if you are sure that they do
-- UDB -- not contain any important user tables!!!

--DROP TABLESPACE TSASNCA;
--DROP TABLESPACE TSASNUOW;
--DROP TABLESPACE TSASNAA;

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

-- UDB -- Note: tablespace parameters correspond to "FILE 'C:\TSASNCA.F1'"
-- UDB -- and "2000", respectively, in the following sample statement.

--CREATE TABLESPACE TSASNCA MANAGED BY DATABASE
--USING (FILE 'C:\TSASNCA.F1' 2000);

-- UDB -- Note: tablespace parameters correspond to "FILE 'C:\TSASNUOW.F1'"
-- UDB -- and "1000", respectively, in the following sample statement.

--CREATE TABLESPACE TSASNUOW MANAGED BY DATABASE
--USING (FILE 'C:\TSASNUOW.F1' 1000);

-- UDB -- Note: tablespace parameters correspond to "FILE 'C:\TSASNAA.F1'"
-- UDB -- and "2000", respectively, in the following sample statement.

--CREATE TABLESPACE TSASNAA MANAGED BY DATABASE
--USING (FILE 'C:\TSASNAA.F1' 2000);


--********************************************************************/
-- Create Capture Control tables                                     */
-- In this sample the Capture schema is ASN.
--********************************************************************/

-- connect to capture_server

------------------------------------------------------------------
--    Register Table       (All platforms      )
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_REGISTER(
  SOURCE_OWNER                    VARCHAR(30) NOT NULL,
  SOURCE_TABLE                    VARCHAR(128) NOT NULL,
  SOURCE_VIEW_QUAL                SMALLINT NOT NULL,
  GLOBAL_RECORD                   CHAR( 1) NOT NULL,
  SOURCE_STRUCTURE                SMALLINT NOT NULL,
  SOURCE_CONDENSED                CHAR( 1) NOT NULL,
  SOURCE_COMPLETE                 CHAR(  1) NOT NULL,
  CD_OWNER                        VARCHAR(30),
  CD_TABLE                        VARCHAR(128),
  PHYS_CHANGE_OWNER               VARCHAR(30),
  PHYS_CHANGE_TABLE               VARCHAR(128),
  CD_OLD_SYNCHPOINT               CHAR( 10) FOR BIT DATA,
  CD_NEW_SYNCHPOINT               CHAR( 10) FOR BIT DATA,
  DISABLE_REFRESH                 SMALLINT NOT NULL,
  CCD_OWNER                       VARCHAR(30),
  CCD_TABLE                       VARCHAR(128),
  CCD_OLD_SYNCHPOINT              CHAR( 10) FOR BIT DATA,
  SYNCHPOINT                      CHAR( 10) FOR BIT DATA,
  SYNCHTIME                       TIMESTAMP,
  CCD_CONDENSED                   CHAR(  1),
  CCD_COMPLETE                    CHAR(  1),
  ARCH_LEVEL                      CHAR(  4) NOT NULL,
  DESCRIPTION                     CHAR(254),
  BEFORE_IMG_PREFIX               VARCHAR(   4),
  CONFLICT_LEVEL                  CHAR(   1),
  CHG_UPD_TO_DEL_INS              CHAR(   1),
  CHGONLY                         CHAR(   1),
  RECAPTURE                       CHAR(   1),
  OPTION_FLAGS                    CHAR(   4) NOT NULL,
  STOP_ON_ERROR                   CHAR(  1) WITH DEFAULT 'Y',
  STATE                           CHAR(  1) WITH DEFAULT 'I',
  STATE_INFO                      CHAR(  8))
IN TSASNCA;

CREATE UNIQUE INDEX ASN.IBMSNAP_REGISTERX
ON ASN.IBMSNAP_REGISTER(
  SOURCE_OWNER                    ASC,
  SOURCE_TABLE                    ASC,
  SOURCE_VIEW_QUAL                ASC);

CREATE  INDEX ASN.IBMSNAP_REGISTERX1
ON ASN.IBMSNAP_REGISTER(
  PHYS_CHANGE_OWNER               ASC,
  PHYS_CHANGE_TABLE               ASC);

CREATE  INDEX ASN.IBMSNAP_REGISTERX2
ON ASN.IBMSNAP_REGISTER(
  GLOBAL_RECORD                   ASC);

ALTER TABLE ASN.IBMSNAP_REGISTER VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Pruning Control Table                  (All platforms      )
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_PRUNCNTL(
  TARGET_SERVER                   CHAR(18) NOT NULL,
  TARGET_OWNER                    VARCHAR(30) NOT NULL,
  TARGET_TABLE                    VARCHAR(128) NOT NULL,
  SYNCHTIME                       TIMESTAMP,
  SYNCHPOINT                      CHAR( 10) FOR BIT DATA,
  SOURCE_OWNER                    VARCHAR(30) NOT NULL,
  SOURCE_TABLE                    VARCHAR(128) NOT NULL,
  SOURCE_VIEW_QUAL                SMALLINT NOT NULL,
  APPLY_QUAL                      CHAR( 18) NOT NULL,
  SET_NAME                        CHAR( 18) NOT NULL,
  CNTL_SERVER                     CHAR( 18) NOT NULL,
  TARGET_STRUCTURE                SMALLINT NOT NULL,
  CNTL_ALIAS                      CHAR( 8),
  PHYS_CHANGE_OWNER               VARCHAR(30),
  PHYS_CHANGE_TABLE               VARCHAR(128),
  MAP_ID                          VARCHAR(10) NOT NULL)
IN TSASNCA;

CREATE UNIQUE INDEX ASN.IBMSNAP_PRUNCNTLX
ON ASN.IBMSNAP_PRUNCNTL(
  SOURCE_OWNER                    ASC,
  SOURCE_TABLE                    ASC,
  SOURCE_VIEW_QUAL                ASC,
  APPLY_QUAL                      ASC,
  SET_NAME                        ASC,
  TARGET_SERVER                   ASC,
  TARGET_TABLE                    ASC,
  TARGET_OWNER                    ASC);

CREATE UNIQUE INDEX ASN.IBMSNAP_PRUNCNTLX1
ON ASN.IBMSNAP_PRUNCNTL(
  MAP_ID                          ASC);

CREATE  INDEX ASN.IBMSNAP_PRUNCNTLX2
ON ASN.IBMSNAP_PRUNCNTL(
  PHYS_CHANGE_OWNER               ASC,
  PHYS_CHANGE_TABLE               ASC);

CREATE  INDEX ASN.IBMSNAP_PRUNCNTLX3
ON ASN.IBMSNAP_PRUNCNTL(
  APPLY_QUAL                      ASC,
  SET_NAME                        ASC,
  TARGET_SERVER                   ASC);

ALTER TABLE ASN.IBMSNAP_PRUNCNTL VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Prune Set Table                       (All IBM platforms  )
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_PRUNE_SET(
  TARGET_SERVER                   CHAR( 18) NOT NULL,
  APPLY_QUAL                      CHAR( 18) NOT NULL,
  SET_NAME                        CHAR( 18) NOT NULL,
  SYNCHTIME                       TIMESTAMP,
  SYNCHPOINT                      CHAR( 10) FOR BIT DATA NOT NULL)
IN TSASNCA;

CREATE UNIQUE INDEX ASN.IBMSNAP_PRUNE_SETX
ON ASN.IBMSNAP_PRUNE_SET(
  TARGET_SERVER                   ASC,
  APPLY_QUAL                      ASC,
  SET_NAME                        ASC);

ALTER TABLE ASN.IBMSNAP_PRUNE_SET VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Signal Table    (All platforms)
--    (allows user to synchronize events with db2 log)
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_SIGNAL(
  SIGNAL_TIME                     TIMESTAMP NOT NULL WITH DEFAULT ,
  SIGNAL_TYPE                     VARCHAR( 30) NOT NULL,
  SIGNAL_SUBTYPE                  VARCHAR( 30),
  SIGNAL_INPUT_IN                 VARCHAR(500),
  SIGNAL_STATE                    CHAR( 1) NOT NULL,
  SIGNAL_LSN                      CHAR( 10) FOR BIT DATA)
IN TSASNCA
DATA CAPTURE CHANGES;

CREATE UNIQUE INDEX ASN.IBMSNAP_SIGNALX
ON ASN.IBMSNAP_SIGNAL(
  SIGNAL_TIME                     ASC);

ALTER TABLE ASN.IBMSNAP_SIGNAL VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Restart Table        (All  platforms  )
--    ASN.IBMSNAP_WARMSTART has been replaced by ASN.IBMSNAP_RESTART
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_RESTART(
  MAX_COMMITSEQ                   CHAR( 10) FOR BIT DATA NOT NULL,
  MAX_COMMIT_TIME                 TIMESTAMP NOT NULL,
  MIN_INFLIGHTSEQ                 CHAR( 10) FOR BIT DATA NOT NULL,
  CURR_COMMIT_TIME                TIMESTAMP NOT NULL,
  CAPTURE_FIRST_SEQ               CHAR( 10) FOR BIT DATA NOT NULL)
IN TSASNCA;

------------------------------------------------------------------
--    Capture Trace Table     (All IBM platforms except the 400)
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_CAPTRACE(
  OPERATION                       CHAR( 8) NOT NULL,
  TRACE_TIME                      TIMESTAMP NOT NULL,
  DESCRIPTION                     VARCHAR(1024) NOT NULL)
IN TSASNCA;

CREATE  INDEX ASN.IBMSNAP_CAPTRACEX
ON ASN.IBMSNAP_CAPTRACE(
  TRACE_TIME                      ASC);

ALTER TABLE ASN.IBMSNAP_CAPTRACE VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Tuning Parameters Table for Capture    (All IBM platforms  )
--
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_CAPPARMS(
  RETENTION_LIMIT                 INT,
  LAG_LIMIT                       INT,
  COMMIT_INTERVAL                 INT,
  PRUNE_INTERVAL                  INT,
  TRACE_LIMIT                     INT,
  MONITOR_LIMIT                   INT,
  MONITOR_INTERVAL                INT,
  MEMORY_LIMIT                    SMALLINT,
  REMOTE_SRC_SERVER               CHAR( 18),
  AUTOPRUNE                       CHAR(  1),
  TERM                            CHAR(  1),
  AUTOSTOP                        CHAR(  1),
  LOGREUSE                        CHAR(  1),
  LOGSTDOUT                       CHAR(  1),
  SLEEP_INTERVAL                  SMALLINT,
  CAPTURE_PATH                    VARCHAR(1040),
  STARTMODE                       VARCHAR( 10))
IN TSASNCA;

------------------------------------------------------------------
--    Unit Of Work Table                 (All IBM platforms  )
--    volatile on UDB
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_UOW(
  IBMSNAP_UOWID                   CHAR( 10) FOR BIT DATA NOT NULL,
  IBMSNAP_COMMITSEQ               CHAR( 10) FOR BIT DATA NOT NULL,
  IBMSNAP_LOGMARKER               TIMESTAMP NOT NULL,
  IBMSNAP_AUTHTKN                 VARCHAR(30) NOT NULL,
  IBMSNAP_AUTHID                  VARCHAR(30) NOT NULL,
  IBMSNAP_REJ_CODE                CHAR(  1) NOT NULL WITH DEFAULT ,
  IBMSNAP_APPLY_QUAL              CHAR( 18) NOT NULL WITH DEFAULT )
IN TSASNUOW;

CREATE UNIQUE INDEX ASN.IBMSNAP_UOWX
ON ASN.IBMSNAP_UOW(
  IBMSNAP_COMMITSEQ               ASC,
  IBMSNAP_LOGMARKER               ASC);

ALTER TABLE ASN.IBMSNAP_UOW VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Enqueue Table for Capture    (All IBM platforms  ) - not the 400?
--    New table to ensure only one capture is running per DB
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_CAPENQ(
  LOCK_NAME                       CHAR(  9))
IN TSASNCA;

--------------------------------------------------------------------
--    SCHEMA Table                          (all platforms)
--    for the GUI
--------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_CAPSCHEMAS(
  CAP_SCHEMA_NAME                 VARCHAR(30))
IN TSASNCA;

CREATE UNIQUE INDEX ASN.IBMSNAP_CAPSCHEMAX
ON ASN.IBMSNAP_CAPSCHEMAS(
  CAP_SCHEMA_NAME                 ASC);

ALTER TABLE ASN.IBMSNAP_CAPSCHEMAS VOLATILE CARDINALITY;

INSERT INTO ASN.IBMSNAP_CAPSCHEMAS(CAP_SCHEMA_NAME)
     VALUES ('ASN');

------------------------------------------------------------------
--    Capture Monitor Table                 (All IBM platforms  )
--    (provides operational statistics to users)
--    JRN_LIB and JRN_NAME are for AS/400
------------------------------------------------------------------

CREATE TABLE ASN.IBMSNAP_CAPMON(
  MONITOR_TIME                    TIMESTAMP NOT NULL,
  RESTART_TIME                    TIMESTAMP NOT NULL,
  CURRENT_MEMORY                  INT NOT NULL,
  CD_ROWS_INSERTED                INT NOT NULL,
  RECAP_ROWS_SKIPPED              INT NOT NULL,
  TRIGR_ROWS_SKIPPED              INT NOT NULL,
  CHG_ROWS_SKIPPED                INT NOT NULL,
  TRANS_PROCESSED                 INT NOT NULL,
  TRANS_SPILLED                   INT NOT NULL,
  MAX_TRANS_SIZE                  INT NOT NULL,
  LOCKING_RETRIES                 INT NOT NULL,
  JRN_LIB                         CHAR( 10),
  JRN_NAME                        CHAR( 10),
  LOGREADLIMIT                    INT NOT NULL,
  CAPTURE_IDLE                    INT NOT NULL,
  SYNCHTIME                       TIMESTAMP NOT NULL)
IN TSASNCA;

CREATE UNIQUE INDEX ASN.IBMSNAP_CAPMONX
ON ASN.IBMSNAP_CAPMON(
  MONITOR_TIME                    ASC);

ALTER TABLE ASN.IBMSNAP_CAPMON VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Prune Lock Table                       (All platforms)
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_PRUNE_LOCK(
  DUMMY			CHAR(1)
);

INSERT INTO ASN.IBMSNAP_CAPPARMS(
RETENTION_LIMIT,LAG_LIMIT,COMMIT_INTERVAL,PRUNE_INTERVAL,
TRACE_LIMIT,MONITOR_LIMIT,MONITOR_INTERVAL,MEMORY_LIMIT,
SLEEP_INTERVAL,AUTOPRUNE,TERM,AUTOSTOP,LOGREUSE,LOGSTDOUT,
CAPTURE_PATH,STARTMODE) VALUES (
10080, 10080, 30, 300, 10080, 10080,
300000, 32, 5, 'Y', 'Y', 'N', 'N', 'N', NULL, 'WARMSI' );

------------------------------------------------------------------
--   New version tables for V9         (All platforms)
--   Tables names start with IBMQREP, not IBMSNAP
------------------------------------------------------------------

CREATE TABLE ASN.IBMQREP_COLVERSION
(  LSN            CHAR(10)     FOR BIT DATA NOT NULL,
  TABLEID1       SMALLINT                  NOT NULL,
  TABLEID2       SMALLINT                  NOT NULL,
  POSITION       SMALLINT                  NOT NULL,
  NAME           VARCHAR(128)              NOT NULL,
  TYPE           SMALLINT                  NOT NULL,
  LENGTH         INTEGER                   NOT NULL,
  NULLS          CHAR(1)                   NOT NULL,
  DEFAULT        VARCHAR(1536)
) IN TSASNCA;

CREATE UNIQUE INDEX ASN.IBMQREP_COLVERSIOX
  ON ASN.IBMQREP_COLVERSION(
  LSN, TABLEID1, TABLEID2, POSITION);

CREATE TABLE ASN.IBMQREP_TABVERSION
(  LSN            CHAR(10)     FOR BIT DATA NOT NULL,
  TABLEID1       SMALLINT                  NOT NULL,
  TABLEID2       SMALLINT                  NOT NULL,
  VERSION        INTEGER                   NOT NULL,
  SOURCE_OWNER   VARCHAR(128)              NOT NULL,
  SOURCE_NAME    VARCHAR(128)              NOT NULL
) IN TSASNCA;

CREATE UNIQUE INDEX ASN.IBMQREP_TABVERSIOX
  ON ASN.IBMQREP_TABVERSION(
  LSN, TABLEID1, TABLEID2, VERSION);

------------------------------------------------------------------
--   New tables to ignore transactions    (All IBM platforms  )
--   Tables names starts with IBMQREP, not IBMSNAP
------------------------------------------------------------------

CREATE TABLE ASN.IBMQREP_IGNTRAN
( AUTHID 	CHARACTER(128),
 AUTHTOKEN 	CHARACTER(30),
 PLANNAME 	CHARACTER(8),
 IGNTRANTRC CHAR(1) NOT NULL DEFAULT 'Y'
)  IN TSASNCA;

CREATE TABLE ASN.IBMQREP_IGNTRANTRC
( IGNTRAN_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP, 
 AUTHID 	CHARACTER(128),
 AUTHTOKEN 	CHARACTER(30),
 PLANNAME 	CHARACTER(8),
 TRANSID 	CHARACTER(10) 	FOR BIT DATA NOT NULL,
 COMMITLSN 	CHARACTER(10) 	FOR BIT DATA NOT NULL
)  IN TSASNCA;


-- connect to apply_control_server

-- All Apply tables must have schema ASN

------------------------------------------------------------------
--    Subscription Set Table             (All IBM platforms  )
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_SUBS_SET(
  APPLY_QUAL                      CHAR( 18) NOT NULL,
  SET_NAME                        CHAR( 18) NOT NULL,
  SET_TYPE                        CHAR(  1) NOT NULL,
  WHOS_ON_FIRST                   CHAR(  1) NOT NULL,
  ACTIVATE                        SMALLINT NOT NULL,
  SOURCE_SERVER                   CHAR( 18) NOT NULL,
  SOURCE_ALIAS                    CHAR(  8),
  TARGET_SERVER                   CHAR( 18) NOT NULL,
  TARGET_ALIAS                    CHAR(  8),
  STATUS                          SMALLINT NOT NULL,
  LASTRUN                         TIMESTAMP NOT NULL,
  REFRESH_TYPE                    CHAR( 1) NOT NULL,
  SLEEP_MINUTES                   INT,
  EVENT_NAME                      CHAR( 18),
  LASTSUCCESS                     TIMESTAMP,
  SYNCHPOINT                      CHAR( 10) FOR BIT DATA,
  SYNCHTIME                       TIMESTAMP,
  CAPTURE_SCHEMA                  VARCHAR( 30) NOT NULL,
  TGT_CAPTURE_SCHEMA              VARCHAR( 30),
  FEDERATED_SRC_SRVR              VARCHAR( 18),
  FEDERATED_TGT_SRVR              VARCHAR( 18),
  JRN_LIB                         CHAR( 10),
  JRN_NAME                        CHAR( 10),
  OPTION_FLAGS                    CHAR(  4) NOT NULL,
  COMMIT_COUNT                    SMALLINT,
  MAX_SYNCH_MINUTES               SMALLINT,
  AUX_STMTS                       SMALLINT NOT NULL,
  ARCH_LEVEL                      CHAR( 4) NOT NULL)
IN TSASNAA;

CREATE UNIQUE INDEX ASN.IBMSNAP_SUBS_SETX
ON ASN.IBMSNAP_SUBS_SET(
  APPLY_QUAL                      ASC,
  SET_NAME                        ASC,
  WHOS_ON_FIRST                   ASC);

ALTER TABLE ASN.IBMSNAP_SUBS_SET VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Subscription-Targets-Member Table    (All IBM platforms  )
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_SUBS_MEMBR(
  APPLY_QUAL                      CHAR( 18) NOT NULL,
  SET_NAME                        CHAR( 18) NOT NULL,
  WHOS_ON_FIRST                   CHAR(  1) NOT NULL,
  SOURCE_OWNER                    VARCHAR( 30) NOT NULL,
  SOURCE_TABLE                    VARCHAR(128) NOT NULL,
  SOURCE_VIEW_QUAL                SMALLINT NOT NULL,
  TARGET_OWNER                    VARCHAR(30) NOT NULL,
  TARGET_TABLE                    VARCHAR(128) NOT NULL,
  TARGET_CONDENSED                CHAR(  1) NOT NULL,
  TARGET_COMPLETE                 CHAR(  1) NOT NULL,
  TARGET_STRUCTURE                SMALLINT NOT NULL,
  PREDICATES                      VARCHAR(1024),
  MEMBER_STATE                    CHAR(  1),
  TARGET_KEY_CHG                  CHAR(  1) NOT NULL,
  UOW_CD_PREDICATES               VARCHAR(1024),
  JOIN_UOW_CD                     CHAR(  1),
  LOADX_TYPE                      SMALLINT,
  LOADX_SRC_N_OWNER               VARCHAR( 30),
  LOADX_SRC_N_TABLE               VARCHAR(128))
IN TSASNAA;

CREATE UNIQUE INDEX ASN.IBMSNAP_SUBS_MEMBX
ON ASN.IBMSNAP_SUBS_MEMBR(
  APPLY_QUAL                      ASC,
  SET_NAME                        ASC,
  WHOS_ON_FIRST                   ASC,
  SOURCE_OWNER                    ASC,
  SOURCE_TABLE                    ASC,
  SOURCE_VIEW_QUAL                ASC,
  TARGET_OWNER                    ASC,
  TARGET_TABLE                    ASC);

ALTER TABLE ASN.IBMSNAP_SUBS_MEMBR VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Subscription Columns Table       (All IBM platforms  )
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_SUBS_COLS(
  APPLY_QUAL                      CHAR( 18) NOT NULL,
  SET_NAME                        CHAR( 18) NOT NULL,
  WHOS_ON_FIRST                   CHAR(  1) NOT NULL,
  TARGET_OWNER                    VARCHAR(30) NOT NULL,
  TARGET_TABLE                    VARCHAR(128) NOT NULL,
  COL_TYPE                        CHAR(  1) NOT NULL,
  TARGET_NAME                     VARCHAR( 30) NOT NULL,
  IS_KEY                          CHAR(  1) NOT NULL,
  COLNO                           SMALLINT NOT NULL,
  EXPRESSION                      VARCHAR(254) NOT NULL)
IN TSASNAA;

CREATE UNIQUE INDEX ASN.IBMSNAP_SUBS_COLSX
ON ASN.IBMSNAP_SUBS_COLS(
  APPLY_QUAL                      ASC,
  SET_NAME                        ASC,
  WHOS_ON_FIRST                   ASC,
  TARGET_OWNER                    ASC,
  TARGET_TABLE                    ASC,
  TARGET_NAME                     ASC);

ALTER TABLE ASN.IBMSNAP_SUBS_COLS VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Subscription Statement Table         (All IBM platforms  )
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_SUBS_STMTS(
  APPLY_QUAL                      CHAR( 18) NOT NULL,
  SET_NAME                        CHAR( 18) NOT NULL,
  WHOS_ON_FIRST                   CHAR(  1) NOT NULL,
  BEFORE_OR_AFTER                 CHAR(  1) NOT NULL,
  STMT_NUMBER                     SMALLINT NOT NULL,
  EI_OR_CALL                      CHAR(  1) NOT NULL,
  SQL_STMT                        VARCHAR(1024),
  ACCEPT_SQLSTATES                VARCHAR( 50))
IN TSASNAA;

CREATE UNIQUE INDEX ASN.IBMSNAP_SUBS_STMTX
ON ASN.IBMSNAP_SUBS_STMTS(
  APPLY_QUAL                      ASC,
  SET_NAME                        ASC,
  WHOS_ON_FIRST                   ASC,
  BEFORE_OR_AFTER                 ASC,
  STMT_NUMBER                     ASC);

ALTER TABLE ASN.IBMSNAP_SUBS_STMTS VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Subscription Event Table          (All IBM platforms  )
--
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_SUBS_EVENT(
  EVENT_NAME                      CHAR( 18) NOT NULL,
  EVENT_TIME                      TIMESTAMP NOT NULL,
  END_SYNCHPOINT                  CHAR( 10) FOR BIT DATA,
  END_OF_PERIOD                   TIMESTAMP)
IN TSASNAA;

CREATE UNIQUE INDEX ASN.IBMSNAP_SUBS_EVENX
ON ASN.IBMSNAP_SUBS_EVENT(
  EVENT_NAME                      ASC,
  EVENT_TIME                      ASC);

ALTER TABLE ASN.IBMSNAP_SUBS_EVENT VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Apply Trail Table
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_APPLYTRAIL(
  APPLY_QUAL                      CHAR( 18) NOT NULL,
  SET_NAME                        CHAR( 18) NOT NULL,
  SET_TYPE                        CHAR(  1) NOT NULL,
  WHOS_ON_FIRST                   CHAR(  1) NOT NULL,
  ASNLOAD                         CHAR(  1),
  FULL_REFRESH                    CHAR(  1),
  EFFECTIVE_MEMBERS               INT,
  SET_INSERTED                    INT NOT NULL,
  SET_DELETED                     INT NOT NULL,
  SET_UPDATED                     INT NOT NULL,
  SET_REWORKED                    INT NOT NULL,
  SET_REJECTED_TRXS               INT NOT NULL,
  STATUS                          SMALLINT NOT NULL,
  LASTRUN                         TIMESTAMP NOT NULL,
  LASTSUCCESS                     TIMESTAMP,
  SYNCHPOINT                      CHAR( 10) FOR BIT DATA,
  SYNCHTIME                       TIMESTAMP,
  SOURCE_SERVER                   CHAR( 18) NOT NULL,
  SOURCE_ALIAS                    CHAR(  8),
  SOURCE_OWNER                    VARCHAR(30),
  SOURCE_TABLE                    VARCHAR(128),
  SOURCE_VIEW_QUAL                SMALLINT,
  TARGET_SERVER                   CHAR( 18) NOT NULL,
  TARGET_ALIAS                    CHAR(  8),
  TARGET_OWNER                    VARCHAR(30) NOT NULL,
  TARGET_TABLE                    VARCHAR(128) NOT NULL,
  CAPTURE_SCHEMA                  VARCHAR(30) NOT NULL,
  TGT_CAPTURE_SCHEMA              VARCHAR(30),
  FEDERATED_SRC_SRVR              VARCHAR( 18),
  FEDERATED_TGT_SRVR              VARCHAR( 18),
  JRN_LIB                         CHAR( 10),
  JRN_NAME                        CHAR( 10),
  COMMIT_COUNT                    SMALLINT,
  OPTION_FLAGS                    CHAR(  4) NOT NULL,
  EVENT_NAME                      CHAR( 18),
  ENDTIME                         TIMESTAMP NOT NULL WITH DEFAULT ,
  SOURCE_CONN_TIME                TIMESTAMP,
  SQLSTATE                        CHAR(  5),
  SQLCODE                         INT,
  SQLERRP                         CHAR(  8),
  SQLERRM                         VARCHAR( 70),
  APPERRM                         VARCHAR(760))
IN TSASNAA;

CREATE  INDEX ASN.IBMSNAP_APPLYTRLX
ON ASN.IBMSNAP_APPLYTRAIL(
  LASTRUN                         DESC,
  APPLY_QUAL                      ASC);

ALTER TABLE ASN.IBMSNAP_APPLYTRAIL VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Apply Trace Table       (All IBM platforms except the 400)
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_APPLYTRACE(
  APPLY_QUAL                      CHAR(18) NOT NULL,
  TRACE_TIME                      TIMESTAMP NOT NULL,
  OPERATION                       CHAR(  8) NOT NULL,
  DESCRIPTION                     VARCHAR(1024) NOT NULL)
IN TSASNAA;

CREATE INDEX ASN.IBMSNAP_APPLYTRACX
ON ASN.IBMSNAP_APPLYTRACE(
  APPLY_QUAL                      ASC,
  TRACE_TIME                      ASC);

ALTER TABLE ASN.IBMSNAP_APPLYTRACE VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Compansate Table
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_COMPENSATE(
  APPLY_QUAL                      CHAR( 18) NOT NULL,
  MEMBER                          SMALLINT NOT NULL,
  INTENTSEQ                       CHAR( 10) FOR BIT DATA NOT NULL,
  OPERATION                       CHAR(  1) NOT NULL)
IN TSASNAA;

CREATE UNIQUE INDEX ASN.IBMSNAP_COMPENSATX
ON ASN.IBMSNAP_COMPENSATE(
  APPLY_QUAL                      ASC,
  MEMBER                          ASC);

ALTER TABLE ASN.IBMSNAP_COMPENSATE VOLATILE CARDINALITY;

------------------------------------------------------------------
--  Enqueue Table for Apply                (All platforms)
--  Table to ensure only one apply is running per control server
------------------------------------------------------------------
CREATE TABLE ASN.IBMSNAP_APPENQ(
  APPLY_QUAL                      CHAR( 18))
IN TSASNAA;

CREATE UNIQUE INDEX ASN.IBMSNAP_APPENQX
ON ASN.IBMSNAP_APPENQ(
  APPLY_QUAL                      ASC);

ALTER TABLE ASN.IBMSNAP_APPENQ VOLATILE CARDINALITY;

------------------------------------------------------------------
--    Tuning Parameters Table for Apply      (All IBM platforms  )
------------------------------------------------------------------

CREATE TABLE ASN.IBMSNAP_APPPARMS(
  APPLY_QUAL                      CHAR( 18) NOT NULL,
  APPLY_PATH                      VARCHAR(1040),
  COPYONCE                        CHAR(  1) WITH DEFAULT 'N',
  DELAY                           INT WITH DEFAULT 6,
  ERRWAIT                         INT WITH DEFAULT 300,
  INAMSG                          CHAR(  1) WITH DEFAULT 'Y',
  LOADXIT                         CHAR(  1) WITH DEFAULT 'N',
  LOGREUSE                        CHAR(  1) WITH DEFAULT 'N',
  LOGSTDOUT                       CHAR(  1) WITH DEFAULT 'N',
  NOTIFY                          CHAR(  1) WITH DEFAULT 'N',
  OPT4ONE                         CHAR(  1) WITH DEFAULT 'N',
  SLEEP                           CHAR(  1) WITH DEFAULT 'Y',
  SQLERRCONTINUE                  CHAR(  1) WITH DEFAULT 'N',
  SPILLFILE                       VARCHAR( 10) WITH DEFAULT 'DISK',
  TERM                            CHAR(  1) WITH DEFAULT 'Y',
  TRLREUSE                        CHAR(  1) WITH DEFAULT 'N')
IN TSASNAA;

CREATE UNIQUE INDEX ASN.IBMSNAP_APPPARMSX
ON ASN.IBMSNAP_APPPARMS(
  APPLY_QUAL                      ASC);

ALTER TABLE ASN.IBMSNAP_APPPARMS VOLATILE CARDINALITY;

-- Monitor Control tables

--DROP TABLESPACE REPLMONTS1;
--DROP TABLESPACE REPLMONTS2;
--DROP TABLESPACE REPLMONTS3;

CREATE  TABLESPACE REPLMONTS1
 MANAGED BY DATABASE
 USING
( FILE 'REPLMONTS1' 5M);

CREATE  TABLESPACE REPLMONTS2
 MANAGED BY DATABASE
 USING
( FILE 'REPLMONTS2' 5M);

CREATE  TABLESPACE REPLMONTS3
 MANAGED BY DATABASE
 USING
( FILE 'REPLMONTS3' 5M);

CREATE TABLE ASN.IBMSNAP_CONTACTS(
CONTACT_NAME            VARCHAR(127) NOT NULL,
EMAIL_ADDRESS           VARCHAR(128) NOT NULL,
ADDRESS_TYPE            CHAR(1) NOT NULL,
DELEGATE                VARCHAR(127),
DELEGATE_START          DATE,
DELEGATE_END            DATE,
DESCRIPTION             VARCHAR(1024))
IN REPLMONTS1;

CREATE UNIQUE INDEX ASN.IBMSNAP_CONTACTSX
ON ASN.IBMSNAP_CONTACTS(
CONTACT_NAME ASC);

ALTER TABLE ASN.IBMSNAP_CONTACTS VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_ALERTS(
MONITOR_QUAL            CHAR(18) NOT NULL,
ALERT_TIME              TIMESTAMP NOT NULL,
COMPONENT               CHAR( 1) NOT NULL,
SERVER_NAME             CHAR(18) NOT NULL,
SERVER_ALIAS            CHAR( 8),
SCHEMA_OR_QUAL          VARCHAR(128) NOT NULL,
SET_NAME                CHAR(18) NOT NULL WITH DEFAULT ' ',
CONDITION_NAME          CHAR(18) NOT NULL,
OCCURRED_TIME           TIMESTAMP NOT NULL,
ALERT_COUNTER           SMALLINT NOT NULL,
ALERT_CODE              CHAR( 10) NOT NULL,
RETURN_CODE             INT NOT NULL,
NOTIFICATION_SENT       CHAR(1) NOT NULL,
ALERT_MESSAGE           VARCHAR(1024) NOT NULL)
IN REPLMONTS2;

CREATE  INDEX ASN.IBMSNAP_ALERTX
ON ASN.IBMSNAP_ALERTS(
MONITOR_QUAL            ASC,
COMPONENT               ASC,
SERVER_NAME             ASC,
SCHEMA_OR_QUAL          ASC,
SET_NAME                ASC,
CONDITION_NAME          ASC,
ALERT_CODE              ASC);

ALTER TABLE ASN.IBMSNAP_ALERTS VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_MONPARMS(
MONITOR_QUAL            CHAR( 18) NOT NULL,
ALERT_PRUNE_LIMIT       INT WITH DEFAULT 10080,
AUTOPRUNE               CHAR(  1) WITH DEFAULT 'Y',
EMAIL_SERVER            VARCHAR(128),
LOGREUSE                CHAR(  1) WITH DEFAULT 'N',
LOGSTDOUT               CHAR(  1) WITH DEFAULT 'N',
NOTIF_PER_ALERT         INT WITH DEFAULT 3,
NOTIF_MINUTES           INT WITH DEFAULT 60,
MONITOR_ERRORS          VARCHAR(128),
MONITOR_INTERVAL        INT WITH DEFAULT 300000,
MONITOR_PATH            VARCHAR(1040),
RUNONCE                 CHAR(  1) WITH DEFAULT 'N',
TERM                    CHAR(  1) WITH DEFAULT 'N',
TRACE_LIMIT             INT WITH DEFAULT 10080,
ARCH_LEVEL              CHAR(  4) WITH DEFAULT '0810')
IN REPLMONTS3;

CREATE UNIQUE INDEX ASN.IBMSNAP_MONPARMSX
ON ASN.IBMSNAP_MONPARMS(
MONITOR_QUAL            ASC);

ALTER TABLE ASN.IBMSNAP_MONPARMS VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_GROUPS(
GROUP_NAME              VARCHAR(127) NOT NULL,
DESCRIPTION             VARCHAR(1024))
IN REPLMONTS1;

CREATE UNIQUE INDEX ASN.IBMSNAP_GROUPSX
ON ASN.IBMSNAP_GROUPS(
GROUP_NAME              ASC);

ALTER TABLE ASN.IBMSNAP_GROUPS VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_CONTACTGRP(
GROUP_NAME              VARCHAR(127) NOT NULL,
CONTACT_NAME            VARCHAR(127) NOT NULL)
IN REPLMONTS1;

CREATE UNIQUE INDEX ASN.IBMSNAP_CONTACTGPX
ON ASN.IBMSNAP_CONTACTGRP(
GROUP_NAME              ASC,
CONTACT_NAME            ASC);

ALTER TABLE ASN.IBMSNAP_CONTACTGRP VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_CONDITIONS(
MONITOR_QUAL            CHAR(18) NOT NULL,
SERVER_NAME             CHAR(18) NOT NULL,
COMPONENT               CHAR( 1) NOT NULL,
SCHEMA_OR_QUAL          VARCHAR(128) NOT NULL,
SET_NAME                CHAR(18) NOT NULL WITH DEFAULT ' ',
SERVER_ALIAS            CHAR( 8),
ENABLED                 CHAR( 1) NOT NULL,
CONDITION_NAME          CHAR(18) NOT NULL,
PARM_INT                INT,
PARM_CHAR               VARCHAR(128),
CONTACT_TYPE            CHAR( 1) NOT NULL,
CONTACT                 VARCHAR(127) NOT NULL)
IN REPLMONTS1;

CREATE UNIQUE INDEX ASN.IBMSNAP_MONCONDX
ON ASN.IBMSNAP_CONDITIONS(
MONITOR_QUAL            ASC,
SERVER_NAME             ASC,
COMPONENT               ASC,
SCHEMA_OR_QUAL          ASC,
SET_NAME                ASC,
CONDITION_NAME          ASC);

ALTER TABLE ASN.IBMSNAP_CONDITIONS VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_MONSERVERS(
MONITOR_QUAL            CHAR(18) NOT NULL,
SERVER_NAME             CHAR(18) NOT NULL,
SERVER_ALIAS            CHAR( 8),
LAST_MONITOR_TIME       TIMESTAMP NOT NULL,
START_MONITOR_TIME      TIMESTAMP,
END_MONITOR_TIME        TIMESTAMP,
LASTRUN                 TIMESTAMP NOT NULL,
LASTSUCCESS             TIMESTAMP,
STATUS                  SMALLINT NOT NULL)
IN REPLMONTS1;

CREATE UNIQUE INDEX ASN.IBMSNAP_MONSERVERX
ON ASN.IBMSNAP_MONSERVERS(
MONITOR_QUAL            ASC,
SERVER_NAME             ASC);

ALTER TABLE ASN.IBMSNAP_MONSERVERS VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_MONENQ(
MONITOR_QUAL            CHAR( 18) NOT NULL)
IN REPLMONTS1;

CREATE TABLE ASN.IBMSNAP_MONTRACE(
MONITOR_QUAL            CHAR(18) NOT NULL,
TRACE_TIME              TIMESTAMP NOT NULL,
OPERATION               CHAR( 8) NOT NULL,
DESCRIPTION             VARCHAR(1024) NOT NULL)
IN REPLMONTS3;

CREATE  INDEX ASN.IBMSNAP_MONTRACEX
ON ASN.IBMSNAP_MONTRACE(
MONITOR_QUAL            ASC,
TRACE_TIME              ASC);

ALTER TABLE ASN.IBMSNAP_MONTRACE VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_MONTRAIL(
MONITOR_QUAL            CHAR(18) NOT NULL,
SERVER_NAME             CHAR(18) NOT NULL,
SERVER_ALIAS            CHAR( 8),
STATUS                  SMALLINT NOT NULL,
LASTRUN                 TIMESTAMP NOT NULL,
LASTSUCCESS             TIMESTAMP,
ENDTIME                 TIMESTAMP NOT NULL WITH DEFAULT,
LAST_MONITOR_TIME       TIMESTAMP NOT NULL,
START_MONITOR_TIME      TIMESTAMP,
END_MONITOR_TIME        TIMESTAMP,
SQLCODE                 INT,
SQLSTATE                CHAR(5),
NUM_ALERTS              INT NOT NULL,
NUM_NOTIFICATIONS       INT NOT NULL,
SUSPENSION_NAME         VARCHAR(128)  )
IN REPLMONTS3;

CREATE TABLE ASN.IBMSNAP_TEMPLATES(
TEMPLATE_NAME                   VARCHAR(128) NOT NULL PRIMARY KEY,
START_TIME                      TIME NOT NULL,
WDAY                            SMALLINT DEFAULT null,
DURATION                        INT NOT NULL)
IN REPLMONTS3;


ALTER TABLE ASN.IBMSNAP_TEMPLATES VOLATILE CARDINALITY;

CREATE TABLE ASN.IBMSNAP_SUSPENDS(
SUSPENSION_NAME                 VARCHAR(128) NOT NULL PRIMARY KEY,
SERVER_NAME                     CHAR( 18) NOT NULL,
SERVER_ALIAS                    CHAR(  8),
TEMPLATE_NAME                   VARCHAR(128),
START                           TIMESTAMP NOT NULL,
STOP                            TIMESTAMP NOT NULL)
IN REPLMONTS3;


CREATE UNIQUE INDEX ASN.IBMSNAP_SUSPENDSX
ON ASN.IBMSNAP_SUSPENDS(
SERVER_NAME                     ASC,
START                           ASC,
TEMPLATE_NAME                   ASC);

ALTER TABLE ASN.IBMSNAP_SUSPENDS VOLATILE CARDINALITY;

-- COMMIT;
