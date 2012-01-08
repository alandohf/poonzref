/**
name: test ptr & array
purpose: 数组作为函数参数
dependence: 
compiler: tcc/dev-cpp
summary:
1.对指针进行加1 操作，得到的是下一个元素的地址，而不是原有地址值直接加1。
2.一个类型为T 的指针的移动，以sizeof(T) 为移动单位

refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

void fun(char a[10]);
char b[10] ="abcdefg";
fun(b);
//fun(b[10]);
//fun(b[0]);
//fun(&b);


	
return 0;
}




void fun(char a[10])
{
char c = a[3];
printf("%c\n",c);
}