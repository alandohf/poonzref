/**
name:  test strings  
purpose:  test strrchr()
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
char *strB="abcddf";

printf("%s\n",strrchr(strA,'d'));
printf("%s\n",strrchr(strB,'d')); // the direction is different !
return 0;

} 