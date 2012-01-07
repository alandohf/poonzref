/**
test extern keyword (t00010_1.c)
1. auto init to zero
2.global var
3. can be omitted when in single file

complie :
1.using makefile
2.build

D:\pzw\prj\poonzref\dev\gcc\testcase>d:\program\tcc\tcc.exe t00010.c t00010_1.c -o t00010.exe

**/

#include <stdio.h>

//extern int a = 9; // ';' expected  不能这样写
extern int a; 
//a=9; //t00010_1.o(.data+0x0):t00010_1.c: multiple definition of `a

//extern int extvar ; // ok
//extern  extvar ; // ok too!
extern double  extvar ; // ok too! why ??? 
//extern char  extvar ; //  complie ok , but the result unexpect !! // gcc.exe error: conflicting declaration 'char extvar'
//extern void extfn(void); // ok 
extern int  extfn(); // ok  too!
//extvar = 100;  // 'extvar' defined twice
int b = 10;
int c;

int 
main(int argc,char *argv[]){
	printf("a=%d,b=%d c=%d\n",a,b,c);
	printf("extvar=%d\n",extvar);
	extfn();
return 0;
}
