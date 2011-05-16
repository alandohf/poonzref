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
# MAKEFILE for XML JDBC samples on Unix
#
# Enter one of the following commands 
#
#   make <app_name>        - Builds the program designated by <app_name>.
#
#   make all               - Builds all supplied sample programs except GSS API
#                            plugin samples. 
#
#   make srv               - Builds samples that can only be run on the server,
#                            includes stored procedures.
#
#   make call_srv          - Builds all client programs that call stored 
#                            procedures. 
#
#   make all_client        - Builds all client samples (all programs in the
#                             'call_srv' and 'client_run' categories).
#
#   make client_run        - Builds all programs that run completely on the
#                            client (not ones that call stored procedures).
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
#
##############################################################################
#                  1 -- VARIABLES                                     
##############################################################################

# This file assumes the DB2 instance path is defined by the variable HOME.
# It also assumes DB2 is installed under the DB2 instance.
# If these statements are not correct, update the variable DB2PATH. 
DB2PATH = $(HOME)/sqllib

COPY=cp
ERASE=rm -f

#############################################################################
#  Generic rule to make a class from a java source file
#############################################################################

.SUFFIXES : .class .java

.java.class :
	javac $<

#############################################################################
#  2 -- MAKE CATEGORIES
#              2a - make all (srv + all_client)
#              2b - make all_client
#              2c - make srv
#              2d - make call_srv
#              2e - make client_run
#              2f - make clean
#              2g - make cleanall
#############################################################################

#****************************************************************************
#                  2a - make all (srv + all_client)
#****************************************************************************

all : \
        srv \
        all_client

#****************************************************************************
#                  2b - make all_client (call_srv + client_run)
#****************************************************************************

all_client : \
        call_srv \
        client_run 

#****************************************************************************
#                  2c - make srv
#****************************************************************************

srv : \
        Simple_XmlProc

#****************************************************************************
#                  2d - make call_srv
#****************************************************************************

call_srv : \
        Simple_XmlProc_Client 

#****************************************************************************
#                  2e - make client_run
#****************************************************************************

client_run : \
	XmlSchema XmlRunstats XmlIndex XmlConst XmlInsert XmlUpDel \
	XmlRead RelToXmlDoc RelToXmlType XmlToTable \
	XmlDecomposition 

#****************************************************************************
#                  2f - make clean
#****************************************************************************

clean :
	$(ERASE) *.class 

#****************************************************************************
#                  2g - make cleanall
#****************************************************************************

cleanall : \
	clean
	$(ERASE) $(DB2PATH)/function/Simple_XmlProc.class

#############################################################################
#  3 -- COMMANDS TO MAKE INDIVIDUAL SAMPLES
#                  3a -  standalone applications
#                  3b -  client/server applications
#############################################################################


#****************************************************************************
#                  3a -  standalone applications
#****************************************************************************

XmlSchema : XmlSchema.class

XmlRunstats : Util.class XmlRunstats.class 

XmlIndex : Util.class XmlIndex.class

XmlConst : Util.class XmlConst.class

XmlInsert : Util.class XmlInsert.class 

XmlUpDel : Util.class XmlUpDel.class

XmlToTable : Util.class XmlToTable.class

XmlRead : Util.class XmlRead.class

RelToXmlDoc : Util.class RelToXmlDoc.class

RelToXmlType : Util.class RelToXmlType.class

XmlDecomposition : Util.class XmlDecomposition.class 

#****************************************************************************
#                  3b -  client/server applications
#****************************************************************************

#-----------------Simple_XmlProc_Client / Simple_XmlProc--------------------------#
# Note: before you execute Simple_XmlProc_Client for the first time, you must call the
# Simple_XmlProc_Create.db2 CLP script to catalog the methods in Simple_XmlProc as stored
# procedures. Call Simple_XmlProc_Drop.db2 to uncatalog the methods in Simple_XmlProc.

SpCat :
	spcat_xml

Simple_XmlProc_Client : Util.class Simple_XmlProc_Client.class

Simple_XmlProc : Simple_XmlProc.class
	$(ERASE) $(DB2PATH)/function/Simple_XmlProc.class
	$(COPY) Simple_XmlProc.class $(DB2PATH)/function
	spcat_xml

