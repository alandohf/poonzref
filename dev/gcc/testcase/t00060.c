/**
name:  test strings  
purpose:  strncmp() vs strcmp()
dependence: 
compiler: tcc/dev-cpp
summary:
1.ת����ascii �Ĳ�ֵ
2.�ı�strA,strB��ֵ�۲����
3.�ı�strncmp�Ĳ���3�۲����
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
