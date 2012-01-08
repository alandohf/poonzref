/**
name: test array & pointer 
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.��ָ����м�1 �������õ�������һ��Ԫ�صĵ�ַ��������ԭ�е�ֱֵַ�Ӽ�1��
2.һ������ΪT ��ָ����ƶ�����sizeof(T) Ϊ�ƶ���λ
3. g++ will report errors , tcc & gcc will report warnings,use (char (*)[n]) to cast!
4.
(char (*)[16]) ��ָ������
(char  * [16]) ����������
refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

char a[5]={'A','B','C','D'};
char (*p3)[3] = (char (*)[3]) &a;
char (*p4)[3] = (char (*)[3]) a;

char (*p5)[10] = (char (*)[10]) &a;
char (*p6)[10] = (char (*)[10]) a;

char (*p7)[16] = (char (*)[16]) &a;
char (*p8)[16] = (char (*)[16]) a;

printf("addr_of__a:%p\n",a);
printf("addr_of_&a:%p\n",&a);

printf("addr_of_p3:%p\n",p3);
printf("addr_of_p4:%p\n",p4);

printf("addr_of_p3+1:%p\n",p3+1); // ��ַƫ�Ƹ�������ָ����ָ�����鳤���� 
printf("addr_of_p4+1:%p\n",p4+1);

printf("addr_of_p3+2:%p\n",p3+2);
printf("addr_of_p4+2:%p\n",p4+2);

printf("addr_of_p5+1:%p\n",p5+1);
printf("addr_of_p6+1:%p\n",p6+1);

printf("addr_of_p7+1:%p\n",p7+1);
printf("addr_of_p8+1:%p\n",p8+1);// ��ַƫ�Ƹ�������ָ����ָ�����鳤���� 


return 0;
}


