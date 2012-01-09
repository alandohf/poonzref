/**
name:  test �ڴ�Խ��
purpose:  test heap size
dependence: 
compiler: tcc/dev-cpp
summary:
valgrind , gdb

2.����Ч�ʵıȽ�
����ջ��ϵͳ�Զ����䣬�ٶȽϿ졣������Ա���޷����Ƶġ�  
����������new������ڴ棬һ���ٶȱȽ������������ײ����ڴ���Ƭ,�������������.

3.�����С������  
����ջ����Windows��,ջ����͵�ַ��չ�����ݽṹ����һ���������ڴ��������仰����˼��ջ���ĵ�ַ��ջ�����������ϵͳԤ�ȹ涨�õģ��� WINDOWS�£�ջ�Ĵ�С��2M��Ҳ�е�˵��1M����֮��һ������ʱ��ȷ���ĳ��������������Ŀռ䳬��ջ��ʣ��ռ�ʱ������ʾoverflow����ˣ��ܴ�ջ��õĿռ��С��  
�����ѣ�������ߵ�ַ��չ�����ݽṹ���ǲ��������ڴ�������������ϵͳ�����������洢�Ŀ����ڴ��ַ�ģ���Ȼ�ǲ������ģ�������ı����������ɵ͵�ַ��ߵ�ַ���ѵĴ�С�����ڼ����ϵͳ����Ч�������ڴ档�ɴ˿ɼ����ѻ�õĿռ�Ƚ���Ҳ�Ƚϴ� 

refs: 
http://topic.csdn.net/u/20090922/10/dbf7a5b7-f426-4d89-a3e9-38d843cca94a.html
http://wenku.baidu.com/view/a943ebc589eb172ded63b76e.html
http://c.group.iteye.com/group/wiki/784-c-exception-handling-mechanism
example:
http://topic.csdn.net/u/20071229/15/54aa6ae5-0527-4809-9f56-177768e0f5b3.html 

**/

#include <stdio.h>
#include <stdlib.h>
#define I 1024
#define J 2070 // adj this value
char* heapsize();

int 
main(int argc,char *argv[]){
/**	char *p1,*p2;
	p1 = (char*)malloc(10);
	p2 = (char*)malloc(1000000000);

	//p2 = (char*)malloc(100000000000000000);
	//printf("%p\n",p1);
	//printf("%p\n",p2); // overflow
	free(p1);
	free(p2);
	
**/

char  c_a[I][J]={'a'};

int i=0 , j=0;
do{
i++;
do{
j++;
//if(c_a[I][J] != 0){
printf("%d\t%d\t%d\n",i,j,c_a[I][J]);
//;
//}
}while(j<J);
}while(i < I );

	/**
int i=0 , j=0;
for(i=0;i<I;i++) {
	for (j = 0 ; j<J;j++){
		c_a[i][j]='a';
		if(c_a[i][j]!='a'){
		printf("%d\t%d\t%c\n",i,j,c_a[i][j]);
		}

	}
	
}
**/

/**
	int i = 0;
	int n = 1;
	char*	p_init = (char*)malloc(1024*1024);
	while(1){
		i++;
		n=i*1024*1024;
		p2 = (char*)malloc(n);
		printf("%p\t%d\ti:%fMB\n",p2,n,i*1.00/1024); // overflow
		if(NULL ==p2){
			char*	p_init = (char*)malloc(1024*1024);
		free(p2);
		break;	
		}
		free(p2);

	}
	
**/


// heap memory allocate test:

/**
char *cptr_heap[10];
int i = 0;
for ( i = 0 ; i < 10 ; i++){
		cptr_heap[i]=heapsize();
		printf("the heap memory allocated above start at:%p\n",cptr_heap[i]);
}
**/
	return 0;

}


char*
heapsize(){
//char* cp_initaddr = (char*) malloc(1);
//printf("%p\n",cp_initaddr);
int n = 1024*2*2;
	while(1){
	//char* cp_prevaddr = (char*) malloc(n);
	n=n+1024*2*2; // 4KByte�Ĳ���
	//printf("%d\n",n);
	char* cp_endaddr = (char*) malloc(n);

		if (n%(1024*1024*2*2) == 0){
			printf("start at %p\tallocated:%d MByte\t end at %p\n"
			,cp_endaddr , n/1024/1024,cp_endaddr+n);
		}
		
		if(NULL == cp_endaddr){
			//printf("%p\n",cp_prevaddr);
			//printf("%d\n",cp_prevaddr - cp_initaddr);
			//printf("%d\n",n);
			printf("---------------------------------------------------------------------\n");
			return (char*) malloc(n-1024*2*2);
			//return n;
		}
		else{
			free(cp_endaddr);
		}
	}
}
