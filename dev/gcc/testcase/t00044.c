/**
name:  test function pointer
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:


refs: 
**/

#include <stdio.h>
char* fun(char *a,char *b);
int main(int argc,char *argv[]){
char *ret;
char* (*fp)(char*,char*);
fp=&fun;
//fp=&fun; // equals
ret=(*fp)("xxx","yyy");
printf("%s\n",ret);	
return 0;

}


char* fun(char *a,char *b){
int i = strcmp(a,b);
if(i){
return b;
}else {
return a;
}

}