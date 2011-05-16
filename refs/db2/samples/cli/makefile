#############################################################################
# Licensed Materials - Property of IBM 
#
# Governed under the terms of the International
# License Agreement for Non-Warranted Sample Code.
#
# (C) COPYRIGHT International Business Machines Corp. 1995 - 2006
#  All Rights Reserved.
#
#  US Government Users Restricted Rights - Use, duplication or
#  disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#############################################################################
#
# MAKEFILE for CLI samples on Solaris
#
# Enter one of the following commands
#
#   make <app_name>	   - Builds the program designated by <app_name>
#   make all		   - Builds all supplied sample programs
#   make rtn		   - Builds all routines (stored procedures and UDFs)
#   make all_client	   - Builds all client samples (all programs in the
#			      call_rtn and client_run categories)
#   make call_rtn	   - Builds all client programs that call routines
#			      (stored procedures and UDFs) 
#   make client_run	   - Builds all programs that run completely on the
#			      client (not ones that call routines)
#   make clean		   - Erases all intermediate files produced in the  
#			      build process
#   make cleanall	   - Erases all files produced in the build process
#			      (all files except the original source files)
#
# The makefile contains the following sections:
#    1 -- VARIABLES
#    2 -- MAKE CATEGORIES
#    3 -- COMMANDS TO MAKE INDIVIDUAL SAMPLES
#
#
##############################################################################
#		   1 -- VARIABLES				      
##############################################################################

# This file assumes the DB2 instance path is defined by the variable HOME.
# It also assumes DB2 is installed under the DB2 instance.
# If these statements are not correct, update the variable DB2PATH. 
DB2PATH = $(HOME)/sqllib


BLDAPP=bldapp
BLDRTN=bldrtn
BLDMC=bldmc


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
#	       2a - make all (rtn + all_client)
#	       2b - make rtn
#	       2c - make all_client (call_rtn + client_run)
#	       2d - make call_rtn
#	       2e - make client_run
#	       2f - make clean
#	       2g - make cleanall
#############################################################################


#****************************************************************************
#		   2a - make all
#****************************************************************************

all : \
	rtn \
	all_client

#****************************************************************************
#		   2b - make rtn
#****************************************************************************

rtn : \
	spserver \
	udfsrv

#****************************************************************************
#		   2c - make all_client (call_rtn + client_run) 
#****************************************************************************

all_client : \
	call_rtn \
	client_run

#****************************************************************************
#		   2d - make call_rtn
#****************************************************************************

call_rtn : \
	spcall \
	spclient \
	spclires \
	udfcli

#****************************************************************************
#		  2e - make client_run 
#****************************************************************************

client_run : \
	admincmd_autoconfigure admincmd_contacts admincmd_describe \
	admincmd_export admincmd_import admincmd_onlinebackup \
	admincmd_quiesce admincmd_updateconfig \
	clihandl cli_info clisqlca \
	dbcongui dbconn dbinfo dbmcon dbmconx dbnative dbuse dbusemx \
	dbxamon \
	dtinfo dtlob dtudt \
	ilinfo \
	ininfo getdbcfgparams getdbmcfgparams getmessage \
	tbast tbcompress tbconstr tbcreate tbinfo tbload tbmod tbonlineinx \
	tbread tbrunstats tbtemp tbumqt \

#****************************************************************************
#		   2f - make clean
#****************************************************************************

clean : 
	$(ERASE) *.o *.map *.TXT *.BMP *.GIF *.XWD
	$(ERASE) dbmconx1.c dbmconx2.c dbusemx.c 

#****************************************************************************
#		   2g - make cleanall
#****************************************************************************

cleanall : \
	clean 
	$(ERASE) *.bnd
	$(ERASE) admincmd_autoconfigure admincmd_contacts admincmd_describe
	$(ERASE) admincmd_export admincmd_import admincmd_onlinebackup
	$(ERASE) admincmd_quiesce admincmd_updateconfig 
	$(ERASE) clihandl cli_info clisqlca
	$(ERASE) dbcongui dbconn dbinfo dbmcon dbmconx dbnative dbuse dbusemx
	$(ERASE) dbxamon 
	$(ERASE) dtinfo dtlob dtudt
	$(ERASE) ilinfo
	$(ERASE) ininfo
	$(ERASE) getdbcfgparams getdbmcfgparams getmessage
	$(ERASE) spcall spclient spclires spserver
	$(ERASE) tbast tbcompress tbconstr tbcreate tbinfo tbload tbmod
	$(ERASE) tbonlineinx tbread tbrunstats tbtemp tbumqt
	$(ERASE) udfcli udfsrv

	$(ERASE) $(DB2PATH)/function/spserver
	$(ERASE) $(DB2PATH)/function/udfsrv


#############################################################################
#  3 -- COMMANDS TO MAKE INDIVIDUAL SAMPLES
#		   3a -  regular samples
#		   3b -  CLI mixed with embedded SQL samples
#		   3d -  client/server samples
#############################################################################


#****************************************************************************
#		   3a -  regular samples
#****************************************************************************

admincmd_autoconfigure :
	$(BLDAPP) admincmd_autoconfigure 
admincmd_contacts :
	$(BLDAPP) admincmd_contacts 
admincmd_describe :
	$(BLDAPP) admincmd_describe
admincmd_export :
	$(BLDAPP) admincmd_export 
admincmd_import :
	$(BLDAPP) admincmd_import 
admincmd_onlinebackup :
	$(BLDAPP) admincmd_onlinebackup 
admincmd_quiesce :
	$(BLDAPP) admincmd_quiesce 
admincmd_updateconfig :
	$(BLDAPP) admincmd_updateconfig
clihandl :
	$(BLDAPP) clihandl
cli_info :
	$(BLDAPP) cli_info
clisqlca :
	$(BLDAPP) clisqlca
dbcongui :
	$(BLDAPP) dbcongui
dbconn :
	$(BLDAPP) dbconn
dbinfo :
	$(BLDAPP) dbinfo
dbmcon :
	$(BLDAPP) dbmcon
dbnative :
	$(BLDAPP) dbnative
dbxamon :
	$(BLDAPP) dbxamon
dbuse :
	$(BLDAPP) dbuse
dtinfo :
	$(BLDAPP) dtinfo
dtlob :
	$(BLDAPP) dtlob
dtudt :
	$(BLDAPP) dtudt
getdbcfgparams :
	$(BLDAPP) getdbcfgparams 
getdbmcfgparams :
	$(BLDAPP) getdbmcfgparams 
getmessage :
	$(BLDAPP) getmessage
ilinfo :
	$(BLDAPP) ilinfo
ininfo :
	$(BLDAPP) ininfo
tbast :
	$(BLDAPP) tbast
tbcompress :
	$(BLDAPP) tbcompress
tbconstr :
	$(BLDAPP) tbconstr
tbcreate :
	$(BLDAPP) tbcreate
tbinfo :
	$(BLDAPP) tbinfo
tbload :
	$(BLDAPP) tbload
tbmod :
	$(BLDAPP) tbmod
tbonlineinx :
	$(BLDAPP) tbonlineinx
tbread :
	$(BLDAPP) tbread
tbrunstats :
	$(BLDAPP) tbrunstats
tbtemp :
	$(BLDAPP) tbtemp
tbumqt :
	$(BLDAPP) tbumqt


#****************************************************************************
#		   3b -  CLI mixed with embedded SQL samples
#****************************************************************************


dbmconx :
	$(BLDMC) dbmconx $(ALIAS) $(ALIAS2) $(UID) $(PWD) $(UID2) $(PWD2)
dbusemx :
	$(BLDAPP) dbusemx $(ALIAS) $(UID) $(PWD)

#****************************************************************************
#		   3c -  client/server samples 
#****************************************************************************

spcall :
	$(BLDAPP) spcall
spclient :
	$(BLDAPP) spclient
spclires :
	$(BLDAPP) spclires
spserver :
	$(BLDRTN) spserver
	spcat
udfcli :
	$(BLDAPP) udfcli
udfsrv :
	$(BLDRTN) udfsrv
