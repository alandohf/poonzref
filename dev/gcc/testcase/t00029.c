/**
name: test  address
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1. 一个地址单元能够代表8位，即一个字节。
2.how the stack store data: high addr -> low addr 
refs:
**/

#include <stdio.h>
#include <stdlib.h>
#ifndef _ABC_
#pragma message("hello , guy!")
#endif
int main(int argc,char *argv[]){
char a,b,c,d;
int *p=NULL;
a=1;
b=2;
c=3;
d=127; // greater than 127 is invalid !
printf("%p\n",&a);
printf("%p\n",&b);
printf("%p\n",&c);
printf("%p\n",&d);

printf("%d\n",a);
printf("%d\n",b);
printf("%d\n",c);
printf("%d\n",d);
int x,y,z;
x=1;
y=2;
z=3;
printf("%p\n",&x);
printf("%p\n",&y);
printf("%p\n",&z);
printf("%p\n",p);
system("PAUSE");
return 0;
}

