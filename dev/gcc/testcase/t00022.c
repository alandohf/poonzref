/**
name: test escape character
purpose: 
compiler: tcc/dev-cpp
summary:
refs:
**/

#include <stdio.h>
int main(int argc,char *argv[]){

printf("a\vb\n");
printf("a\bb\n");

return 0;

}







