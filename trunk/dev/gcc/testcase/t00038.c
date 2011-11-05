/**
name: test ptr & array
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.对指针进行加1 操作，得到的是下一个元素的地址，而不是原有地址值直接加1。
2.一个类型为T 的指针的移动，以sizeof(T) 为移动单位
3. a[0] , a[1].. 连续存放
refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

int a[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};

int *p;
p=a[1];
printf("%d\n",*(p-1));
printf("%d\n",*p);
printf("%d\n",*(p+1));
printf("%d\n",*(p+2));
printf("%d\n",*(p+3));
printf("%d\n",p[0]);

int b = (0,1,100);
printf("b:%d\n",b);

return 0;
}


