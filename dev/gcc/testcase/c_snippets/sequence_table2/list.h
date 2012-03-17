#ifndef _LIST_H
#include "data.h"
#define _LIST_H

/*******************************************************************
*sequence list
*顺序表的定义
*******************************************************************/

#define SEQLIST_INIT_SIZE 10 //顺序表的初始大小
#define SEQLIST_INCR_SIZE 10 //顺序表每次扩展的大小
/**SeqList用来描述顺序表的信息**/
typedef struct SeqList{
	pElemType data; //数据元素首地址
	int		  cnt;  //有效元素个数
	int		  length; //已经分配的存储单元数
} SEQLIST,* PSEQLIST;

PSEQLIST InitSeqList();

int InsertSeqList(PSEQLIST l,pElemType data,int pos);
int incrSeqList(PSEQLIST l);
int DestroySeqList(PSEQLIST * l);
int EmptySeqList(PSEQLIST l);
int DeleteSeqList(PSEQLIST l,int pos );
int AppendSeqList(PSEQLIST l,pElemType idata);
int SeqListGetNext(PSEQLIST l,int pos,pElemType Next );

#endif
