/**
name:  test strings  
purpose:  cmpare  0056&& 0059  : char strC[2];
dependence: 
compiler: tcc/dev-cpp
summary:

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
printf("%i\n",strncmp(strA,strB,6));
return 0;

} 
