#include <stdio.h>
#include <stdlib.h>
#include "list.h"


		ElemType stu[10] = {
		 { "S000","NAME0"  ,"ÄÐ",10,81 }
		,{ "S001","NAME1"  ,"ÄÐ",11,92 }
		,{ "S002","NAME2"  ,"Å®",12,73 }
		,{ "S003","NAME3"  ,"ÄÐ",10,84 }
		,{ "S004","NAME4"  ,"ÄÐ",10,85 }
		,{ "S005","NAME5"  ,"ÄÐ",10,86 }
		,{ "S006","NAME6"  ,"ÄÐ",10,87 }
		,{ "S007","NAME7"  ,"ÄÐ",10,88 }
		,{ "S008","NAME8"  ,"ÄÐ",10,89 }
		,{ "S009","NAME9"  ,"ÄÐ",10,76 }
	};

int main(){
		/**
	int i = 0;
	PSEQLIST l = NULL;
	pElemType t = NULL;
	l = ( PSEQLIST ) malloc( sizeof (SEQLIST) );
	if ( NULL == l ) return ;
	l->data = (pElemType) malloc (SEQLIST_INIT_SIZE*sizeof(ElemType));
	if ( NULL == l->data ) return ;
	l->cnt = 0;
	l->length = SEQLIST_INIT_SIZE;

	t = (pElemType) realloc (l->data,2*SEQLIST_INIT_SIZE*sizeof(ElemType));
	if ( NULL == t ) return ;
	l->data = t;
	l->cnt = 0;
	l->length = 2*SEQLIST_INIT_SIZE;
	**/


	int i = 0;
	ElemType NextStu;
	PSEQLIST l = InitSeqList();
	
	for ( i = 0 ; i < 35 ; i ++ ){
		InsertSeqList(l,&stu[i%10],i+1);
	}
//	printf("sizeof Stu : %d\t%d\n",sizeof(ElemType),sizeof(stu));

	//incrSeqList(l);
	//incrSeqList(l);
	//incrSeqList(l);

	InsertSeqList(l,&stu[1],36);
    DeleteSeqList(l,5);
	InsertSeqList(l,&stu[2],36);
	
	for ( i = 0 ; i < 35 ; i ++ ){
		AppendSeqList(l, &stu[i%10]);
	}

	SeqListGetNext( l,2, &NextStu );

	EmptySeqList(l);

	DestroySeqList(&l);
	printf("%p\n",l);

	return 0;
}

