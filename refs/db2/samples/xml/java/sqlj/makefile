#############################################################################
# Licensed Materials # Property of IBM
#
# Governed under the terms of the International
# License Agreement for Non#Warranted Sample Code.
#
# (C) COPYRIGHT International Business Machines Corp. 2006
#  All Rights Reserved.
#
#  US Government Users Restricted Rights # Use, duplication or
#  disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#############################################################################
#
# MAKEFILE for XML SQLj samples on Unix
#
# Enter one of the following commands
#
#   make <app_name>        - Builds the program designated by <app_name>.
#
#   make all               - Builds all supplied sample programs.
#
#   make clean             - Erases all intermediate files produced in the
#                            build process.
#
#   make cleanall          - Erases all files produced in the build process
#                            (all files except the original source files).
#
# The makefile contains the following sections:
#    1 -- VARIABLES
#    2 -- MAKE CATEGORIES
#    3 -- COMMANDS TO MAKE INDIVIDUAL SAMPLES
#
############################################################################
#                  1 -- VARIABLES
############################################################################

# This file assumes the DB2 instance path is defined by the variable HOME.
# It also assumes DB2 is installed under the DB2 instance.
# If these statements are not correct, update the variable DB2PATH.
DB2PATH = $(HOME)/sqllib

# To connect to a remote SAMPLE database cataloged on the client machine
# with another name, update the DB variable.
DB=sample

# Set UID, PWD, SERVER_NAME and PORT_NUMBER
UID=$(USER)
PWD=
SERVER_NAME=$(HOSTNAME)
PORT_NUMBER=50000

COPY=cp
ERASE=rm -f

#############################################################################
#  2 -- MAKE CATEGORIES
#              2a - make all 
#              2b - make clean
#              2c - make cleanall
#############################################################################

#****************************************************************************
#                  2a - make all
#****************************************************************************

all : \
         XmlSchema XmlIndex XmlConst \
         XmlInsert XmlUpDel \
         XmlRead XmlToTable \
         RelToXmlType RelToXmlDoc

#****************************************************************************
#                  2b - make clean
#****************************************************************************

clean :
	$(ERASE) XmlSchema.java
	$(ERASE) XmlIndex.java 
	$(ERASE) XmlConst.java 
	$(ERASE) XmlInsert.java 
	$(ERASE) XmlUpDel.java 
	$(ERASE) XmlRead.java 
	$(ERASE) XmlToTable.java
	$(ERASE) RelToXmlDoc.java
	$(ERASE) RelToXmlType.java

#****************************************************************************
#                  2c - make cleanall
#****************************************************************************

cleanall : \
	clean
	$(ERASE) *.class *.ser

#############################################################################
#  3 -- COMMANDS TO MAKE INDIVIDUAL SAMPLES
#                  3a -  standalone applications
#############################################################################

#***************************************************************************
#                  3a -  standalone applications
#***************************************************************************

XmlSchema : Util.class XmlSchema.sqlj 
	sqlj XmlSchema.sqlj 

XmlIndex : Util.class XmlIndex.sqlj
	sqlj XmlIndex.sqlj

XmlConst : Util.class XmlConst.sqlj
	sqlj XmlConst.sqlj 

XmlInsert : Util.class XmlInsert.sqlj
	sqlj XmlInsert.sqlj
 
XmlToTable : Util.class XmlToTable.sqlj
	sqlj XmlToTable.sqlj

RelToXmlType : Util.class RelToXmlType.sqlj
	sqlj RelToXmlType.sqlj

RelToXmlDoc : Util.class RelToXmlDoc.sqlj
	sqlj RelToXmlDoc.sqlj

XmlUpDel : Util.class XmlUpDel.sqlj
	sqlj XmlUpDel.sqlj 

XmlRead : Util.class XmlRead.sqlj
	bldsqlj XmlRead $(UID) $(PWD) $(SERVER_NAME) $(PORT_NUMBER) $(DB)

Util.class : Util.sqlj
	bldsqlj Util $(UID) $(PWD) $(SERVER_NAME) $(PORT_NUMBER) $(DB)
