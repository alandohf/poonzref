/**
name:  test strings  : test strcat
purpose: test strcat()
dependence: 
compiler: tcc/dev-cpp
summary:


**/
#include <windows.h>
#include <stdio.h> 
#include <stdlib.h>
/**
name:  test strings 
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:


**/
#include <windows.h>
#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char* argv[]) 
{ 
char *strA="abcdef";
char *strB="123456";
char *strC=NULL;
strC=(char *)malloc(100);

if( NULL == strC ){
printf("error\n");
exit(1);
}

printf("%p\n",strC);

//printf("%s\n",strcat(strA,strB));	
strcpy(strC,strA);
strC=strcat(strC,strB);
printf("%s\n",strC);
printf("%p\n",strC);
free(strC);
    return 0; 
} 
 

//	
//	int main(int argc, char* argv[]) 
//	{ 
//	char *strA="abcdef";
//	char *strB="123456";
//	char *strC=NULL;
//	strC=malloc(100);
//	if( NULL == strC ){
//	printf("error\n");
//	exit(1);
//	}
//	//printf("%s\n",strcat(strA,strB));	
//	//	strC=strcat(strA,strB); // compile not pass in vc !!
//	//printf("%s\n",strC);
//	    return 0; 
//	} 
//	 