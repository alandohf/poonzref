#windows makefile 
#use nmake /f makefile [target] to compile
# use , to seperate mutiple INCLUDE PATH & LIB PATH
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
LIBS		=	kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib winmm.lib wininet.lib MSWSOCK.LIB /nologo /subsystem:windows /incremental:no /machine:I386

#define THE TOOLS
#~ CC   RC IS PREDEFINED
#~ CC			=	cl.exe
LINK		=	link.exe
#~ RC			=	rc.exe

#~ CFLAGS		=	/c /I$(INCLUDEDIR) /Fo$(OBJECTS) 
CFLAGS		=	/c /I$(INCLUDEDIR)
LNK_FLAGS   =   /DEFAULTLIB:$(LIBS) /SUBSYSTEM:WINDOWS /OUT:$(PROG)
CLEANS		=	*.obj  *.res *.exe

######################################COMMON SETTINGS END ##################################
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
clean:
	-@$(DEL) $(CLEANS)
#~ end target��t00003_BasicWindowWithMenu

