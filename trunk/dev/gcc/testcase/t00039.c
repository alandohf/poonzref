/**
name: test ptr & array
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.��ָ����м�1 �������õ�������һ��Ԫ�صĵ�ַ��������ԭ�е�ֱֵַ�Ӽ�1��
2.һ������ΪT ��ָ����ƶ�����sizeof(T) Ϊ�ƶ���λ
3.�����ָ��ı����Ի�����ָ�����
4.g++���ϸ�����ͼ�飡����Ҫһ�¡�
refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

int a[5][5]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
int (*p)[4];
p = (int(*)[4] )a;
printf("a_ptr=%#p,p_ptr=%#p\n",&a[4][2],&p[4][2]);
printf("a_ptr=%d,p_ptr=%d\n",a[4][2],p[4][2]); // a[0],p[0]ά�ȳ��Ȳ�һ����������ͬ�±꣬��������Ԫ��ֵ��һ����a:4*5+2+1 vs p:4*4+2+1
printf("a_ptr=%d,p_ptr=%d\n",a[0][2],p[0][2]); 
printf("%p,%d\n",&p[4][2] - &a[4][2],&p[4][2] - &a[4][2]); //4*4+2 - (5*4+2)

	
return 0;
}


