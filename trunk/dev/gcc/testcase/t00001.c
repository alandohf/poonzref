/**
test strrchr
����strrchr() ���������ַ���ָ���ַ����дӺ��濪ʼ�ĵ�һ�γ��ֵ�λ�ã�����ɹ����򷵻�ָ���λ�õ�ָ�룬���ʧ�ܣ��򷵻� false��

**/
#include <stdio.h> 
#include <string.h>
int main(int argc,char *argv[]){
char* str;
str=strrchr("hello, world", ',');
printf(str);
printf("\n");
return 0;
}


