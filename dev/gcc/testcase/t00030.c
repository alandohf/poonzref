/**
name: test  address
purpose: ֱ�ӶԵ�ַ��������ã���������ֵ��
dependence: 
compiler: tcc/dev-cpp
summary:
1. if the program compile ok but run crash , it maybe use the wrong address!!
refs:
**/

#include <stdio.h>

int main(int argc,char *argv[]){
int i ;
int *pt;
pt=&i;
printf("%p\n",pt);
	
int *p=NULL;
p=(int *)0x0012ff5c ;
*p= 99;
//int i = *p;
printf("0x0012ff5c addr : %p\n",p);
printf("0x0012ff5c value: %i\n",*p);

*((int *) 0x0012ffe0) = 15;
printf("0x0012ffe0 value: %i\n",*((int *) 0x0012ffe0));

system("PAUSE");
return 0;
}


