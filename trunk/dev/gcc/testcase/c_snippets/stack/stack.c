//http://blog.csdn.net/astropeak/article/details/6653048

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����һ��ջ�ṹ������ջ����Ϣ��ջ��Ԫ�ظ�����ջ����ʼ��ַ����ʵ����ṹ���������κ�һ��ջ����������ջ�͵�����ջ��
/**
typedef struct _stack {
		int ActSize;
		int * pStack; //  array pointer 's should change as it's needed
} iSTACK, * iPSTACK;
**/
// ��ͨ��һ�㣺
typedef struct _stack {
		int		count;			// ջ��ʵ����ЧԪ�ظ���
		void *	base; 		// ������Ԫ������Ϊcharʱ����Ϊ char * pStack; 
		void *	top; 		// ������Ԫ������Ϊcharʱ����Ϊ char * pStack; 
} STACK, * PSTACK;



void exitm(char a[] ){
	printf("%s\n",a);
	exit(1);
}

/**
PSTACK  InitStack(int DataSize,int StackSize)
{
	STACK * pS = NULL;
	memset(pS,0,sizeof(STACK));
	pS->base = malloc(DataSize*StackSize);
	if ( NULL == pS->base ) exitm("OutOfMemory!");
	return pS;
}
**/

//��ʼ��ջ��ʵ����Ϊջ��ָ������������̬�����ڴ棡����Ǿ�̬���飬�Ͳ�����������ˡ�
void  InitStack(PSTACK ps, int DataSize,int StackSize)
{
	ps->base  = malloc(DataSize*StackSize);
	if ( NULL == ps->base ) exitm("OutOfMemory!");
	ps->top   = ps->base;
	ps->count = 0;
}

int isEmpty(PSTACK ps)
{   
	if ( NULL == ps ) exitm("OutOfMemory!");
	return ( ps->top == ps->base) ? 1 : 0;
}

int push(PSTACK ps)
{
	return 0;
}

int main(int argc, char *argv[]) {
	// ��Ҫһ����СΪSIZE,���type�����ݵ�ջ��
	// 1. ���ͣ���СΪ10
	//~ STACK is = {0,0};
	//~ PSTACK ps = &is;
	//~ // 2. char �ͣ���СΪ10
	//~ STACK cs = {0,0};
	//~ PSTACK pcs = &cs;

// ��ʵ����Ҫ���ⶨ��һ���ض����͵Ľṹ�壬ֻҪ���ⶨ��һ���ض����͵�ָ�� type * p �Ϳ�����������ջ�ˡ�
	/**
	typedef struct _mystack {
		int		count;			// ջ��ʵ����ЧԪ�ظ���
		int	 *	base; 		// ������Ԫ������Ϊcharʱ����Ϊ char * pStack; 
		int  *	top; 		// ������Ԫ������Ϊcharʱ����Ϊ char * pStack; 
	} MYSTACK, * PMYSTACK;
	**/
	STACK is = {0,0,0};
	PSTACK ps = &is;
	int * p = NULL;
	InitStack(ps,sizeof(int),10);
	p = (int*)ps->base;
	//~ pcs->base =  (char*) InitStack(sizeof(char),10);
	return 0;
}
