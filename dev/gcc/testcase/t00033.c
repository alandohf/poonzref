/**
name: test  array & pointer
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.���������ǰ�*���±����ʽ�Ĳ���*����Ϊ*��ָ�����ʽ�Ĳ���*. 
Ҳ����˵�����鵱ָ�봦����
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


