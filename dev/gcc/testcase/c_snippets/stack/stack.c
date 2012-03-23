
/*
*---------------------------------------------------------------------------
;program name  : 通用栈实现
;author		   : panzhiwei
;date		   : 2012-03-22
;function desc : 可以对任意类型的数据进行入栈出栈等操作
;compiler      : vc6 enterprise 
;notes		   :
;1.指针转换成结构体指针要用struct tag *
;2.操作顺序：确定数据类型->初始化->出入栈
;3.
;revision log  :
;1.	v1.0 使用了栈结构体中使用了base和top指针！
;2. v1.1 废除top指针，使用SizeOfType+base来计算top！使用memcpy来给空指针赋值！然后作为输出参数输出！
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
//~ typedef struct _stack {
		//~ int		count;			// 栈中实际有效元素个数
		//~ int 	SizeOfType;
		//~ void *	base; 		// 当数组元素类型为char时，改为 char * pStack; 
		//~ void *	top; 		// 当数组元素类型为char时，改为 char * pStack; 
//~ } STACK, * PSTACK;
typedef struct mystack {
	int Count;
	int SizeOfType;
	void * data;
} MYSTACK, * PMYSTACK;

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
//~ void  InitStack(PSTACK ps, int DataSize,int StackSize)
//~ {
	//~ ps->base  = malloc(DataSize*StackSize);
	//~ if ( NULL == ps->base ) exitm("OutOfMemory!");
	//~ ps->top   = ps->base;
	//~ ps->count = 0;
//~ }

//~ int isEmpty(PSTACK ps)
//~ {   
	//~ return ( ps->top == ps->base) ? 1 : 0;
//~ }



//~ 用以下代码定义也可以！


void Init(MYSTACK * ps,int SizeOfType)
{
	if(NULL == ps ) exit(0);
	ps->data = malloc(SizeOfType*STACK_INIT_SIZE);
	if(NULL == ps->data ) exit(0);
	ps->Count = 0;
	ps->SizeOfType = SizeOfType;
}


//~ int push(PSTACK ps,void * data)
//~ {

	//~ //*(ps->top) = *data;//空指针不能这样赋值,用memcpy
	//~ memcpy(ps->top,data,ps->SizeOfType);
	//~ (int*)ps->count++;
	 //~ ps->top=(char*)ps->top+ps->SizeOfType*ps->count;
	//~ return 0;
//~ }


//~ push v1
//~ void push(MYSTACK * ps,void * data)
//~ {   
	//~ void *top;
	//~ if(NULL == ps ) exit(0);
	//~ if(ps->Count == STACK_INIT_SIZE ) exit(0);
	//~ if(ps->Count == 0)
	//~ {
		//~ memcpy(ps->data,data,ps->SizeOfType);
		//~ ps->Count++;
	//~ }
	//~ else
	//~ {
		//~ top=(void*) ( (char*)ps->data + ps->Count * ps->SizeOfType );
		//~ memcpy(top,data,ps->SizeOfType);
		//~ ps->Count++;
	//~ }
	//~ return ;
//~ }

//~ push v2
void push(MYSTACK * ps,void * data)
{   
	void *top;
	if(NULL == ps ) exit(0);
	if(ps->Count == STACK_INIT_SIZE ) exit(0);
	top=(void*) ( (char*)ps->data + (ps->Count++) * ps->SizeOfType );
	memcpy(top,data,ps->SizeOfType);
	return ;
}


void pop(MYSTACK * ps,void * data)
{   
	void *top;
	if(NULL == ps ) exit(0);
	if( 0 == ps->Count ) exit(0);
	top=(void*) ( (char*)ps->data + (--ps->Count) * ps->SizeOfType );
	memcpy(data,top,ps->SizeOfType);
	return ;
}




//~ int pop(PSTACK ps)
//~ {
	//~ if ( 1 == isEmpty(ps) ) 
	//~ {
		//~ exitm("StackIsEmpty!");
		//~ return 1;
	//~ };
	 //~ ps->top=(char*)ps->top-ps->SizeOfType*ps->count;
	//~ (int*)ps->count--;
	//~ return 0;
//~ }



int main(int argc, char *argv[]) {
	// test int type
	//~ STACK is = {0,sizeof(int),0,0};
	//~ PSTACK pis = &is;
	//~ int i = 119;
	//~ // test char type
	//~ STACK cs = {0,sizeof(char),0,0};
	//~ PSTACK pcs = &cs;
	//~ int c = 'A';

	//~ // test ElemType type
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
	//~ };
	MYSTACK stuS = {0,sizeof(ElemType),0,0};
	PMYSTACK pstuS = &stuS;
	//~ ElemType *p=NULL;
	//~ // test int type	
	//~ InitStack(pis,sizeof(int),10);
	//~ push(pis,&i);
	//~ i = 121;
	//~ push(pis,&i);
	//~ pop(pis);
	//~ pop(pis);
	//~ pop(pis);
	//~ // test char type
	//~ InitStack(pcs,sizeof(char),10);
	//~ c = 'B';
	//~ push(pcs,&c);
	//~ push(pcs,&c);
	//~ // test ElemType type
	//~ InitStack(pstuS,sizeof(ElemType),10);
	//~ push(pstuS,&stu[0]);
	//~ push(pstuS,&stu[1]);
	//~ p=pstuS->base;
	// (struct Stu *)(pstuS->base) // true!
	// (ElemType *)(pstuS->base) // wrong!
	// (pElemType )(pstuS->base) // wrong!
	
	
	MYSTACK s;
	MYSTACK * ps=&s;
	int i = 99;
	int x = 0;
	Init(ps,sizeof(int));
	push(ps,&i);
	i = 190;
	push(ps,&i);
	i = 2190;
	push(ps,&i);
	pop(ps,&x);

	Init(pstuS,sizeof(stuS));
	push(pstuS,&stu[0]);
	push(pstuS,&stu[1]);
	return 0;
}

