/**
name: test  array & pointer
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.���������ǰ����±����ʽ�Ĳ�������Ϊ��ָ�����ʽ�Ĳ���.
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


