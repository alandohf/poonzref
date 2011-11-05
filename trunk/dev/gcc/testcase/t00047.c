/**
name:  test null pointer
purpose:  test heap size
dependence: 
compiler: tcc/dev-cpp
summary:


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
