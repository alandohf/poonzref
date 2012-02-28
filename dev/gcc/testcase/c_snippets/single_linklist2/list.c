#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "student.h"
#include "list.h"



/***************************************************************************************
*单向链表操作
*
****************************************************************************************/

/*
*
*初始化链表
*
*/

stLinkList* initLinkList(){
	stLinkList* linklist = (stLinkList*) malloc ( sizeof(stLinkList));
	if ( NULL == linklist ){
		free(linklist);
		exit(0);
	}
	//linklist->head = NULL;
	//linklist->last = NULL;
	//linklist->length = 0;
	memset(linklist,0,sizeof(stLinkList));
	return linklist;
}

/*
*
*向链表末尾插入节点
*
*/

int insertLinkList (stLinkList * l,void * data,int dataSize) {
	NODE *n = (NODE *) malloc ( sizeof(NODE) );
	if ( NULL == l )
		return -1;
	if ( NULL == data )
		return -2;
	n->data =(void *) malloc(dataSize);
	if ( NULL == n->data ){
		free(n->data);
		return -3;
		}
	memcpy(n->data,data,dataSize);

	if ( NULL == l->head )  {
		l->head = n;
	}
	else{
		l->last->next = n;
	} 
		l->last = n;
		l->length++;
	return 0;
}


int compareBySno(void * dataOfNode,void * keyWord){
	stElemType * pstStu = NULL;
	char *pkeyWord=NULL;
	pkeyWord=(char*)keyWord;
	pstStu = (stElemType *) malloc (sizeof(stElemType));
	pstStu = (stElemType *) dataOfNode;
	return (0 == strcmp(pstStu->cStuNo,pkeyWord)) ? 1 : 0;
}

int compareBySname(void * dataOfNode,void * keyWord){
	stElemType * pstStu = NULL;
	char *pkeyWord=NULL;
	pkeyWord=(char*)keyWord;
	//pstStu = (stElemType *) malloc (sizeof(stElemType));
	pstStu = (stElemType *) dataOfNode;
	return (0 == strcmp(pstStu-> cStuName,pkeyWord)) ? 1 : 0;
}

/*
*
*在单向链表中根据关键字查找节点
*
*/

NODE * findNodeByKey(stLinkList * l,void *key ,int (*compare) ( void * dataBeingSearch,void * keyWord )){
	NODE *p = NULL;
	if ( NULL == l || NULL == key || NULL == compare )
		return NULL ;
	p=l->head;

	while(p) {
		if(compare( p->data ,key ))
			return p;
		p=p->next;
	}
	return NULL;
}

int freeStuNodeData(void * data){
	stElemType * pdata = (stElemType *)data;
	free(pdata);
	pdata=NULL;
	return 0;
}

// 释放单向链表的内存
void freeLinkList(stLinkList * l,int (*freeNodeData)(void *data)){
	NODE *tmpNode=NULL;
	NODE *pNode  =NULL;
	pNode=l->head;
	do{
	freeNodeData(pNode->data);
	pNode->data = NULL;
	tmpNode=pNode;
	pNode=pNode->next;
	free(tmpNode);
	tmpNode = NULL;
	} while(pNode);

	free(l);
	l = NULL;
}
