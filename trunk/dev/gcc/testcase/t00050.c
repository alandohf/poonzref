/**
name:  test array & '\0'
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:


**/

#include <stdio.h> 
#include <stdlib.h> 

int main(int argc, char* argv[]) 
{ 
    int *a = NULL;
    a=malloc(10*sizeof(int));
    int i = 0;
    for (i=0;i<10;i++){
     *(a+i)=i;
      printf("value:%d\n",*(a+i));
    }
    char *p;
    p=malloc(10*sizeof(char));
    int j = 0;
    for (j=0;j<10;j++){
     *(p+j)=65+j;
      printf("value:%c\n",*(p+j));
    }
    
    return 0; 
} 
 