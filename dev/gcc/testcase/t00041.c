/**
name: test ptr & array
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
C �����У���һά������Ϊ����������ʱ�򣬱��������ǰ���������һ��ָ������Ԫ
���׵�ַ��ָ�롣
��ô������ԭ��ġ���C �����У����з�������ʽ������ʵ�ξ��Դ�ֵ��ʽ����ʵ��
��һ�ݿ��������ݸ������õĺ��������������޸���Ϊʵ�ε�ʵ�ʱ�����ֵ����ֻ���޸�
���ݸ������Ƿݿ��������á�Ȼ�������Ҫ�����������飬�����ڿռ��ϻ�����ʱ���ϣ�
�俪�����Ƿǳ���ġ�����Ҫ���ǣ��ھ��󲿷�����£�����ʵ������Ҫ��������Ŀ�����
��ֻ����ߺ�������һ�̶��ĸ��ض����������Ȥ�������Ļ���Ϊ�˽�ʡʱ��Ϳռ䣬��
�߳������е�Ч�ʣ����Ǿ����������Ĺ���ͬ���ģ������ķ���ֵҲ������һ�����飬
��ֻ����ָ�롣����Ҫ��ȷ��һ��������ǣ�����������û�����͵ģ�ֻ�к����ķ���ֵ
�������͡��ܶ��鶼�����Ū���ˣ��������֡�XXX ���͵ĺ���������˵������ֱ�ǻ���
������
refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

void fun(char a[10]);
char b[10] ="abcdefg";
fun(b);
//fun(b[10]);
//fun(b[0]);
//fun(&b);


	
return 0;
}




void fun(char a[10])
{
int i = sizeof(a);
char c = a[3];
printf("%c\n",c);
printf("sizeof:%d\n",i);
}