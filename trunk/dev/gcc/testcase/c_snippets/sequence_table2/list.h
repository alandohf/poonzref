#ifndef _LIST_H
#include "data.h"
#define _LIST_H

/*******************************************************************
*sequence list
*˳���Ķ���
*******************************************************************/

#define SEQLIST_INIT_SIZE 10 //˳���ĳ�ʼ��С
#define SEQLIST_INCR_SIZE 10 //˳���ÿ����չ�Ĵ�С
/**SeqList��������˳������Ϣ**/
typedef struct SeqList{
	pElemType data; //����Ԫ���׵�ַ
	int		  cnt;  //��ЧԪ�ظ���
	int		  length; //�Ѿ�����Ĵ洢��Ԫ��
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
