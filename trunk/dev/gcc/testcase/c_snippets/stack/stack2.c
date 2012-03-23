
/*
*---------------------------------------------------------------------------
;program name  : 通用栈实现--简化，去掉top
;author		   : panzhiwei
;date		   : 2012-03-22
;function desc : 可以对任意类型的数据进行入栈出栈等操作
;compiler      : vc6 enterprise 
;notes		   :
;1.指针转换成结构体指针要用struct tag *
;2.操作顺序：确定数据类型->初始化->出入栈
;3.
;revision log  :
;1.	
;2.
;3.
;ref		   :
;1.http://blog.csdn.net/genaman/article/details/4336483
;2.http://stackoverflow.com/questions/3848236/managing-an-array-of-indeterminate-type-with-void-pointers
;3.
*/

//http://blog.csdn.net/astropeak/article/details/6653048
//空指针自增要先把它转成char*型，再加上增量
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_INIT_SIZE 10

// 更通用一点：
typedef struct _stack {
		int		count;			// 栈中实际有效元素个数
		int 	SizeOfType;
		void *	base; 		// 当数组元素类型为char时，改为 char * pStack; 
} STACK, * PSTACK;


int exitm(char a[] ){
	printf("%s\n",a);
	return 1;
}

/************************************************************************************/
typedef struct Stu {
	char cStuNo[5] ;
	char cStuName[16];
	char cSex[4];
	int  iAge;
	int  iScore;
} ElemType, * pElemType;


//初始化栈结构体，实际是为栈按指定的类型来动态分配内存并初始化栈的描述参数！如果是静态数组，就不用这个函数了。
void  InitStack(PSTACK ps, int DataSize)
{
	ps->base  = malloc(DataSize*STACK_INIT_SIZE);
	if ( NULL == ps->base ) exitm("OutOfMemory!");
	memset(ps,0,sizeof(ps));
	ps->SizeOfType = DataSize;
}

int isEmpty(PSTACK ps)
{   
	return ( ps->count == 0 ) ? 1 : 0;
}

int push(PSTACK ps,void * data)
{
	if( ps->count == STACK_INIT_SIZE ) exitm("StackOverflow!");
	memcpy((char*)ps->base+(ps->SizeOfType)*(ps->count++),data,ps->SizeOfType);
	return 0;
}


int pop(PSTACK ps,void * data)
{
	if ( 1 == isEmpty(ps) ) 
	{
		exitm("StackIsEmpty!");
		return 1;
	};
	*data = (char*)ps->base+(ps->SizeOfType)*(--ps->count);
	ps->count--;
	return 0;
}



int main(int argc, char *argv[]) {
	// test int type
	STACK is = {0,sizeof(int),0,0};
	PSTACK pis = &is;
	int i = 119;
	// test char type
	STACK cs = {0,sizeof(char),0,0};
	PSTACK pcs = &cs;
	int c = 'A';

	// test ElemType type
	ElemType stu[10] = {
		 { "S000","NAME0"  ,"男",10,81 }
		,{ "S001","NAME1"  ,"男",11,92 }
		,{ "S002","NAME2"  ,"女",12,73 }
		,{ "S003","NAME3"  ,"男",10,84 }
		,{ "S004","NAME4"  ,"男",10,85 }
		,{ "S005","NAME5"  ,"男",10,86 }
		,{ "S006","NAME6"  ,"男",10,87 }
		,{ "S007","NAME7"  ,"男",10,88 }
		,{ "S008","NAME8"  ,"男",10,89 }
		,{ "S009","NAME9"  ,"男",10,76 }
	};
	STACK stuS = {0,sizeof(ElemType),0,0};
	PSTACK pstuS = &stuS;
	ElemType *p=NULL;
	// test int type	
	InitStack(pis,sizeof(int),10);
	push(pis,&i);
	i = 121;
	push(pis,&i);
	pop(pis);
	pop(pis);
	pop(pis);
	// test char type
	InitStack(pcs,sizeof(char),10);
	c = 'B';
	push(pcs,&c);
	push(pcs,&c);
	// test ElemType type
	InitStack(pstuS,sizeof(ElemType),10);
	push(pstuS,&stu[0]);
	push(pstuS,&stu[1]);
	p=pstuS->base;
	// (struct Stu *)(pstuS->base) // true!
	// (ElemType *)(pstuS->base) // wrong!
	// (pElemType )(pstuS->base) // wrong!
	return 0;
}

