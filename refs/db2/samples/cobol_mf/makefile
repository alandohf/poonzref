#############################################################################
# Licensed Materials - Property of IBM
# 
# Governed under the terms of the International
# License Agreement for Non-Warranted Sample Code.
# 
# (C) COPYRIGHT International Business Machines Corp. 1995 - 2002 
# All Rights Reserved.
#
# US Government Users Restricted Rights - Use, duplication or
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#############################################################################
#
# MAKEFILE for Micro Focus COBOL samples on Solaris
#
# Enter one of the following commands 
#
#   make <app_name>	   - Builds the program designated by <app_name>
#
#   make all		   - Builds the all the supplied sample programs
#   make udfspserver       - Builds the examples that implement
#			     stored procedures and UDFs (on the server)
#   make localclient       - Builds the examples that can only be run
#			     successfully on a server 
#   make udfspclient       - Builds the examples that call stored 
#			     procedures and UDFs ( they can run remotely )
#   make otherremoteclient - Builds the examples that will run successfully
#			     on a client platform ( others than udfspclient )
#   make allremoteclient   - Builds programs in udfspclient and 
#			     otherremoteclient categories
#
#   make clean		   - Erases intermediate files
#   make cleanall	   - Erases all files produced in the build process,
#			     except the original source files
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
DB2PATH = $(HOME)/sqllib
BLDAPP=bldapp
BLDRTN=bldrtn

# To connect to a remote SAMPLE database cataloged on the client machine
# with another name, update the ALIAS variable.
ALIAS=sample
# Set UID and PWD if neccesary  
UID=
PWD=

COPY=cp
ERASE=rm -f

#############################################################################
#  2 -- MAKE CATEGORIES
#	       2a - make all(= allremoteclient + localclient +udfspserver)
#	       2b - make udfspserver
#	       2c - make localclient  
#	       2d - make udfspclient
#	       2e - make otherremoteclient
#	       2f - make allremoteclient(= udfspclient + otherremoteclient)
#	       2g - make clean
#	       2h - make cleanall
#############################################################################

#****************************************************************************
#		   2a - make all
#****************************************************************************

all : \
	udfspserver \
	allremoteclient \
	localclient

#****************************************************************************
#		   2b - make udfspserver
#****************************************************************************

udfspserver : \
	inpsrv\
	outsrv

#****************************************************************************
#		   2c - make localclient 
#****************************************************************************

localclient : \
	dbstart dbstop 

#****************************************************************************
#		   2d - make udfspclient
#****************************************************************************

udfspclient : \
	inpcli \
	outcli 

#****************************************************************************
#		   2e - make otherremoteclient
#****************************************************************************

otherremoteclient : \
	advsql \
	client cursor \
	d_dbconf d_dbmcon db_udcs dbauth dbcat \
	dbcmt dbconf dbinst dbmconf dbsnap \
	dbstat dcscat delet dynamic \
	ebcdicdb expsamp \
	impexp \
	joinsql \
	loadqry lobeval lobfile lobloc \
	migrate monreset monsz \
	nodecat \
	openftch \
	prepbind \
	qload \
	rebind restart \
	setact static sws \
	tabscont tabspace tabsql \
	tload trigsql tspace \
	updat \
	varinp


#****************************************************************************
#		   2f - make allremoteclient
#****************************************************************************

allremoteclient : \
	udfspclient \
	otherremoteclient

#****************************************************************************
#		   2g - make clean
#****************************************************************************

clean : \
	cleangen \
	cleanemb \
	cleanclisrv
 
cleangen :
	$(ERASE) *.o *.int
	$(ERASE) *.txt *.ixf

cleanemb :
	$(ERASE) advsql.cbl  
	$(ERASE) cursor.cbl 
	$(ERASE) dbauth.cbl dbstat.cbl delet.cbl dynamic.cbl  
	$(ERASE) expsamp.cbl 
	$(ERASE) impexp.cbl 
	$(ERASE) joinsql.cbl  
	$(ERASE) loadqry.cbl lobeval.cbl lobfile.cbl lobloc.cbl  
	$(ERASE) openftch.cbl 
	$(ERASE) prepbind.cbl 
	$(ERASE) qload.cbl 
	$(ERASE) rebind.cbl 
	$(ERASE) static.cbl 
	$(ERASE) tabscont.cbl tabspace.cbl tabsql.cbl  
	$(ERASE) tload.cbl trigsql.cbl tspace.cbl 
	$(ERASE) updat.cbl 
	$(ERASE) varinp.cbl 

cleanclisrv:
	$(ERASE) inpcli.cbl
	$(ERASE) inpsrv.cbl
	$(ERASE) inpsrv_wrap.c
	$(ERASE) inpsrv_wrap.exp

	$(ERASE) outcli.cbl
	$(ERASE) outsrv.cbl
	$(ERASE) outsrv_wrap.c
	$(ERASE) outsrv_wrap.exp

#****************************************************************************
#		   2h - make cleanall
#****************************************************************************

cleanall : \
	clean
	$(ERASE) *.bnd
	$(ERASE) advsql
	$(ERASE) client cursor
	$(ERASE) d_dbconf d_dbmcon db_udcs dbauth dbcat
	$(ERASE) dbcmt dbconf dbinst dbmconf dbsnap
	$(ERASE) dbstart dbstat dbstop dcscat delet dynamic
	$(ERASE) ebcdicdb expsamp
	$(ERASE) impexp inpcli inpsrv
	$(ERASE) joinsql
	$(ERASE) loadqry lobeval lobfile lobloc
	$(ERASE) migrate monreset monsz
	$(ERASE) nodecat
	$(ERASE) openftch outcli outsrv
	$(ERASE) prepbind
	$(ERASE) qload
	$(ERASE) rebind restart
	$(ERASE) setact static sws
	$(ERASE) tabscont tabspace tabsql
	$(ERASE) tload trigsql tspace
	$(ERASE) updat
	$(ERASE) varinp

	$(ERASE) $(DB2PATH)/function/inpsrv
	$(ERASE) $(DB2PATH)/function/outsrv     

#############################################################################
#  3 -- COMMANDS TO MAKE INDIVIDUAL SAMPLES
#		   3a -  non embedded SQL, non client/server samples
#		   3b -  embedded SQL, non client/server samples
#		   3c -  client/server samples 
#############################################################################

#****************************************************************************
#		   3a -  non embedded SQL, non client/server samples
#****************************************************************************

client : 
	$(BLDAPP) client  $(ALIAS) $(UID) $(PWD)

d_dbconf :
	$(BLDAPP) d_dbconf $(ALIAS) $(UID) $(PWD)

d_dbmcon :
	$(BLDAPP) d_dbmcon $(ALIAS) $(UID) $(PWD)

db_udcs :
	$(BLDAPP) db_udcs $(ALIAS) $(UID) $(PWD)

dbcat :
	$(BLDAPP) dbcat $(ALIAS) $(UID) $(PWD)

dbcmt :
	$(BLDAPP) dbcmt $(ALIAS) $(UID) $(PWD)

dbconf :
	$(BLDAPP) dbconf $(ALIAS) $(UID) $(PWD)

dbinst :
	$(BLDAPP) dbinst $(ALIAS) $(UID) $(PWD)

dbmconf :
	$(BLDAPP) dbmconf $(ALIAS) $(UID) $(PWD)

dbsnap :
	$(BLDAPP) dbsnap $(ALIAS) $(UID) $(PWD)

dbstart :
	$(BLDAPP) dbstart $(ALIAS) $(UID) $(PWD)

dbstop :
	$(BLDAPP) dbstop $(ALIAS) $(UID) $(PWD)

dcscat :
	$(BLDAPP) dcscat $(ALIAS) $(UID) $(PWD)

ebcdicdb :
	$(BLDAPP) ebcdicdb $(ALIAS) $(UID) $(PWD)

migrate :
	$(BLDAPP) migrate $(ALIAS) $(UID) $(PWD)

monreset :
	$(BLDAPP) monreset $(ALIAS) $(UID) $(PWD)

monsz :
	$(BLDAPP) monsz $(ALIAS) $(UID) $(PWD)

nodecat :
	$(BLDAPP) nodecat $(ALIAS) $(UID) $(PWD)

restart :
	$(BLDAPP) restart $(ALIAS) $(UID) $(PWD)

setact :
	$(BLDAPP) setact $(ALIAS) $(UID) $(PWD)

sws :
	$(BLDAPP) sws $(ALIAS) $(UID) $(PWD)

#****************************************************************************
#		   3b -  embedded SQL non client/server samples
#****************************************************************************

advsql :
	$(BLDAPP) advsql $(ALIAS) $(UID) $(PWD)

cursor :
	$(BLDAPP) cursor $(ALIAS) $(UID) $(PWD)

dbauth :
	$(BLDAPP) dbauth $(ALIAS) $(UID) $(PWD)

dbstat :
	$(BLDAPP) dbstat $(ALIAS) $(UID) $(PWD)

delet :
	$(BLDAPP) delet $(ALIAS) $(UID) $(PWD)

dynamic :
	$(BLDAPP) dynamic $(ALIAS) $(UID) $(PWD)

expsamp :
	$(BLDAPP) expsamp $(ALIAS) $(UID) $(PWD)

impexp :
	$(BLDAPP) impexp $(ALIAS) $(UID) $(PWD)

joinsql :
	$(BLDAPP) joinsql $(ALIAS) $(UID) $(PWD)

loadqry :
	$(BLDAPP) loadqry $(ALIAS) $(UID) $(PWD)

lobeval :
	$(BLDAPP) lobeval $(ALIAS) $(UID) $(PWD)

lobfile :
	$(BLDAPP) lobfile $(ALIAS) $(UID) $(PWD)

lobloc :
	$(BLDAPP) lobloc $(ALIAS) $(UID) $(PWD)

openftch :
	$(BLDAPP) openftch $(ALIAS) $(UID) $(PWD)

prepbind :
	$(BLDAPP) prepbind $(ALIAS) $(UID) $(PWD)

qload :
	$(BLDAPP) qload $(ALIAS) $(UID) $(PWD)

rebind :
	$(BLDAPP) rebind $(ALIAS) $(UID) $(PWD)

static :
	$(BLDAPP) static $(ALIAS) $(UID) $(PWD)

tabscont :
	$(BLDAPP) tabscont $(ALIAS) $(UID) $(PWD)

tabspace :
	$(BLDAPP) tabspace $(ALIAS) $(UID) $(PWD)

tabsql :
	$(BLDAPP) tabsql $(ALIAS) $(UID) $(PWD)

tload :
	$(BLDAPP) tload $(ALIAS) $(UID) $(PWD)

trigsql :
	$(BLDAPP) trigsql $(ALIAS) $(UID) $(PWD)

tspace :
	$(BLDAPP) tspace $(ALIAS) $(UID) $(PWD)

updat :
	$(BLDAPP) updat $(ALIAS) $(UID) $(PWD)

varinp :
	$(BLDAPP) varinp $(ALIAS) $(UID) $(PWD)

#****************************************************************************
#		   3c -  client/server samples    
#****************************************************************************

#--------------------inpcli/inpsrv------------------------------------------#

inpcli :
	$(BLDAPP) inpcli $(ALIAS) $(UID) $(PWD)

inpsrv :
	$(BLDRTN) inpsrv $(ALIAS) $(UID) $(PWD)

#--------------------outcli/outsrv------------------------------------------#

outcli :
	$(BLDAPP) outcli $(ALIAS) $(UID) $(PWD)

outsrv :
	$(BLDRTN) outsrv $(ALIAS) $(UID) $(PWD)



