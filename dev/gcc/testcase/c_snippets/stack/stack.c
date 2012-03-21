//http://blog.csdn.net/astropeak/article/details/6653048

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义一个栈结构来描述栈的信息：栈的元素个数，栈的起始地址。其实这个结构可以描述任何一种栈，包括数组栈和单链表栈。
/**
typedef struct _stack {
		int ActSize;
		int * pStack; //  array pointer 's should change as it's needed
} iSTACK, * iPSTACK;
**/
// 更通用一点：
typedef struct _stack {
		int		count;			// 栈中实际有效元素个数
		void *	base; 		// 当数组元素类型为char时，改为 char * pStack; 
		void *	top; 		// 当数组元素类型为char时，改为 char * pStack; 
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

//初始化栈，实际是为栈按指定的类型来动态分配内存！如果是静态数组，就不用这个函数了。
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
	// 若要一个大小为SIZE,存放type型数据的栈：
	// 1. 整型，大小为10
	//~ STACK is = {0,0};
	//~ PSTACK ps = &is;
	//~ // 2. char 型，大小为10
	//~ STACK cs = {0,0};
	//~ PSTACK pcs = &cs;

// 其实不需要另外定义一个特定类型的结构体，只要另外定义一个特定类型的指针 type * p 就可以引用数组栈了。
	/**
	typedef struct _mystack {
		int		count;			// 栈中实际有效元素个数
		int	 *	base; 		// 当数组元素类型为char时，改为 char * pStack; 
		int  *	top; 		// 当数组元素类型为char时，改为 char * pStack; 
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
