/**
name: test ptr & array
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.��ָ����м�1 �������õ�������һ��Ԫ�صĵ�ַ��������ԭ�е�ֱֵַ�Ӽ�1��
2.һ������ΪT ��ָ����ƶ�����sizeof(T) Ϊ�ƶ���λ
3. a[0] , a[1].. �������
refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

int a[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};

int *p;
p=a[1];
printf("%d\n",*(p-1));
printf("%d\n",*p);
printf("%d\n",*(p+1));
printf("%d\n",*(p+2));
printf("%d\n",*(p+3));
printf("%d\n",p[0]);

int b = (0,1,100);
printf("b:%d\n",b);

return 0;
}


