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
char *strB="abcdee";
char strC[20]; // for strcpy , though strC can be overwritten, but the program may be crash if x of [x] is not large enough to hold the src-string.
//char *strD=(char*)malloc(100);
char strD[100]="xxxx";
//strchr 
printf("%s\n",strchr(strA,'d'));

//strcmp
printf("%d\n",strcmp(strA,strB));


printf("%s\n",strC);	
//strcpy
strcpy(strC,strA);
printf("%s\n",strC);  // why  can print all the "abcdef" when strC[2]; ??
//strlen
printf("strlen:%d\n",strlen(strA)); 

//strncat 

strcpy(strD,strA);
printf("%s\n",strD);	
strncat(strD,strB,3);
printf("%s\n",strD); 
return 0;

} 
