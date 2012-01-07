CC=C:\Dev-Cpp\bin\gcc.exe
RM=C:\Dev-Cpp\bin\rm.exe
OUTPUTDIR=C:\ccoutput
OBJECTS=main.o bubbleSort.o
main.exe:main.o bubbleSort.o
	$(CC) -o $(OUTPUTDIR)\main.exe $(OBJECTS)
main.o:main.c bubbleSort.h
bubbleSort.o:bubbleSort.c
clean:
	$(RM) *.o

