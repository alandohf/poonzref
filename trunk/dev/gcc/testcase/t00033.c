/**
name: test  array & pointer
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.编译器总是把以下标的形式的操作解析为以指针的形式的操作.
refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){
char *p="abcdefg";
printf("%c\n",p[4]);
printf("%c\n",*(p+4));
system("PAUSE");

char a[]="12345678";

printf("%c\n",a[4]);
printf("%c\n",*(a+4));

return 0;
}


