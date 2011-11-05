/**
name:  modify var 's value in function by pointer !
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
p 作为参数值. int * 作为类型
4.6.2.2，无法把指针变量本身传递给一个函数
refs: 
**/

#include <stdio.h>
void fun(int *);
int* fun2(int *);
int* fun3(int **);
void fun4(int **);
int main(int argc,char *argv[]){
int i = 10;
int *p = &i;
printf("%d\n",i);

printf("%p\n",p);	
fun(p);
printf("fun : %p\n",p);	
p=fun2(p); // use 'p='
printf("fun2: %p\n",p);	
fun3(&p);
printf("fun3: %p\n",p);	
p=&i;	
printf("%p\n",p);	
fun4(&p);
printf("fun4: %p\n",p);	
	
return 0;

}




void fun(int *p)
{
p=NULL;
printf("%p\n",p);
}


int* fun2(int *p)
{
p=NULL;
printf("%p\n",p);
return p;
}



int* fun3(int **p)
{
*p=NULL;
printf("%p\n",*p);
return *p;
}



void fun4(int **p)
{
*p=NULL;
printf("%p\n",*p);
}



