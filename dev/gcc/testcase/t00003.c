/**

test storage area adress allocation.

tcc ��֧�� strcpy??

**/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

int a = 0; //ȫ�ֳ�ʼ����
char *p1; //ȫ��δ��ʼ����


int main(int argc,char *argv[]){

int b; //ջ
char s[] = "abc"; //ջ
char *p2; //ջ
char *p3 = "123456"; //123456\\0�ڳ�������p3��ջ�ϡ�
static int c =0; //ȫ�֣���̬����ʼ����
////p1 = new char[10]; 
////p2 = new char[20]; 
////��������ĺ��ֽڵ�������ڶ�����
//strcpy(p1, "123456");
strcpy(s, "123456");
// ���� s/ p1 ��s������strcpy��д����p1�����ԡ���Ϊp1δָ�����õ��ڴ档
//123456 ���ڳ����������������ܻὫ����p3��ָ���\"123456\"�Ż���һ���ط���

printf("addr of a :%p\n",&a);
printf("addr of p1:%p\n",&p1);
printf("addr of b :%p\n",&b);
printf("addr of c :%p\n",&c);
printf("value of s :%s\n",s);
//�����ֵַ�Ĺ���	
return 0;
}
