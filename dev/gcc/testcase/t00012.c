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

void alter1(void);
void alter2(void);
void alter3(void);
int main(int argc,char *argv[]){
alter1();
alter2();
	
return 0;
}

void alter1(void){
//p:��ָ�Ķ����ֵ���ܸı䣬���Ը�����ָ�Ķ���
char *p1= "abc";
char *p2= "def";
const char *p;
p=p1;
printf("p=%s \n",p);
p=p2;
printf("p=%s \n",p);
//*p=*p1;
printf("p=%s \n",p);
//*p=*p2;
printf("p=%s \n",p);

}



void alter2(void){
//p:�����Ը�����ָ�Ķ��󣬿����޸���ָ�����ֵ��	
char *p1= "abc";
char *p2= "def";
char * const p;
//p=p1;
printf("p=%s \n",p);
//p=p2;
printf("p=%s \n",p);
*p=*p1;
*(p+1)=*(p1+1);
*(p+2)=*(p1+2);
printf("p=%s \n",p);
strcpy(p,p1);
//*p=*p2;
printf("p=%s \n",p);

}



void alter3(void){
//p:�Ȳ����Ը�����ָ�Ķ���Ҳ�������޸���ָ�����ֵ��	
char *p1= "abc";
char *p2= "def";
const char * const p;
//p=p1;
printf("p=%s \n",p);
//p=p2;
printf("p=%s \n",p);
//*p=*p1;
printf("p=%s \n",p);
//*p=*p2;
printf("p=%s \n",p);

}

