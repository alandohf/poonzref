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

char a[5]={'A','B','C','D'};
char (*p3)[3] = &a;
char (*p4)[3] = a;

char (*p5)[10] = &a;
char (*p6)[10] = a;

char (*p7)[16] = &a;
char (*p8)[16] = a;

printf("%p\n",a);
printf("%p\n",&a);

printf("%p\n",p3);
printf("%p\n",p4);

printf("%p\n",p3+1); // 地址偏移跟着数组指针所指的数组长度走 
printf("%p\n",p4+1);

printf("%p\n",p3+2);
printf("%p\n",p4+2);

printf("%p\n",p5+1);
printf("%p\n",p6+1);

printf("%p\n",p7+1);
printf("%p\n",p8+1);// 地址偏移跟着数组指针所指的数组长度走 


return 0;
}


