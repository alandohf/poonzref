/**
name: test ptr & array
purpose: ������Ϊ��������
dependence: 
compiler: tcc/dev-cpp
summary:
1.��ָ����м�1 �������õ�������һ��Ԫ�صĵ�ַ��������ԭ�е�ֱֵַ�Ӽ�1��
2.һ������ΪT ��ָ����ƶ�����sizeof(T) Ϊ�ƶ���λ

refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

void fun(char a[10]);
char b[10] ="abcdefg";
fun(b);
//fun(b[10]);
//fun(b[0]);
//fun(&b);


	
return 0;
}




void fun(char a[10])
{
char c = a[3];
printf("%c\n",c);
}