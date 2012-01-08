/**
name: test  precompile
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary: not work on g++
refs:
http://blog.csdn.net/normallife/article/details/3710838

**/

#include <stdio.h>
#include <stdlib.h>
#ifndef _ABC_
#pragma message("hello , guy!")
#endif
int main(int argc,char *argv[]){
system("PAUSE");
return 0;
}
