/**
name: test ptr & array
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.��ָ����м�1 �������õ�������һ��Ԫ�صĵ�ַ��������ԭ�е�ֱֵַ�Ӽ�1��
2.һ������ΪT ��ָ����ƶ�����sizeof(T) Ϊ�ƶ���λ

refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

int a[5][5];
int (*p)[4];
p = a;
printf("a_ptr=%#p,p_ptr=%#p\n",&a[4][2],&p[4][2]);
printf("%p,%d\n",&p[4][2] - &a[4][2],&p[4][2] - &a[4][2]); //4*4+2 - (5*4+2)

	
return 0;
}


