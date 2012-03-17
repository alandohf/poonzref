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
LIBS		=	kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib \
				shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

#define THE TOOLS
#~ CC   RC IS PREDEFINED
#~ CC			=	cl.exe
LINK		=	link.exe
#~ RC			=	rc.exe

#~ CFLAGS		=	/c /I$(INCLUDEDIR) /Fo$(OBJECTS) 
CFLAGS		=	/c /I$(INCLUDEDIR)
LNK_FLAGS   =   /DEFAULTLIB:$(LIBS) /SUBSYSTEM:WINDOWS /OUT:$(PROG)
CLEANS		=	*.obj *.exe $(OUTPUTDIR)\*.obj

######################################COMMON SETTINGS END ##################################
TARGET		= 	t00003_BasicWindowWithMenu
OBJECTS		=	$(TARGET).obj
PROG		= 	$(TARGET).exe



#~ DO THE JOBS
$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
#~ 收尾工作
	@COPY $(@F) $(OUTPUTDIR)\$(PROG)
#~ 运用推导法则，CC,CFLAGS会自动应用
$(OBJECTS):
#~ $(CC) $(CFLAGS) %s
#~ ECHO $(MAKE)
#~ ECHO $(PATH) $(LIB) $(INCLUDE)

#~ clean:
#~ $(DEL) $(CLEANS)
#~ end target：t00003_BasicWindowWithMenu

####################################################################################
TARGET		= 	t00004_MenuWithResponse
OBJECTS		=	$(TARGET).obj
PROG		= 	$(TARGET).exe

$(PROG):$(OBJECTS)
	$(LINK) $(LNK_FLAGS) $(OBJECTS)
	@COPY $(@F) $(OUTPUTDIR)\$(PROG)
$(OBJECTS):
####################################################################################

clean:
	$(DEL) $(CLEANS)
#~ end target：t00003_BasicWindowWithMenu

