/**
name: test ptr & array
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.对指针进行加1 操作，得到的是下一个元素的地址，而不是原有地址值直接加1。
2.一个类型为T 的指针的移动，以sizeof(T) 为移动单位

refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

int a[5][5];
int (*p)[4];
p = a;
printf("a_ptr=%#p,p_ptr=%#p\n",&a[4][2],&p[4][2]);
printf("%p,%d\n",&p[4][2] - &a[4][2],&p[4][2] - &a[4][2]); //4*4+2 - (5*4+2)

	
return 0;
}


