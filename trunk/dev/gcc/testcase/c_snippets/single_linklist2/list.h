#ifndef _LIST_H
#include "student.h"
#define _LIST_H
#define LIST_INIT_SIZE 10
#define LIST_INCR_SIZE 10
//顺序存储结构

//单向链表
typedef struct node_st{
	void		 *data;
	struct node_st *next;
}NODE;

typedef struct LinkList {
	NODE * head;
	NODE * last;
	int	   length;
}stLinkList;

stLinkList* initLinkList();
int insertLinkList (stLinkList * l,void * data,int dataSize);
//void freeLinkList(stLinkList * l);

int compareBySno(void * dataOfNode,void * keyWord);
int compareBySname(void * dataOfNode,void * keyWord);
NODE * findNodeByKey(stLinkList * l,void *key ,int (*compare) ( void * dataBeingSearch,void * keyWord ));
int freeStuNodeData(void ** data);
void freeLinkList(stLinkList ** l,int (*freeNodeData)(void **data));

#endif
