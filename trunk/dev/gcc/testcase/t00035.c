/**
name: test array & pointer 
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

	int i=0;
	int *a[10]; //ָ������  [] �����ȼ���*�ߣ����� * ���� [];
	int (*p)[10]; // ����ָ��--ָ�������ָ�� ; ( ) �����ȼ��ߣ����� [] ���� (*p)
	a[0] = &i;

	int b[10];
	p=&b; // not b 
return 0;
}


