# Wedit Makefile for project flash_wnd
SRCDIR=d:\pzw\prj\poonzref\dev\windows_c
CFLAGS=-I"d:\program\lcc\include"  -g2 
CC=$(LCCROOT)\bin\lcc.exe
LINKER=$(LCCROOT)\bin\lcclnk.exe
OBJS=\
	flash_wnd.obj

LIBS=
EXE=flash_wnd.exe

$(EXE):	$(OBJS) Makefile
	$(LINKER)  -subsystem windows -o $(SRCDIR)\lcc1\flash_wnd.exe $(OBJS) $(LIBS)

# Build flash_wnd.c
FLASH_WND_C=\

flash_wnd.obj: $(FLASH_WND_C) $(SRCDIR)\flash_wnd.c
	$(CC) -c $(CFLAGS) $(SRCDIR)\flash_wnd.c

link:
	$(LINKER)  -subsystem windows -o $(SRCDIR)\lcc1\flash_wnd.exe $(OBJS) $(LIBS)

clean:
	del $(OBJS) flash_wnd.exe
