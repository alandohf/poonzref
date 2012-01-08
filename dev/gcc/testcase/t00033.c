/**
name: test  array & pointer
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.编译器总是把*以下标的形式的操作*解析为*以指针的形式的操作*. 
也就是说把数组当指针处理？！
refs: 4.2.3 c in deep
**/

#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
char *p="abcdefg";
printf("%c\n",p[4]);
printf("%c\n",*(p+4));

char a[]="12345678";

printf("%c\n",a[4]);
printf("%c\n",*(a+4));
system("PAUSE");

return 0;
}


