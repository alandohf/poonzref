/**
test asm

9.
ת��ࣺ
c:\Dev-Cpp\bin\gcc.exe -S t00073.c
���תexe:
c:\Dev-Cpp\bin\gcc.exe -c t00073.s
c:\Dev-Cpp\bin\gcc.exe -o my.exe  t00073.o


10.gcc ���ע�ͣ�ͬc !

**/


#include <stdio.h>

int main(void)
{	int a = 9;
	int b = 2;
	int *ip = &a;
	ip=&b;
	return 0;
}

