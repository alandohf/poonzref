#include "data.h"
#include "list.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>


PSEQLIST InitSeqList(){
	PSEQLIST l = NULL;
	l = (PSEQLIST) malloc(sizeof(SEQLIST));
	if ( NULL == l ) return NULL;
	l->data = (pElemType)malloc(SEQLIST_INIT_SIZE*sizeof(ElemType));
	if ( NULL == l->data ) 
	{
		free(l);
		return NULL;
	};
	//memset(l->data,0,SEQLIST_INIT_SIZE*sizeof(ElemType));
	l->cnt = 0;
	l->length = SEQLIST_INIT_SIZE;
	return l;
}

int incrSeqList(PSEQLIST l){
	pElemType pdata = NULL;
	pdata = (pElemType) realloc(l->data,( l->length + SEQLIST_INCR_SIZE )*sizeof(ElemType));
	if ( NULL == pdata ) {
		return -4;
	}
	l->data    = pdata;
	l->length += SEQLIST_INCR_SIZE;
	return 1;
}

int InsertSeqList(PSEQLIST l,pElemType idata,int pos){
	int i = 0,j=0;
	pElemType NewSpace = NULL;
	if ( NULL == l || NULL == idata || pos < 1 || pos > l->cnt + 1 )
		return -1;
	if ( l->cnt  >=  l->length ){
		 incrSeqList(l);
	}
//	if( pos > l->cnt + 1 ) //如果插入位置超过有效个数+1 ，则无效退出
//		exit(-3);
//	if (  0 == l->cnt )
//		l->data[0] = *idata;
//	else
//	{   
		  // 先定位到最后一个元素;i = l->cnt-1 ;  如果为cnt=0，for 中的语句将不会执行！
		i = l->cnt - 1; //i赋初值，为最后一个有效元素的索引!!int i = l->length-1;  //有误!
	    j = pos -1; // 第pos个元素在内存中的索引值为j

		for ( ; i >= j ; i-- )
		{
			l->data[ i + 1 ] = l->data[ i ];
		}

		l->data[ j ] = *idata;
//	}

	l->cnt++;

	return 1;
}

int DestroySeqList(PSEQLIST * l){
	if ( NULL == *l ) return -5;
	free((*l)->data);
	(*l)->data = NULL;
	free(*l);
	*l = NULL;
	return 1;
}

int EmptySeqList(PSEQLIST l){
	if ( NULL == l ) return -6;
	l->cnt = 0;
	memset(l->data,0,l->length*sizeof(ElemType));
	return 1;
}

int DeleteSeqList(PSEQLIST l,int pos ){
	int target = pos - 1;
	int last = l->cnt -1;
	if ( NULL == l || pos < 1 || pos > l->cnt ) return -7 ;
	for ( ;target < last  ; target++ )
	{
		l->data[target] = l->data[ target+1 ] ;
	}

	l->cnt--;
	return 1;
}



int AppendSeqList(PSEQLIST l,pElemType idata){
	
	if ( NULL == l || NULL == idata  )
		return -8;
	if ( l->cnt  >=  l->length ){
		 incrSeqList(l);
	}
	
	l->data[ l->cnt ] = *idata;

	l->cnt++;

	return 1;
}




int SeqListGetNext(PSEQLIST l,int pos,pElemType Next ){
	
	if ( NULL == l || pos < 1 || pos > l->cnt - 1 )
		return -8;

	*Next = l->data[pos];

	return 1 ;
}

