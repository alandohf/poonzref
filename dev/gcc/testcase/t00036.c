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

char a[5]={'A','B','C','D'};
char (*p3)[3] = &a;
char (*p4)[3] = a;

char (*p5)[10] = &a;
char (*p6)[10] = a;

char (*p7)[16] = &a;
char (*p8)[16] = a;

printf("%p\n",a);
printf("%p\n",&a);

printf("%p\n",p3);
printf("%p\n",p4);

printf("%p\n",p3+1); // ��ַƫ�Ƹ�������ָ����ָ�����鳤���� 
printf("%p\n",p4+1);

printf("%p\n",p3+2);
printf("%p\n",p4+2);

printf("%p\n",p5+1);
printf("%p\n",p6+1);

printf("%p\n",p7+1);
printf("%p\n",p8+1);// ��ַƫ�Ƹ�������ָ����ָ�����鳤���� 


return 0;
}


