/**
name: test array & pointer 
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

int i=0;
int *a[10]; //指针数组
int (*p)[10]; // 数组指针
a[0] = &i;

int b[10];
p=&b; // not b 
return 0;
}


