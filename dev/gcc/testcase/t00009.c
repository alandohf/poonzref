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
void * p1;
p=p1;
//p1=p;
return 0;
}
