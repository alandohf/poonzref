/**
name:  test strings 
purpose: test strncat() & strncmp()
dependence: 
compiler: tcc/dev-cpp
summary:


**/

#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char* argv[]) 
{ 
char strA[100]="abcdef";
char strB[8]="123456";
char strB1[8]="123acd";
char *strD;
//strD=(char*)calloc(100,0);
strD=(char*)malloc(100);
//*strD=NULL;
strncat(strA,strB,3);
printf("%s\n",strA);

strcpy(strD,strA);
strncat(strD,strB,3);
printf("%s\n",strD);

printf("%i\n",strncmp(strB1,strB,3));
printf("%i\n",strncmp(strB1,strB,4));
    return 0; 
}

 