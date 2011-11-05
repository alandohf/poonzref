/**
name:  test strings 
purpose: 
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
char *strB="abcdee";
//char *strD=(char*)malloc(100);
char strD[100]="xxxx";
//strchr 
printf("%s\n",strchr(strA,'d'));

//strcmp
printf("%d\n",strcmp(strA,strB));



//strlen
printf("strlen:%d\n",strlen(strA)); 

//strncat 

//strcpy(strD,strA);
//printf("%s\n",strD);	
//strncat(strD,strB,3);
printf("%s\n",strD); 
return 0;

} 
