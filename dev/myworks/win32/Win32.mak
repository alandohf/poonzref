#############################################################################################
#windows makefile 
#use nmake /f makefile [target] to compile
# use , to seperate mutiple INCLUDE PATH & LIB PATH
#############################################################################################
#~ revison log:
#~ 2012-03-20: add *.aps to clean
######################################COMMON SETTINGS START##################################
DEL			=	del /F /Q
OUTPUTDIR	=	C:\ccoutput
ROOT		=	C:\poon\wcwp\wcwp\bin\VC6CMD
INCLUDEDIR  =	$(ROOT)\INCLUDE;$(ROOT)\MFC\INCLUDE;$(ROOT)\MFC\ATL\INCLUDE
LIBPATH		=	$(ROOT)\LIB;$(ROOT)\MFC\LIB
#make use of the system environment 
PATH		=	$(ROOT)\bin;$(PATH)
LIB			=	$(LIBPATH);$(LIB)
INCLUDE		=	$(INCLUDEDIR);$(INCLUDE)
#
LIBS		=	kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib winmm.lib wininet.lib MSWSOCK.LIB ws2_32.lib wsock32.lib

#define THE TOOLS
#~ CC   RC IS PREDEFINED
#~ CC			=	cl.exe
LINK		=	link.exe
#~ RC			=	rc.exe

#~ CFLAGS		=	/c /I$(INCLUDEDIR) /Fo$(OBJECTS) 
CFLAGS		=	/c /I$(INCLUDEDIR)
LNK_FLAGS   =   /DEFAULTLIB:$(LIBS) /OUT:$(PROG)  /nologo /subsystem:windows /incremental:no /machine:I386
LF_CONSOLE  =   /DEFAULTLIB:$(LIBS) /OUT:$(PROG)  /nologo /subsystem:console /incremental:no /machine:I386
RLS_FLAGS   =   /DEFAULTLIB:$(LIBS) /OUT:$(PROG)  /nologo /subsystem:windows /incremental:no /machine:I386 /RELEASE
DBG_FLAGS   =   /DEFAULTLIB:$(LIBS) /OUT:$(PROG)  /nologo /subsystem:windows /incremental:no /machine:I386 /DEBUG
CLEANS		=	*.obj *.res *.aps *.exe *.idb *.pdb
######################################COMMON SETTINGS END ##################################
#~ t00000_DlgTemplate.c
TARGET		= 	t00000_DlgTemplate
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):
####################################################################################
TARGET		= 	t00003_BasicWindowWithMenu
OBJECTS		=	$(TARGET).obj
PROG		= 	$(TARGET).exe



#~ DO THE JOBS
$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
#~ ��β����
	@COPY $(@F) $(OUTPUTDIR)\$(PROG)
#~ �����Ƶ�����CC,CFLAGS���Զ�Ӧ��,��Ŀ��Ҳ���Ժϲ�
$(OBJECTS):
#~ $(CC) $(CFLAGS) %s
#~ ECHO $(MAKE)
#~ ECHO $(PATH) $(LIB) $(INCLUDE)

#~ clean:
#~ $(DEL) $(CLEANS)
#~ end target��t00003_BasicWindowWithMenu

####################################################################################
TARGET		= 	t00004_MenuWithResponse
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	@COPY $(@F) $(OUTPUTDIR)\$(@F)
	$(DEL) $(CLEANS)
$(OBJECTS):
####################################################################################
#t00005_BasicDlgBaseApp.c
TARGET		= 	t00005_BasicDlgBaseApp
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):
####################################################################################
#t00006_DlgBaseAppWithMenu.c
TARGET		= 	t00006_DlgBaseAppWithMenu
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):
####################################################################################

#t00007_DlaBaseAppWithRespone.c
TARGET		= 	t00007_DlaBaseAppWithRespone
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):
####################################################################################

#t00008_DAPcolorPanel.c
TARGET		= 	t00008_DAPcolorPanel
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):
####################################################################################
#~ t00009_DAPcolorPanelEx.c
TARGET		= 	t00009_DAPcolorPanelEx
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):
####################################################################################
#~ t00010_DAPcomboBox.c
TARGET		= 	t00010_DAPcomboBox
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):
####################################################################################
#~ t00011_DAPsockSMTP.c
TARGET		= 	t00011_DAPsockSMTP
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):

####################################################################################
#~ t00012_DlgConnectDB2_A.c
TARGET		= 	t00012_DlgConnectDB2_A
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):

####################################################################################
#~ t00012_DlgConnectDB2_B.c
TARGET		= 	t00012_DlgConnectDB2_B
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):


####################################################################################
#~ t00012_DlgConnectDB2_C.c
TARGET		= 	t00012_DlgConnectDB2_C
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):

####################################################################################
#~ t00013_DlgDBOperation.c
TARGET		= 	t00013_DlgDBOperation
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):
####################################################################################
#~ t00013_DlgDBOperation2.c
TARGET		= 	t00013_DlgDBOperation2
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):

####################################################################################
#~ t00013_DlgDescTable.c
TARGET		= 	t00013_DlgDescTable
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):


####################################################################################
#~ t00014_DlgDescTableSimplfied
TARGET		= 	t00014_DlgDescTableSimplfied
OBJECTS		=	$(TARGET).obj  poonapi.obj $(TARGET).res
PROG		= 	$(TARGET).exe
CPP=cl.exe
INTDIR=.
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):
####################################################################################
#~ t00015_DlgTestBgd
TARGET		= 	t00015_DlgTestBgd
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):

####################################################################################
#~ t00014_DlgDescTableColorBtn
TARGET		= 	t00014_DlgDescTableColorBtn
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):

####################################################################################
#~ t00014_DlgDescTableColorBtnRound
TARGET		= 	t00014_DlgDescTableColorBtnRound
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):

####################################################################################
#~ t00016_DlgInvokeByConsole
TARGET		= 	t00016_DlgInvokeByConsole
OBJECTS		=	$(TARGET).obj $(TARGET).res
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LF_CONSOLE) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):

####################################################################################
#~ t00000_ConsoleInvokeTemplate
TARGET		= 	t00000_ConsoleInvokeTemplate
OBJECTS		=	$(TARGET).obj  poonapi.obj $(TARGET).res
PROG		= 	$(TARGET).exe
$(PROG):$(OBJECTS)
	$(LINK) $(LF_CONSOLE) $(OBJECTS)
	-@COPY $(@F) $(OUTPUTDIR)\$(@F)
	-@$(DEL) $(CLEANS)
$(OBJECTS):












#~ ADD BUILD TARGET ABOVE
####################################################################################
clean:
	-@$(DEL) $(CLEANS)
