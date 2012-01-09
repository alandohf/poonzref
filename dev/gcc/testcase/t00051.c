/**
name:  test calloc
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
calloc() - allocates the specified number of bytes and initializes them to zero
//mArray = calloc( count, sizeof(struct V)) 

**/

#include <stdio.h> 
#include <stdlib.h> 

int main(int argc, char* argv[]) 
{ 
    int *a = NULL;
    a=(int*)calloc(10,sizeof(int));
    int i = 0;
    for (i=0;i<10;i++){
     *(a+i)=i;
      printf("value:%d\n",*(a+i));
    }

    return 0; 
}

 