/**
name: test ptr & array
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.��ָ����м�1 �������õ�������һ��Ԫ�صĵ�ַ��������ԭ�е�ֱֵַ�Ӽ�1��
2.һ������ΪT ��ָ����ƶ�����sizeof(T) Ϊ�ƶ���λ
3. a[0] , a[1].. �������,���Ե������������� {a[0],a[1],a[2]} �ĸ���Ԫ�ء�a[n] ��һά���顣
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

int (*p_a)[4];
p_a=&(a[0]); // ����p_a��ƫ�ƣ�p_a��ָ�������ָ�롣p_a+1 ƫ����һ������ĳ��ȣ������Ǽ򵥼�1��int�ĳ��ȡ�
printf("%p\t%p\t%p\t%d\n",p,p_a,p_a+1,*(*(p_a+1)));

int b = (0,1,100);
printf("b:%d\n",b);

return 0;
}


