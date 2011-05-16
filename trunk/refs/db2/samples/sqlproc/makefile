##############################################################################
# Licensed Materials - Property of IBM
#
# Governed under the terms of the International
# License Agreement for Non-Warranted Sample Code.
#
# (C) COPYRIGHT International Business Machines Corp. 2000 - 2002
# All Rights Reserved.
#
# US Government Users Restricted Rights - Use, duplication or
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
##############################################################################
#
# MAKEFILE for SQL Procedures samples on Solaris
#
# Enter one of the following commands 
#
#   make <app_name>        - Builds the program designated by <app_name>
#
#   make all               - Builds the all the supplied sample programs
#
#   make clean             - Erases intermediate files
#   make cleanall          - Erases all files produced in the build process,
#                             except the original source files
#
# The makefile contains the following sections:
#    1 -- VARIABLES
#    2 -- MAKE CATEGORIES
#    3 -- COMMANDS TO MAKE INDIVIDUAL SAMPLES
#
#
##############################################################################
#                  1 -- VARIABLES                                
##############################################################################

# This file assumes the DB2 instance path is defined by the variable HOME.
# It also assumes DB2 is installed under the DB2 instance.
# If these statements are not correct, update the variable DB2PATH. 
DB2PATH = $(HOME)/sqllib

BLDAPP=bldapp

# To connect to a remote SAMPLE database cataloged on the client machine
# with another name, update the DB variable.
DB=sample
# Set UID and PWD if neccesary  
UID=
PWD=

COPY=cp
ERASE=rm -f

#############################################################################
#  2 -- MAKE CATEGORIES
#              2a - make all(= all samples)
#              2b - make clean
#              2a - make cleanall
#############################################################################

#****************************************************************************
#                  2a - make all
#****************************************************************************

all : \
	basecase baseif \
	dynamic \
	iterate \
	leave loop \
	nestcase nestif \
	repeat rsultset \
	tbsel \
	whiles \
	NestedSP

#****************************************************************************
#                  2b - make clean
#****************************************************************************

 
clean : \
	cleangen \
	cleanemb

cleangen :
	$(ERASE) *.class *.o *.map message.*

cleanemb :
	$(ERASE) basecase.c baseif.c 
	$(ERASE) dynamic.c
	$(ERASE) iterate.c
	$(ERASE) leave.c loop.c
	$(ERASE) nestcase.c nestif.c
	$(ERASE) repeat.c
	$(ERASE) tbsel.c
	$(ERASE) whiles.c

#****************************************************************************
#                  2c - make cleanall
#****************************************************************************

cleanall : \
	clean
	$(ERASE) *.bnd
	$(ERASE) basecase baseif 
	$(ERASE) dynamic
	$(ERASE) iterate
	$(ERASE) leave loop
	$(ERASE) nestcase nestif
	$(ERASE) repeat rsultset
	$(ERASE) tbsel
	$(ERASE) whiles

#############################################################################
#  3 -- COMMANDS TO MAKE INDIVIDUAL SAMPLES
#                  3a -  embedded SQL client samples
#                  3b -  CLI universal client sample
#                  3c -  JDBC client sample
#############################################################################

#****************************************************************************
#                 3a -  embedded SQL client samples
#****************************************************************************

basecase :
	$(BLDAPP) basecase $(DB) $(UID) $(PWD)

baseif :
	$(BLDAPP) baseif $(DB) $(UID) $(PWD)

dynamic :
	$(BLDAPP) dynamic $(DB) $(UID) $(PWD)

iterate :
	$(BLDAPP) iterate $(DB) $(UID) $(PWD)

leave :
	$(BLDAPP) leave $(DB) $(UID) $(PWD)

loop :
	$(BLDAPP) loop $(DB) $(UID) $(PWD)

nestif :
	$(BLDAPP) nestif $(DB) $(UID) $(PWD)

nestcase :
	$(BLDAPP) nestcase $(DB) $(UID) $(PWD)

repeat :
	$(BLDAPP) repeat $(DB) $(UID) $(PWD)

tbsel :
	$(BLDAPP) tbsel $(DB) $(UID) $(PWD)

whiles :
	$(BLDAPP) whiles $(DB) $(UID) $(PWD)

#****************************************************************************
#                 3b -  CLI client samples
#****************************************************************************

rsultset :
	$(BLDAPP) rsultset

#****************************************************************************
#                 3c - JDBC client samples 
#****************************************************************************

NestedSP : NestedSP.java
	javac Util.java
	javac NestedSP.java
