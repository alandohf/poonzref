/**
name:  test null pointer
purpose:  
dependence: 
compiler: tcc/dev-cpp
summary: char *p=0; same as : char *p1=NULL; 
1. 

refs: 
**/

#include <stdio.h>
char* fun(char *a,char *b);
int main(int argc,char *argv[]){
char *p=0;
printf("%p\n",p);
char *p1=NULL;
printf("%p\n",p1);
return 0;

}
