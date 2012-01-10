/**
name:  test strings  
purpose:  strncmp() vs strcmp()
dependence: 
compiler: tcc/dev-cpp
summary:
1.转化成ascii 的差值
2.改变strA,strB的值观察输出
3.改变strncmp的参数3观察输出
refs:
http://en.wikibooks.org/wiki/C_Programming/Strings

**/
// without  windows.h/string.h , vc6 not recognize  strchr,strcmp...
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
int main(int argc, char* argv[]) 
{ 
char *strA="abcdef";
char *strB="abcdef";
printf("%i\n",strncmp(strA,strB,4));
return 0;

} 
