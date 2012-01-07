/**
test const keyword no.2

Const ����

1.   const���Ͷ��壺ָ������������ֵ�ǲ��ܱ�����,����Ŀ����Ϊ��ȡ��Ԥ����ָ��

2.   ���Ա��������εĶ�������ֹ������޸ģ���ǿ����Ľ�׳�ԡ�

3.   ������ͨ����Ϊ��ͨconst��������洢�ռ䣬���ǽ����Ǳ����ڷ��ű��У���ʹ������Ϊһ�������ڼ�ĳ�����û���˴洢����ڴ�Ĳ�����ʹ������Ч��Ҳ�ܸߡ�

4.    ���Խ�ʡ�ռ䣬���ⲻ��Ҫ���ڴ���䡣


ps. const  �������κܶණ�� �� �����飬ָ�룬�������������ȡ��� 1.11.5  c�������
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alter1(void);
void alter2(void);
void alter3(void);
int main(int argc,char *argv[]){
	alter1();
	alter2();
	alter3();	
return 0;
}

void alter1(void){
printf("alter1: \n");

//p:��ָ�Ķ����ֵ���ܸı䣬���Ը�����ָ�Ķ���
char *p1= "abc";
char *p2= "def";
const char *p; //�������Ϊ ��ĳ������Ϊchar���ڴ� ����Ϊconst,����ڴ潫����pָ��ͨ��p��������ڴ�ʱ�����ɸı��ڴ�����ֵ�� ��location read-only
p=p1;
printf("p=%s \n",p);
p=p2;
printf("p=%s \n",p);
//*p=*p1;
printf("p=%s \n",p);
//*p=*p2; //error: assignment of read-only location
printf("p=%s \n",p);

}



void alter2(void){
printf("alter2: \n");

//p:�����Ը�����ָ�Ķ��󣬿����޸���ָ�����ֵ��	
char *p1= "abc";
char *p2= "def";
//char * const p; // error: uninitialized const `p'
char * const p = p1; // correct �������Ϊ ������һ��ָ�룬���ָ����ָ��ĵ�ַ�������λ�ã��ǲ��ɸı�ģ���Ȼ�������ֵ�Ŀ��Ըı�ġ���variable p read-only
//p=p1;
printf("p=%s \n",p);
//p=p2; //error: assignment of read-only variable `p'
printf("p=%s \n",p);
*p=*p1;
*(p+1)=*(p1+1);
*(p+2)=*(p1+2);
printf("p=%s \n",p);
//strcpy(p,p1);  // illegal usage , becasue p has not allocated memory space 
//*p=*p2;
printf("p=%s \n",p);

}



void alter3(void){
printf("alter3: \n");
	
//p:�Ȳ����Ը�����ָ�Ķ���Ҳ�������޸���ָ�����ֵ��	
char *p1= "abc";
char *p2= "def";
//const char * const p; //error: uninitialized const `p'
const char * const p=p2; // both location & variable p are read-only
//p=p1;
printf("p=%s \n",p);
//p=p2;
printf("p=%s \n",p);
//*p=*p1;
printf("p=%s \n",p);
//*p=*p2;
printf("p=%s \n",p);

}

