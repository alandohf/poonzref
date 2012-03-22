
/*
************************************************************************************
;program name  : 栈实现_针对整型
;author		   : panzhiwei
;date		   : 2012-03-22
;function desc : 可以对整类型的数据进行入栈出栈等操作
;compiler      : vc6 enterprise 
;notes		   :
;1.
;2.
;3.
;revision log  :
;1.	
;2.
;3.
;ref		   :
;1.
;2.
;3.
*************************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_INIT_SIZE 10

/************************************************************************************
*struct 结构体定义
*************************************************************************************/

// 更通用一点：
typedef struct _stack {
		int		count;
		int 	a[STACK_INIT_SIZE-1]
	} STACK, * PSTACK;



/************************************************************************************
*struct 自定义函数
*************************************************************************************/

int exitm(char a[] ){
	printf("%s\n",a);
	return 1;
}



int isEmpty(PSTACK ps)
{   
	return ( 0 == PSTACK->count ) ? 1 : 0;
}

int push(PSTACK ps,int * data)
{
	if ( ps->count == STACK_INIT_SIZE ) exitm("StackOverflow!");
	ps->a[ps->count+1] = *data;
	ps->count++;
	return 0;
}


int pop(PSTACK ps,int * data)
{
	if ( 1 == isEmpty(ps) )
	{
		exitm("StackIsEmpty!");
		return 1;
	};
	*data=ps->a[ps->count-1]
	ps->count--;
	return 0;
}



/************************************************************************************
*程序入口
*************************************************************************************/

int main(int argc, char *argv[]) {
	int a = 3, b = 2, c = 9;
	int out = 0;
	STACK s;
	PSTACK ps=&s;
	memset(ps,0,sizeof(s)); // 当然，这步可以用函数封装！
	push(ps,&a);
	push(ps,&b);
	push(ps,&c);
	push(ps,&out);
	push(ps,&out);
	return 0;
}
