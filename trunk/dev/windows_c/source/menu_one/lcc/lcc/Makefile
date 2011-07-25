# Wedit Makefile for project menu
SRCDIR=d:\pzw\prj\poonzref\dev\windows_c\source\menu_one\lcc
CFLAGS=-I"d:\program\lcc\include"  -g2 
CC=$(LCCROOT)\bin\lcc.exe
LINKER=$(LCCROOT)\bin\lcclnk.exe
OBJS=\
	menu_one.res \
	menu_one.obj

LIBS=
EXE=menu.exe

$(EXE):	$(OBJS) Makefile
	$(LINKER)  -subsystem windows -o $(SRCDIR)\lcc\menu.exe $(OBJS) $(LIBS)

# Build menu_one.res
MENU_ONE_RC=\
	$(SRCDIR)\resource.h\
	d:\program\lcc\include\windows.h\

menu_one.res:	$(MENU_ONE_RC) $(SRCDIR)\menu_one.rc
	$(LCCROOT)\bin\lrc.exe -I$(SRCDIR) -I"d:\program\lcc\include"  $(SRCDIR)\menu_one.rc

# Build menu_one.c
MENU_ONE_C=\
	$(SRCDIR)\resource.h\

menu_one.obj: $(MENU_ONE_C) $(SRCDIR)\menu_one.c
	$(CC) -c $(CFLAGS) $(SRCDIR)\menu_one.c

link:
	$(LINKER)  -subsystem windows -o $(SRCDIR)\lcc\menu.exe $(OBJS) $(LIBS)

clean:
	del $(OBJS) menu.exe
