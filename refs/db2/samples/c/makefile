##############################################################################
# Licensed Materials - Property of IBM
#
# Governed under the terms of the International
# License Agreement for Non-Warranted Sample Code.
#
# (C) COPYRIGHT International Business Machines Corp. 2006
# All Rights Reserved.
#
# US Government Users Restricted Rights - Use, duplication or
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
##############################################################################
#
# MAKEFILE for C samples on Solaris
#
# Enter one of the following commands 
#
#   make <app_name>	   - Builds the program designated by <app_name>
#   make all		   - Builds all supplied sample programs
#   make srv		   - Builds all samples that that run on the server
#			      including routines (stored procedures and UDFs)
#   make rtn		   - Builds all routines (stored procedures and UDFs)
#   make all_client	   - Builds all client samples (all programs in the
#			      call_rtn and client_run categories)
#   make call_rtn	   - Builds all client programs that call routines
#   make client_run	   - Builds all programs that run completely on the
#			      client (not ones that call routines)
#   make clean		   - Erases all intermediate files
#   make cleanall	   - Erases all files produced in the build process
#			     except the original source files
#
# The makefile contains the following sections:
#    1 -- VARIABLES
#    2 -- MAKE CATEGORIES
#    3 -- COMMANDS TO MAKE INDIVIDUAL SAMPLES
#
#
###########################################################################
#		   1 -- VARIABLES					  #
###########################################################################

# This file assumes the DB2 instance path is defined by the variable HOME.
# It also assumes DB2 is installed under the DB2 instance.
# If these statements are not correct, update the variable DB2PATH. 
DB2PATH = $(HOME)/sqllib

BLDAPP=bldapp
BLDRTN=bldrtn
BLDMC=bldmc
BLDMT=bldmt

# To connect to a remote SAMPLE database cataloged on the client machine
# with another name, update the ALIAS variable.
ALIAS=sample
# Set UID and PWD if neccesary  
UID=
PWD=

# To connect to a remote SAMPLE2 database cataloged on the client machine
# with another name, update the ALIAS2 variable.
ALIAS2=sample2
# Set UID2 and PWD2 if neccesary
UID2=$(UID)
PWD2=$(PWD)

COPY=cp
ERASE=rm -f

#############################################################################
#  2 -- MAKE CATEGORIES
#	       2a - make all (srv + all_client)
#	       2b - make srv
#	       2c - make rtn
#	       2d - make all_client (call_rtn + client_run)
#	       2e - make call_rtn
#	       2f - make client_run
#	       2g - make clean
#	       2h - make cleanall
#############################################################################


#****************************************************************************
#		   2a - make all
#****************************************************************************

all : \
	srv \
	all_client

#****************************************************************************
#		   2b - make srv
#****************************************************************************

srv : \
	rtn \
	dbcfg \
	instart

#****************************************************************************
#		   2c - make rtn 
#****************************************************************************

rtn : \
	spserver \
	udfsrv \
	udfemsrv

#****************************************************************************
#		   2d - make all_client (call_rtn + client_run)
#****************************************************************************

all_client : \
	call_rtn \
	client_run

#****************************************************************************
#		   2e - make call_rtn
#****************************************************************************

call_rtn : \
	spclient \
	udfcli \
	udfemcli

#****************************************************************************
#		   2f - make client_run
#****************************************************************************

client_run : \
	autostore \
	cli_info clisnap clisnapnew \
	dbauth dbconn dbcreate dbhistfile dbinfo dbinline dbinspec \
	dblogconn dblognoconn \
	dbmcon dbmigrat dbpkg \
	dbredirect dbrestore dbrollfwd \
	dbsnap dbsnapnew dbthrds dbuse \
	dtformat dtlob dtudt \
	evm \
	fnuse getlogs getmessage \
	inattach inauth ininfo insnap insnapnew \
	largerid setintegrity \
	tbast tbcompress tbconstr tbcreate \
	tbident tbinfo tbintrig \
	tbload tbloadcursor tbmerge tbmod tbmove tbonlineinx tbpriv \
	tbread tbreorg tbrowcompress tbrunstats tbsavept tbsel tbtemp \
	tbtrig tbumqt tbunion tscreate tsinfo \

#****************************************************************************
#		   2g - make clean
#****************************************************************************

clean : 
	$(ERASE) *.o
	$(ERASE) *.DEL *.TXT *.MSG
	$(ERASE) dbauth.c dbcfg.c dbconn.c dbhistfile.c dbinline.c dbinspec.c
	$(ERASE) dblogconn.c dblognoconn.c
	$(ERASE) dbmcon.c dbmcon1.c dbmcon2.c dbpkg.c 
	$(ERASE) dbredirect.c dbrestore.c dbrollfwd.c
	$(ERASE) dbthrds.c dbuse.c
	$(ERASE) dtformat.c dtlob.c dtudt.c
	$(ERASE) evm.c
	$(ERASE) fnuse.c 
	$(ERASE) getlogs.c getmessage.c
	$(ERASE) inauth.c 
	$(ERASE) largerid.c
	$(ERASE) setintegrity.c
	$(ERASE) spclient.c spserver.c
	$(ERASE) tbast.c tbcompress.c tbconstr.c tbcreate.c
	$(ERASE) tbident.c tbinfo.c tbintrig.c tbload.c tbloadcursor.c
	$(ERASE) tbmerge.c tbmod.c tbmove.c tbonlineinx.c tbpriv.c 
	$(ERASE) tbread.c tbreorg.c tbrowcompress.c tbrunstats.c
	$(ERASE) tbsavept.c tbsel.c tbtemp.c tbtrig.c 
	$(ERASE) tbumqt.c tbunion.c 
	$(ERASE) tscreate.c tsinfo.c 
	$(ERASE) udfcli.c udfemcli.c udfemsrv.c utilemb.c

#****************************************************************************
#		   2h - make cleanall
#****************************************************************************

cleanall : \
	clean
	$(ERASE) *.bnd
	$(ERASE) autostore
	$(ERASE) cli_info clisnap clisnapnew
	$(ERASE) dbauth dbcfg dbconn dbcreate dbhistfile 
	$(ERASE) dbinfo dbinline dbinspec
	$(ERASE) dblogconn dblognoconn
	$(ERASE) dbmcon dbmcon1 dbmcon2
	$(ERASE) dbmigrat dbpkg 
	$(ERASE) dbredirect dbrestore dbrollfwd
	$(ERASE) dbsnap dbsnapnew dbthrds dbuse
	$(ERASE) dtformat dtlob dtudt
	$(ERASE) evm
	$(ERASE) fnuse getlogs getmessage
	$(ERASE) inattach inauth ininfo instart insnap insnapnew
	$(ERASE) largerid
	$(ERASE) setintegrity
	$(ERASE) spclient spserver
	$(ERASE) tbast tbcompress tbconstr tbcreate
	$(ERASE) tbident tbinfo tbintrig 
	$(ERASE) tbload tbloadcursor tbmerge tbmod tbmove tbonlineinx tbpriv 
	$(ERASE) tbread tbreorg tbrowcompress tbrunstats tbsavept tbsel tbtemp
	$(ERASE) tbtrig tbumqt tbunion tscreate tsinfo
	$(ERASE) udfcli udfsrv
	$(ERASE) udfemcli udfemsrv
	$(ERASE) $(DB2PATH)/function/udfsrv
	$(ERASE) $(DB2PATH)/function/udfemsrv
	$(ERASE) $(DB2PATH)/function/spserver

#############################################################################
#  3 -- COMMANDS TO MAKE INDIVIDUAL SAMPLES
#		   3a -  regular samples, non-embedded SQL
#		   3b -  regular samples, embedded SQL
#		   3c -  client/server samples
#		   3d -  multi-connection samples
#		   3e -  multi-threaded samples
#############################################################################


#****************************************************************************
#		   3a -  regular samples, non-embedded SQL
#****************************************************************************

autostore :
	$(BLDAPP) autostore
cli_info :
	$(BLDAPP) cli_info
clisnap :
	$(BLDAPP) clisnap
clisnapnew :
	$(BLDAPP) clisnapnew
dbcreate :
	$(BLDAPP) dbcreate
dbinfo :
	$(BLDAPP) dbinfo
dbmigrat :
	$(BLDAPP) dbmigrat
dbsnap :
	$(BLDAPP) dbsnap
dbsnapnew :
	$(BLDAPP) dbsnapnew
inattach :
	$(BLDAPP) inattach
ininfo :
	$(BLDAPP) ininfo
instart :
	$(BLDAPP) instart
insnap :
	$(BLDAPP) insnap
insnapnew :
	$(BLDAPP) insnapnew



#****************************************************************************
#		   3b -  regular samples, embedded SQL
#****************************************************************************

dbauth :
	$(BLDAPP) dbauth $(ALIAS) $(UID) $(PWD)
dbcfg :
	$(BLDAPP) dbcfg $(ALIAS) $(UID) $(PWD)
dbconn :
	$(BLDAPP) dbconn $(ALIAS) $(UID) $(PWD)
dbhistfile :
	$(BLDAPP) dbhistfile $(ALIAS) $(UID) $(PWD)
dbinline :
	$(BLDAPP) dbinline $(ALIAS) $(UID) $(PWD)
dbinspec :
	$(BLDAPP) dbinspec $(ALIAS) $(UID) $(PWD)
dblogconn :
	$(BLDAPP) dblogconn $(ALIAS) $(UID) $(PWD)
dblognoconn :
	$(BLDAPP) dblognoconn $(ALIAS) $(UID) $(PWD)
dbpkg :
	$(BLDAPP) dbpkg $(ALIAS) $(UID) $(PWD)
dbredirect :
	$(BLDAPP) dbredirect $(ALIAS) $(UID) $(PWD)
dbrestore :
	$(BLDAPP) dbrestore $(ALIAS) $(UID) $(PWD)
dbrollfwd :
	$(BLDAPP) dbrollfwd $(ALIAS) $(UID) $(PWD)
dbuse :
	$(BLDAPP) dbuse $(ALIAS) $(UID) $(PWD)
dtformat :
	$(BLDAPP) dtformat $(ALIAS) $(UID) $(PWD)
dtlob :
	$(BLDAPP) dtlob $(ALIAS) $(UID) $(PWD)
dtudt :
	$(BLDAPP) dtudt $(ALIAS) $(UID) $(PWD)
evm :
	$(BLDAPP) evm $(ALIAS) $(UID) $(PWD)
fnuse :
	$(BLDAPP) fnuse $(ALIAS) $(UID) $(PWD)
getmessage :
	$(BLDAPP) getmessage $(ALIAS) $(UID) $(PWD)
getlogs :
	$(BLDAPP) getlogs $(ALIAS) $(UID) $(PWD)
inauth :
	$(BLDAPP) inauth $(ALIAS) $(UID) $(PWD)
largerid :
	$(BLDAPP) largerid $(ALIAS) $(UID) $(PWD)
setintegrity :
	$(BLDAPP) setintegrity $(ALIAS) $(UID) $(PWD)
tbast :
	$(BLDAPP) tbast $(ALIAS) $(UID) $(PWD)
tbcompress :
	$(BLDAPP) tbcompress $(ALIAS) $(UID) $(PWD)
tbconstr :
	$(BLDAPP) tbconstr $(ALIAS) $(UID) $(PWD)
tbcreate :
	$(BLDAPP) tbcreate $(ALIAS) $(UID) $(PWD)
tbident :
	$(BLDAPP) tbident $(ALIAS) $(UID) $(PWD)
tbinfo :
	$(BLDAPP) tbinfo $(ALIAS) $(UID) $(PWD)
tbintrig :
	$(BLDAPP) tbintrig $(ALIAS) $(UID) $(PWD)
tbload :
	$(BLDAPP) tbload $(ALIAS) $(UID) $(PWD)
tbmerge :
	$(BLDAPP) tbmerge $(ALIAS) $(UID) $(PWD)
tbmod :
	$(BLDAPP) tbmod $(ALIAS) $(UID) $(PWD)
tbloadcursor :
	$(BLDAPP) tbloadcursor $(ALIAS) $(UID) $(PWD)
tbmove :
	$(BLDAPP) tbmove $(ALIAS) $(UID) $(PWD)
tbonlineinx :
	$(BLDAPP) tbonlineinx $(ALIAS) $(UID) $(PWD)
tbpriv  :
	$(BLDAPP) tbpriv $(ALIAS) $(UID) $(PWD)
tbread :
	$(BLDAPP) tbread $(ALIAS) $(UID) $(PWD)
tbreorg :
	$(BLDAPP) tbreorg $(ALIAS) $(UID) $(PWD)
tbrowcompress :
	$(BLDAPP) tbrowcompress $(ALIAS) $(UID) $(PWD)
tbrunstats :
	$(BLDAPP) tbrunstats $(ALIAS) $(UID) $(PWD)
tbsavept :
	$(BLDAPP) tbsavept $(ALIAS) $(UID) $(PWD)
tbsel :
	tbselinit
	$(BLDAPP) tbsel $(ALIAS) $(UID) $(PWD)
tbtemp :
	$(BLDAPP) tbtemp $(ALIAS) $(UID) $(PWD)
tbtrig :
	$(BLDAPP) tbtrig $(ALIAS) $(UID) $(PWD)
tbumqt :
	$(BLDAPP) tbumqt $(ALIAS) $(UID) $(PWD)
tbunion :
	$(BLDAPP) tbunion $(ALIAS) $(UID) $(PWD)
tscreate :
	$(BLDAPP) tscreate $(ALIAS) $(UID) $(PWD)
tsinfo :
	$(BLDAPP) tsinfo $(ALIAS) $(UID) $(PWD)


#****************************************************************************
#		   3c - client/server samples   
#****************************************************************************


spclient :
	$(BLDAPP) spclient $(ALIAS) $(UID) $(PWD)
spserver :
	$(BLDRTN) spserver $(ALIAS)
	spcat

udfcli :
	$(BLDAPP) udfcli $(ALIAS) $(UID) $(PWD)
udfsrv :
	$(BLDRTN) udfsrv

udfemcli :
	$(BLDAPP) udfemcli $(ALIAS) $(UID) $(PWD)
udfemsrv :
	$(BLDRTN) udfemsrv


#****************************************************************************
#		   3d -  multi-connection samples
#****************************************************************************


dbmcon :
	$(BLDMC)  dbmcon $(ALIAS) $(ALIAS2) $(UID) $(PWD) $(UID2) $(PWD2)


#****************************************************************************
#		   3e -  multi-threaded samples
#****************************************************************************


dbthrds :
	$(BLDMT)  dbthrds $(ALIAS) $(UID) $(PWD)
