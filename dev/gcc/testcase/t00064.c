/**
name:  test strstr  
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.返回指向第一次出现needle位置的指针，如果没找到则返回NULL。
refs:
http://baike.baidu.com/view/745156.htm
**/
// without  windows.h/string.h , vc6 not recognize  strchr,strcmp...
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
int main(int argc, char* argv[]) 
{ 
char *strA="abcdef";
char *strB="cd";

printf("strstr:%s\n",strstr(strA,strB)); 


return 0;

} 
