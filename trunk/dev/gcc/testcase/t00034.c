/**
name: test  &a+1
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
int a[5] = {1,2,3,4,5};


printf("%p\n",a);
printf("%p\n",&a[0]);
printf("%p\n",&a[1]);
printf("%p\n",&a[2]);
printf("%p\n",&a[3]);
printf("%p\n",&a[4]);
printf("%p\n",&a[5]);
printf("%p\n",&a);
printf("%p\n",&a+1);
//printf("%p\n",&a+2);
//printf("%d\n",*(&a+1));

int *ptr=(int *)(&a+1);
printf("%p\n",ptr);
printf("%d,%d",*(a+1),*(ptr-1));

system("PAUSE");

return 0;
}


