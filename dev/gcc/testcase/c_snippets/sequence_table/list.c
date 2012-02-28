#include <stdlib.h>
#include <stdio.h>
#include "student.h"
#include "list.h"


/*
*
*初始化链表
*n : n倍于初始化的大小
*/

LIST*
initList(int n ){

	LIST *l = NULL;

	l = ( LIST *) malloc(sizeof(LIST));
	if( l == NULL) {
		free(l);
		exit(-1);
	}

	l->Elem = (stElemType*) malloc(sizeof(stElemType)*LIST_INIT_SIZE*n);
	if( l->Elem == NULL ){
		free(l->Elem);
		exit(-2);
	}

	l->length = 0;
	l->size = LIST_INIT_SIZE*n;


	return  l ;
}

/*
*
*插入节点到链表
*iPos : 第 iPos 个元素的位置，由1开始
*/
int
insertList(LIST *l,stElemType *e,int iPos){
	stElemType *pLastElem = NULL;
	stElemType *pCurrElem = NULL;
	if ( NULL == l || NULL == e ) 
		exit(-1);
	if ( iPos < 1 )
		exit(-1);


	pLastElem = &l->Elem[ l->length -1 ];
	pCurrElem = &l->Elem[ iPos -1 ];

	for ( ; pLastElem >= pCurrElem ;  pLastElem-- ){
		  *(pLastElem+1)=*pLastElem;
	}
	*pCurrElem = *e;
	l->length=l->length + 1;
return 0;
}


int deleteList(LIST *l,int iPos){
	stElemType *pLastElem = NULL;
	stElemType *pCurrElem = NULL;
	pLastElem = &l->Elem[ l->length -1 ];
	pCurrElem = &l->Elem[ iPos -1 ];

	for ( ; pCurrElem < pLastElem ;  pCurrElem++ ){
		  *pCurrElem = *(pCurrElem+1);
	}
	//*pCurrElem = *e;
	l->length=l->length - 1;
	return 0;
}
//
//int deleteList(LIST *l,int iPos){
//	//stElemType *pNextElem = NULL;
//	int i=0;
//	stElemType *pCurrElem = NULL;
//	//pNextElem = &l->Elem[ l->length -1 ];
//	pCurrElem = &l->Elem[ iPos -1 ];
//
//	for ( i = iPos ;  i < l->length;  i++ ){
//		  *pCurrElem = *(pCurrElem+1);
//	}
//	//*pCurrElem = *e;
//	l->length=l->length - 1;
//	return 0;
//}


/*
*
*顺序表可以直接用下表来索引
*
*/

stElemType *getElem( LIST *l,int i ){
	return &l->Elem[i-1];
}


void
destroyList(LIST *l){
free(l->Elem);
free(l);
}
