#############################################################################
# Licensed Materials - Property of IBM
#
# Governed under the terms of the International  
# License Agreement for Non-Warranted Sample Code.
#
# (C) COPYRIGHT International Business Machines Corp. 2006
#  All Rights Reserved.
#
#  US Government Users Restricted Rights - Use, duplication or
#  disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#############################################################################
#
# MAKEFILE for XML C samples on Unix
#
# Enter one of the following commands
#
#   make <app_name>        - Builds the program designated by <app_name>
#   make all               - Builds all supplied sample programs
#   make all_client        - Builds all client samples (all programs in the
#                             call_rtn and client_run categories)
#   make srv               - Builds sample that run on the server
#                            (stored procedure)
#   make call_rtn          - Builds  client programs that call stored procedure
#   make client_run        - Builds all programs that run completely on the
#                             client (not ones that call stored procedure)
#   make clean             - Erases intermediate files
#   make cleanall          - Erases all files produced in the build process
#                            except the original source files
#
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
#	       2b - make all_client (call_rtn + client_run)
#	       2c - make srv
#	       2d - make call_rtn
#	       2e - make client_run
#	       2f - make clean
#	       2g - make cleanall
#############################################################################


#****************************************************************************
#		   2a - make all
#****************************************************************************

all : \
	all_client

#****************************************************************************
#		   2b - make all_client (call_rtn + client_run)
#****************************************************************************

all_client : \
	client_run \
	call_rtn 

#****************************************************************************
#		   2c - make srv
#****************************************************************************

srv : \
	simple_xmlproc

#****************************************************************************
#                  2d - make call_rtn
#****************************************************************************

call_rtn :

#****************************************************************************
#		  2e - make client_run
#
#  xmldecomposition and reltoxmltype samples may fail to build if the setup 
#  for this sample is not run prior to make, to check setup script for sample 
#  please refer to README of header of the sample".
#****************************************************************************

client_run : \
	xmlconst xmlindex xmlinsert xmlread xmlupdel impexpxml \
	lobstoxml reltoxmltype  xmlrunstats xmldecomposition 

#****************************************************************************
#		   2f - make clean
#****************************************************************************

clean :
	$(ERASE) *.o *.bnd 
	$(ERASE) xmlconst.c xmlindex.c xmlinsert.c xmlread.c xmlupdel.c
	$(ERASE) impexpxml.c lobstoxml.c reltoxmltype.c xmlrunstats.c
	$(ERASE) xmldecomposition.c xmltotable.c simple_xmlproc.c

#****************************************************************************
#		   2g - make cleanall
#****************************************************************************

cleanall : \
	clean
	$(ERASE) xmlconst xmlindex xmlinsert xmlread xmlupdel
	$(ERASE) impexpxml lobstoxml reltoxmltype xmlrunstats
	$(ERASE) xmldecomposition xmltotable  simple_xmlproc
	$(ERASE) $DB2PATH/function/simple_xmlproc.class

#############################################################################
#  3 -- COMMANDS TO MAKE INDIVIDUAL SAMPLES
#                  3a -  regular samples, non-embedded SQL
#                  3b -  client/server samples
#############################################################################

xmlconst :
	$(BLDAPP) xmlconst
xmlindex :
	$(BLDAPP) xmlindex
xmlinsert :
	$(BLDAPP) xmlinsert
xmlread :
	$(BLDAPP) xmlread
xmltotable :
	$(BLDAPP) xmltotable
xmlupdel :
	$(BLDAPP) xmlupdel	
impexpxml :
	$(BLDAPP) impexpxml
lobstoxml :
	$(BLDAPP) lobstoxml
reltoxmltype :
	$(BLDAPP) reltoxmltype
xmlrunstats :
	$(BLDAPP) xmlrunstats
xmldecomposition :
	$(BLDAPP) xmldecomposition

#****************************************************************************
#                  3b - client/server samples
#****************************************************************************

simple_xmlproc :
	$(BLDRTN) simple_xmlproc
	spcat_xml 
