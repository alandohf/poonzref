/**
test const keyword

Const ����

1.   const���Ͷ��壺ָ������������ֵ�ǲ��ܱ�����,����Ŀ����Ϊ��ȡ��Ԥ����ָ��

2.   ���Ա��������εĶ�������ֹ������޸ģ���ǿ����Ľ�׳�ԡ�

3.   ������ͨ����Ϊ��ͨconst��������洢�ռ䣬���ǽ����Ǳ����ڷ��ű��У���ʹ������Ϊһ�������ڼ�ĳ�����û���˴洢����ڴ�Ĳ�����ʹ������Ч��Ҳ�ܸߡ�

4.    ���Խ�ʡ�ռ䣬���ⲻ��Ҫ���ڴ���䡣


ps. const  �������κܶණ�� �� �����飬ָ�룬�������������ȡ��� 1.11.5  c�������
**/

#include <stdio.h>

int main(int argc,char *argv[]){
const int a = 9;
int const b = 9;
const int c ;
a++; //t00011.c:11: warning: assignment of read-only location
b++;
c++;
printf("a=%d,b=%d c=%d\n",a,b,c);
return 0;
}


