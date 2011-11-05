/**
test extern keyword
1. auto init to zero
2.global var
3. can be omitted when in single file

D:\pzw\prj\poonzref\dev\gcc\testcase>d:\program\tcc\tcc.exe t00010.c t00010_1.c -o t00010.exe

**/

#include <stdio.h>

//extern int a = 9; // ';' expected  不能这样写
extern int a; 
a=9;

//extern int extvar ; // ok
//extern  extvar ; // ok too!
extern double  extvar ; // ok too! why ??? 
extern char  extvar ; //  complie ok , but the result unexpect !!
//extern void extfn(void); // ok 
extern  extfn(); // ok  too!
//extvar = 100;  // 'extvar' defined twice
int b = 10;
int c;
int main(int argc,char *argv[]){
printf("a=%d,b=%d c=%d\n",a,b,c);
printf("extvar=%d\n",extvar);
extfn();
return 0;
}
