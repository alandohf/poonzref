/**
name:  modify var 's value in function by pointer !
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:

refs: 
**/

#include <stdio.h>
void fun(int *p);
int main(int argc,char *argv[]){
int i = 10;
printf("%d\n",i);

fun(&i);

printf("%d\n",i);

int *p;
*p=100;
fun(p);
printf("%p\n",p);	
printf("%d\n",*p);

return 0;

}




void fun(int *p)
{
*p=1000;
printf("%p\n",p);	
}
