#first makefile
GCC=C:\Dev-Cpp\bin\gcc.exe
OUTPUTDIR=C:\ccoutput
RM=C:\Dev-Cpp\bin\rm.exe
main.exe:main.o bubbleSort.o
	$(GCC) -o $(OUTPUTDIR)\main.exe $(OUTPUTDIR)\main.o $(OUTPUTDIR)\bubbleSort.o
main.o:main.c bubbleSort.h
	$(GCC) -pedantic -Os -c main.c -o  $(OUTPUTDIR)\main.o -std=c99
bubbleSort.o:bubbleSort.c bubbleSort.h 
	$(GCC) -pedantic -Os -c bubbleSort.c -o $(OUTPUTDIR)\bubbleSort.o -std=c99
clean:
	$(RM) $(OUTPUTDIR)\bubbleSort.o $(OUTPUTDIR)\main.o
