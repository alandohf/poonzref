/**
name:  ��modify�� var 's value in function by pointer !
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:

refs: 
**/

#include <stdio.h>

void fun(int *);
int main(int argc,char *argv[]){
int i = 9;
int j=10;
int *ip;ip=&j;// ip=&j; not *ip = j; ��������������Ϊ����ip��δָ����Ч��ַ���޷�������ֵ��

//printf("%d\n",i);

fun(&i);

printf("%d\n",i);


fun(ip);
//printf("%p\n",ip);	
printf("%d\n",*ip);

return 0;

}




void fun(int *p)
{
*p=1000+*p;
printf("%p\n",p);	
}
