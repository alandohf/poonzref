/**
name: test  array
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:

����a һ��
������ڴ�ƥ��Ͳ��ܱ��ı䡣a[0],a[1]��Ϊa ��Ԫ�أ�������Ԫ�ص����֡������ÿһ��
Ԫ�ض���û�����ֵġ������������ش��һ�½���sizeof �ؼ���ʱ�ļ������⣺
sizeof(a)��ֵΪsizeof(int)*5��32 λϵͳ��Ϊ20��
sizeof(a[0])��ֵΪsizeof(int)��32 λϵͳ��Ϊ4��

2.��a ��Ϊ��ֵʱ��������&a[0]��һ������������������Ԫ�ص��׵�ַ������������
���׵�ַ��

3.a ������Ϊ��ֵ��������󼸺�ÿһ��ѧ��������.���� a=p; // that is wrong

4.����ʵ������ȫ���԰�a ��һ����ͨ�ı���������ֻ������������ڲ���Ϊ�ܶ�С�飬
����ֻ��ͨ���ֱ������ЩС�����ﵽ������������a ��Ŀ�ġ�

refs: 4.2.3 c in deep
**/

#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
int a[5];
printf("size:%d\n",sizeof(a));
printf("size:%d\n",sizeof(a[0]));
printf("size:%d\n",sizeof(a[9])); 
/**���ؼ���sizeof ��ֵ���ڱ����ʱ����Ȼ��������
a[5]���Ԫ�أ���������Ҳ��û��ȥ��������a[5],���ǽ�����������Ԫ�ص�������ȷ����
ֵ����������ʹ��a[5]����������� **/

system("PAUSE");
return 0;
}

