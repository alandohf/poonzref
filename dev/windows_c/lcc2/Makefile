# Wedit Makefile for project getFilename
SRCDIR=d:\pzw\prj\poonzref\dev\windows_c
CFLAGS=-I"d:\program\lcc\include"  -g2 
CC=$(LCCROOT)\bin\lcc.exe
LINKER=$(LCCROOT)\bin\lcclnk.exe
OBJS=\
	getfilename.obj

LIBS=
EXE=getFilename.exe

$(EXE):	$(OBJS) Makefile
	$(LINKER)  -subsystem windows -o $(SRCDIR)\lcc2\getFilename.exe $(OBJS) $(LIBS)

# Build getFilename.c
GETFILENAME_C=\

getfilename.obj: $(GETFILENAME_C) $(SRCDIR)\getfilename.c
	$(CC) -c $(CFLAGS) $(SRCDIR)\getfilename.c

link:
	$(LINKER)  -subsystem windows -o $(SRCDIR)\lcc2\getFilename.exe $(OBJS) $(LIBS)

clean:
	del $(OBJS) getFilename.exe
