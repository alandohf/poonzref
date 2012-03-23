
/*
*---------------------------------------------------------------------------
;program name  : ͨ��ջʵ��--�򻯣�ȥ��top
;author		   : panzhiwei
;date		   : 2012-03-22
;function desc : ���Զ��������͵����ݽ�����ջ��ջ�Ȳ���
;compiler      : vc6 enterprise 
;notes		   :
;1.ָ��ת���ɽṹ��ָ��Ҫ��struct tag *
;2.����˳��ȷ����������->��ʼ��->����ջ
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
//��ָ������Ҫ�Ȱ���ת��char*�ͣ��ټ�������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_INIT_SIZE 10

// ��ͨ��һ�㣺
typedef struct _stack {
		int		count;			// ջ��ʵ����ЧԪ�ظ���
		int 	SizeOfType;
		void *	base; 		// ������Ԫ������Ϊcharʱ����Ϊ char * pStack; 
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


//��ʼ��ջ�ṹ�壬ʵ����Ϊջ��ָ������������̬�����ڴ沢��ʼ��ջ����������������Ǿ�̬���飬�Ͳ�����������ˡ�
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

