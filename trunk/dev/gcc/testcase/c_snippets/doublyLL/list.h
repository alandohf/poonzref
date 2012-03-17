#ifndef _LIST_H
#include "student.h"
#define _LIST_H
#define LIST_INIT_SIZE 10
#define LIST_INCR_SIZE 10

//双向链表
typedef struct dnode {
	void				 *data;
	struct dnode 		 *prior;
	struct dnode		 *next;
}DNODE ,* pDNODE;

typedef struct DLinkList {
	pDNODE head;
	pDNODE last;
	int	   length;
}DLIST ,* pDLIST;


//函数声明
pDLIST initDLinkList();
int insertDLinkNode(pDLIST pdl,int iPos,void *data,int dataSize);

int printfList(void *data);

int deleteDNode(pDLIST pdl,int iPos);

int swapDNode(pDLIST pdl,int iPosA,int iPosB);

int emptyDList(pDLIST pdl);

int destroyDList(pDLIST * pdl);
#endif
