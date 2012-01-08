/**
name: test ptr & array
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.对指针进行加1 操作，得到的是下一个元素的地址，而不是原有地址值直接加1。
2.一个类型为T 的指针的移动，以sizeof(T) 为移动单位
3. a[0] , a[1].. 连续存放,可以单独看成是数组 {a[0],a[1],a[2]} 的各个元素。a[n] 是一维数组。
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

int (*p_a)[4];
p_a=&(a[0]); // 测试p_a的偏移；p_a是指向数组的指针。p_a+1 偏移了一个数组的长度，而不是简单加1个int的长度。
printf("%p\t%p\t%p\t%d\n",p,p_a,p_a+1,*(*(p_a+1)));

int b = (0,1,100);
printf("b:%d\n",b);

return 0;
}


