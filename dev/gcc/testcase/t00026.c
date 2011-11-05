/**
name: test  malloc &  var life
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
refs:
**/

#include <stdio.h>

char *testmalloc(void);
int main(int argc,char *argv[]){
printf("%s\n",testmalloc());
system("PAUSE");
// free(p); // 'p' undeclared
return 0;
}

char *testmalloc(void){
char *p;
p=(char*)malloc(100);
sprintf(p,"%s\n","abcdefg");
printf("%s\n",p);
return p;
}

