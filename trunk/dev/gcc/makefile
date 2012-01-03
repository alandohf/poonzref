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
CC=C:\Dev-Cpp\bin\gcc.exe
RM=C:\Dev-Cpp\bin\rm.exe
OUTPUTDIR=C:\ccoutput
OBJECTS=main.o myh.o
main.exe:main.o myh.o
	$(CC) -o $(OUTPUTDIR)\main.exe $(OBJECTS)
main.o:main.c myh.h
myh.o:myh.c
clean:
	$(RM) *.o

