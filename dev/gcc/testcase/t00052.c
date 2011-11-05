/**
name:  test realloc()
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:

//mArray = calloc( count, sizeof(struct V)) 

**/

#include <stdio.h> 
#include <stdlib.h> 

int main(int argc, char* argv[]) 
{ 
    int *a = NULL;
    a=calloc(10,sizeof(int));
    int i = 0;
    for (i=0;i<10;i++){
//     *(a+i)=i;
      printf("value:%d\n",*(a+i));
    }
    realloc(a,sizeof(int)*20);
    for (i=0;i<20;i++){
     *(a+i)=30+i;
      printf("value:%d\n",*(a+i));
    }
    free(a);
    return 0; 
} 
 