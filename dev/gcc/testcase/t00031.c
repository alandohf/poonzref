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
int i ;
int *pt;
pt=&i;
//printf("%p\n",pt);
int *p = (int *) 0x0022FF55;
*p = 0x1;
//p = NULL;  // why invaild ?
printf("memaddr value: %p\n",p);
printf("mem value: %d\n",*p);
system("PAUSE");
return 0;
}


