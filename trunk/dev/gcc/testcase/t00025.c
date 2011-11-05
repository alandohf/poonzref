/**
name: test ++ sign
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
refs:
**/

#include <stdio.h>


int main(int argc,char *argv[]){
int i = 1;

printf("%d\n",i);
i=i>>1;
printf("%d\n",i);
i=i>>10;
printf("%d\n",i);
i=i<<1;
printf("%d\n",i);
i=i<<1;
printf("%d\n",i);
int a,b;
a= 2;
b= -2;
printf("%d\n",a/b);
printf("%d\n",a%b);
printf("%d\n",a%-b);

system("PAUSE");
return 0;
}

