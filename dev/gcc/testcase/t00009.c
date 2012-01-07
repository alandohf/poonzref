/**
test void 

tcc is not so good to detect the void problem! such as :
1. void a ;
2.
float * p;
void * p1;
p=p1;

**/

#include <stdio.h>

int main(int argc,char *argv[]){
float * p;
void * vp; //error: invalid conversion from `void*' to `float*'
//p=vp; //error: invalid conversion from `void*' to `float*'
vp=p;
return 0;
}
