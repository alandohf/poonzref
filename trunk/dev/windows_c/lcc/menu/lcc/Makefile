# Wedit Makefile for project menu1
SRCDIR=d:\pzw\prj\poonzref\dev\windows_c\lcc\menu
CFLAGS=-I"d:\program\lcc\include"  -g2 
CC=$(LCCROOT)\bin\lcc.exe
LINKER=$(LCCROOT)\bin\lcclnk.exe
OBJS=\
	menu.res \
	menu.obj

LIBS=
EXE=menu1.exe

$(EXE):	$(OBJS) Makefile
	$(LINKER)  -subsystem windows -o $(SRCDIR)\lcc\menu1.exe $(OBJS) $(LIBS)

# Build menu.res
MENU_RC=\
	$(SRCDIR)\resource.h\

menu.res:	$(MENU_RC) $(SRCDIR)\menu.rc
	$(LCCROOT)\bin\lrc.exe -I$(SRCDIR) -I"d:\program\lcc\include"  $(SRCDIR)\menu.rc

# Build menu.c
MENU_C=\
	$(SRCDIR)\resource.h\

menu.obj: $(MENU_C) $(SRCDIR)\menu.c
	$(CC) -c $(CFLAGS) $(SRCDIR)\menu.c

link:
	$(LINKER)  -subsystem windows -o $(SRCDIR)\lcc\menu1.exe $(OBJS) $(LIBS)

clean:
	del $(OBJS) menu1.exe
