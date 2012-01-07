/**

test storage area adress allocation.

tcc 不支持 strcpy??

**/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

int a = 0; //全局初始化区
char *p1; //全局未初始化区


int main(int argc,char *argv[]){

int b; //栈
char s[] = "abc"; //栈
char *p2; //栈
char *p3 = "123456"; //123456\\0在常量区，p3在栈上。
static int c =0; //全局（静态）初始化区
////p1 = new char[10]; 
////p2 = new char[20]; 
////分配得来的和字节的区域就在堆区。
//strcpy(p1, "123456");
strcpy(s, "123456");
// 对于 s/ p1 ，s可以用strcpy改写，但p1不可以。因为p1未指向分配好的内存。
//123456 放在常量区，编译器可能会将它与p3所指向的\"123456\"优化成一个地方。

printf("addr of a :%p\n",&a);
printf("addr of p1:%p\n",&p1);
printf("addr of b :%p\n",&b);
printf("addr of c :%p\n",&c);
printf("value of s :%s\n",s);
//留意地址值的共性	
return 0;
}
