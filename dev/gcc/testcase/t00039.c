/**
name: test ptr & array
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.对指针进行加1 操作，得到的是下一个元素的地址，而不是原有地址值直接加1。
2.一个类型为T 的指针的移动，以sizeof(T) 为移动单位
3.数组和指针的表达可以互换。指针更灵活。
4.g++有严格的类型检查！类型要一致。
refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

int a[5][5]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
int (*p)[4];
p = (int(*)[4] )a;
printf("a_ptr=%#p,p_ptr=%#p\n",&a[4][2],&p[4][2]);
printf("a_ptr=%d,p_ptr=%d\n",a[4][2],p[4][2]); // a[0],p[0]维度长度不一样，导致相同下标，索引到得元素值不一样。a:4*5+2+1 vs p:4*4+2+1
printf("a_ptr=%d,p_ptr=%d\n",a[0][2],p[0][2]); 
printf("%p,%d\n",&p[4][2] - &a[4][2],&p[4][2] - &a[4][2]); //4*4+2 - (5*4+2)

	
return 0;
}


