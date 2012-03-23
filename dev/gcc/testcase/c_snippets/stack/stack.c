
/*
*---------------------------------------------------------------------------
;program name  : ͨ��ջʵ��
;author		   : panzhiwei
;date		   : 2012-03-22
;function desc : ���Զ��������͵����ݽ�����ջ��ջ�Ȳ���
;compiler      : vc6 enterprise 
;notes		   :
;1.ָ��ת���ɽṹ��ָ��Ҫ��struct tag *
;2.����˳��ȷ����������->��ʼ��->����ջ
;3.
;revision log  :
;1.	v1.0 ʹ����ջ�ṹ����ʹ����base��topָ�룡
;2. v1.1 �ϳ�topָ�룬ʹ��SizeOfType+base������top��ʹ��memcpy������ָ�븳ֵ��Ȼ����Ϊ������������
;3. 
;ref		   :
;1.http://blog.csdn.net/genaman/article/details/4336483
;2.http://stackoverflow.com/questions/3848236/managing-an-array-of-indeterminate-type-with-void-pointers
;3.
*/

//http://blog.csdn.net/astropeak/article/details/6653048
//��ָ������Ҫ�Ȱ���ת��char*�ͣ��ټ�������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_INIT_SIZE 10

// ��ͨ��һ�㣺
//~ typedef struct _stack {
		//~ int		count;			// ջ��ʵ����ЧԪ�ظ���
		//~ int 	SizeOfType;
		//~ void *	base; 		// ������Ԫ������Ϊcharʱ����Ϊ char * pStack; 
		//~ void *	top; 		// ������Ԫ������Ϊcharʱ����Ϊ char * pStack; 
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


//��ʼ��ջ�ṹ�壬ʵ����Ϊջ��ָ������������̬�����ڴ沢��ʼ��ջ����������������Ǿ�̬���飬�Ͳ�����������ˡ�
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



//~ �����´��붨��Ҳ���ԣ�


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

	//~ //*(ps->top) = *data;//��ָ�벻��������ֵ,��memcpy
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
		 { "S000","NAME0"  ,"��",10,81 }
		,{ "S001","NAME1"  ,"��",11,92 }
		,{ "S002","NAME2"  ,"Ů",12,73 }
		,{ "S003","NAME3"  ,"��",10,84 }
		,{ "S004","NAME4"  ,"��",10,85 }
		,{ "S005","NAME5"  ,"��",10,86 }
		,{ "S006","NAME6"  ,"��",10,87 }
		,{ "S007","NAME7"  ,"��",10,88 }
		,{ "S008","NAME8"  ,"��",10,89 }
		,{ "S009","NAME9"  ,"��",10,76 }
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

