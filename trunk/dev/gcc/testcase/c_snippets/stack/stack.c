//http://blog.csdn.net/astropeak/article/details/6653048

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"
#include "poonapi.h"

pArrSTACK InitStack(int size){
	
	pArrSTACK pS = (pArrSTACK) malloc(sizeof(size*STACK_INIT_SIZE));
	if(NULL == pS) exitm("not enough memory!");
	memset(pS,0,sizeof(size*STACK_INIT_SIZE));
	pS->actSize = 0;
	return pS;
}

int isEmpty(pArrSTACK s){
	return (s->actSize == 0 ) ? TRUE : FALSE;
}

