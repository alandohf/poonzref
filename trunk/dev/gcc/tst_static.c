/*
author: panzhiwei
purpose : test static keyword .
effects: if static var in an  local func fun1 , then the var work like an global var , the value can be change by fun1.
static ���������ã�
1.�ñ���������������ڴӸ��ļ�����֮�����ļ�����Ϊֹ��
2.�ú���������������ڴӸ��ļ�
3.�þֲ������ں����˳��󲻱����٣��´ε��û��ܼ���ʹ�á�
*/
#include <stdio.h>
//static int j;
 int j = 0;

int fun1();
int fun2();
int fun3();


int main(){
	int k;
	printf("start\n");	
	for ( k=0;k<10;k++ ){
		fun1();
		fun2();
		fun3();
	//printf("%d\n",i+1000);  i ���ɼ�
	}
//	printf("end\n");	
  return 0;
}

int fun1(){
	static int i = 0;
//	 int i = 0;
	i++;
	printf("fun1:%d\n",i);
	return 0;
	}
	
int fun2(){
	j++;
	printf("fun2:%i\n",j);
	return 0;
	}

	
int fun3(){
	k=k+100; // k ������main �Ҷ�fun3���ɼ�,fun3���ܷ���K
	printf("fun3:%d\n",k);
	return 0;
	}