/**
name: test  address
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1. if the program compile ok but run crash , it maybe use the wrong address!!
refs:
**/

#include <stdio.h>
#include <windows.h>
int main(int argc,char *argv[]){
const int i = 9;
//int *pt=&i;//借助i找出编译器分配的地址
char c_a = 'a',c_b = 'b';
int i_a = 1,i_b = 1;
	
printf("c_a：%p\n",&c_a);//high addr 
printf("c_b：%p\n",&c_b);//low addr
printf("i_a：%p\n",&i_a);
printf("i_b：%p\n",&i_b);
	
//printf("%p\n",pt);
//printf("%p\n",pt+1);
//printf("%p\n",pt-1);
const int *p = (int *) (((int) &i));
printf("%p\n",p);
 *p = 2;//g++ 比 tcc　严格；此句在g++不通过
//p = NULL;  // why invaild ?
printf("memaddr value: %p\n",p);
printf("mem value: %d\n",*p);
system("PAUSE");
return 0;
}


