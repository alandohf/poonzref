/**

test static
����ʱ��������Ҫ�����ε���֮��Ա�����ֵ���б��档ͨ�����뷨�Ƕ���һ��ȫ�ֱ�����ʵ�֡�������һ���������Ѿ��������ں��������ˣ����ٽ��ܺ����Ŀ��ƣ�
�������ά���������㡣
������̬�ֲ��������ÿ��Խ��������⡣��̬�ֲ�����������ȫ���������������Ǳ�����ջ�У�ÿ�ε�ֵ���ֵ���һ�ε��ã�ֱ���´θ���ֵ��
ΪʲôҪ����static
���������ڲ�����ı������ڳ���ִ�е����Ķ��崦ʱ��������Ϊ����ջ�Ϸ���ռ䣬���֪����������ջ�Ϸ���Ŀռ��ڴ˺���ִ�н���ʱ���ͷŵ���
�����Ͳ�����һ������: ����뽫�����д˱�����ֵ��������һ�ε���ʱ�����ʵ�֣� �������뵽�ķ����Ƕ���һ��ȫ�ֵı�����
������Ϊһ��ȫ�ֱ��������ȱ�㣬�����Ե�ȱ�����ƻ��˴˱����ķ��ʷ�Χ��ʹ���ڴ˺����ж���ı������������ܴ˺������ƣ���
summary:
1.�� {} �ⶨ��ģ��� ȫ��
2.��{}�ڶ���� , �� �ֲ��� {} �ڵġ�
3.�Զ���ʼ��Ϊ0
4.teststatic and teststatic2,initialize use the same memory address. and the value is not reset. ���Գ�ʼ������Ҫ����
5.��̬���ݣ���ʹ�Ǻ����ڲ��ľ� ̬�ֲ�������Ҳ�����ȫ����������
������̬ȫ�ֱ������ܱ������ļ����ã�
���������ļ��п��Զ�����ͬ���ֵı��������ᷢ����ͻ��
6. ��̬�ֲ������ڳ���ִ�е��ö����������ʱ���״γ�ʼ�������Ժ�ĺ������ò��ٽ��г�ʼ����
��ʼ��פ����ȫ����������ֱ���������н���������������Ϊ�ֲ������򣬵��������ĺ������������ʱ������������֮������
7. teststatic,teststatic2,teststatic3 �Ա�˵��������������b,c�õ���ͬһջ�ڴ棬��������޹ء�
**/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

static int a ;
int x=3;
int ftest();
int teststatic();
int teststatic2();
int teststatic3();

int main(int argc,char *argv[]){

// test if a is initialize to 0. 
printf("a=%d\n",a);
a=9;
ftest();
ftest();
int b = 999; //  ����Ӱ��ftest���b.
ftest();
ftest();

printf("a=%d\t x=%d\n",a,x);



//int b;	
//printf("a=%d b=%d\n",a,b);
	
//b only effects in ftest();
	
int i= 0;

while( i < 10 ){
//initialize();
teststatic();
teststatic2();
teststatic3();
i++;
}



return 0;

}

int ftest(){
static int b = 99;
printf("a=%d\tb=%d\n",a,b);
b++;
a++;
x++;
return 0;
}

int initialize(){
int d=0;
return 0;
}

int teststatic(){
int b;
b++;
printf("addr:%p\tvalueb:%d\n",&b,b);
return 0;
}

int teststatic2(){
int c;
c++;
printf("addr:%p\tvaluec:%d\n",&c,c);
return 0;
}

int 
teststatic3(){
int c;
c++;
printf("addr:%p\tvaluec:%d\n",&c,c);
return 0;
}
