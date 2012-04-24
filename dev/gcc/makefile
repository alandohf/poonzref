######################################COMMON SETTINGS START ##################################

DEL			=	del /F /Q
OUTPUTDIR	=	C:\ccoutput
ROOT		=	d:\Soft_remove\CodeBlocks\MinGW
INCLUDEDIR  =	$(ROOT)\INCLUDE:$(ROOT)\MFC\INCLUDE:$(ROOT)\MFC\ATL\INCLUDE
LIBPATH		=	$(ROOT)\LIB:$(ROOT)\mingw32\lib
#make use of the system environment 
PATH		=	$(ROOT)\bin
LIB			=	$(LIBPATH):$(LIB)
INCLUDE		=	$(INCLUDEDIR):$(INCLUDE)
CC			=	g++.exe
LD			=	ld.exe
LINK		=	ld.exe

#~ CFLAGS		=	-pedantic -Os -g -Wall 
LNK_FLAGS   =   -L $(LIBPATH)
CLEANS		=	*.o *.obj *.res *.aps *.exe *.idb *.pdb
######################################COMMON SETTINGS END ##################################
#~ CCDIR=d:\Soft_remove\CodeBlocks\MinGW\bin
#~ CC=$(CCDIR)\gcc.exe
#~ RM=$(CCDIR)\rm.exe
#~ OUTPUTDIR=C:\ccoutput

### #first version of  makefile
### GCC=C:\Dev-Cpp\bin\gcc.exe
### OUTPUTDIR=C:\ccoutput
### RM=C:\Dev-Cpp\bin\rm.exe
### main.exe:main.o bubbleSort.o
### 	$(GCC) -o $(OUTPUTDIR)\main.exe $(OUTPUTDIR)\main.o $(OUTPUTDIR)\bubbleSort.o
### main.o:main.c bubbleSort.h
### 	$(GCC) -pedantic -Os -c main.c -o  $(OUTPUTDIR)\main.o -std=c99
### bubbleSort.o:bubbleSort.c bubbleSort.h 
### 	$(GCC) -pedantic -Os -c bubbleSort.c -o $(OUTPUTDIR)\bubbleSort.o -std=c99
### clean:
### 	$(RM) $(OUTPUTDIR)\bubbleSort.o $(OUTPUTDIR)\main.o
### 

### #second version of makefile
### GCC=C:\Dev-Cpp\bin\gcc.exe
### OUTPUTDIR=C:\ccoutput
### RM=C:\Dev-Cpp\bin\rm.exe
### OBJECTS=$(OUTPUTDIR)\main.o $(OUTPUTDIR)\myh.o
### main.exe:main.o myh.o
### $(GCC) -o $(OUTPUTDIR)\main.exe $(OBJECTS)
### main.o:main.c myh.h
### $(GCC) -pedantic -Os -c main.c -o  $(OUTPUTDIR)\main.o -std=c99
### myh.o:myh.c
### $(GCC) -pedantic -Os -c myh.c -o $(OUTPUTDIR)\myh.o -std=c99
### clean:
### $(RM)  $(OUTPUTDIR)\\*.o
### #使用通配符*需要转义:(\*)


#third version of makefile
#CC is one of several implicit variables automatically defined in a make session
#CC是内置变量，默认值是cc，这里改变CC的取值

####################################################################################

TARGET		= 	alert_win
SOURCES		= 	poonapi.cpp alert_win.cpp
OBJECTS		=	$(TARGET).o  poonapi.o
PROG		= 	$(TARGET).exe
CFLAGS		=	-g -o $(OUTPUTDIR)\$(TARGET).exe
$(PROG):$(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES) $(LNK_FLAGS)
$(OBJECTS):$(SOURCES)
	g++ -c $(SOURCES)

#~ $(CC) $(CFLAGS) $(SOURCES)
#~ $(OBJECTS):$(SOURCES)
#~ g++ -c $(SOURCES)



#~ $(LINK) $(LNK_FLAGS) $(OBJECTS)
#~ $(LINK) $(LNK_FLAGS) $(OBJECTS)	
#~ -@COPY $(@F) $(OUTPUTDIR)\$(@F)
#~ -@$(DEL) $(CLEANS)
#~ $(CC) $(CFLAGS) $(SOURCES)
clean:
	-@$(DEL) $(CLEANS)
