/**
name:  test strstr  
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
char *strtok(char *restrict s1, const char *restrict delimiters);
refs:

**/
// without  windows.h/string.h , vc6 not recognize  strchr,strcmp...
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
int main(int argc, char* argv[]) 
{ 
char *strA="abcdef";

printf("strstr:%s\n",strtok(strA,"d"));  // "",not ''
printf("strstr:%s\n",strtok(strA,"d")+2);  // "",not ''


return 0;

} 
