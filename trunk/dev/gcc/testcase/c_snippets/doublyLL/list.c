#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "student.h"
#include "list.h"


//双向链表的操作
//初始化
pDLIST initDLinkList(){
	pDLIST pdl = (pDLIST) malloc(sizeof(DLIST));
		if ( NULL ==  pdl ) return NULL;
	pdl->head = (pDNODE) malloc(sizeof(DNODE));
		if ( NULL ==  pdl->head ) { free(pdl); exit(-1);}
	pdl->last = (pDNODE) malloc(sizeof(DNODE));
		if ( NULL ==  pdl->last ) { free(pdl); exit(-2);}
		memset( pdl->head,0,sizeof(DNODE) );
		memset( pdl->last,0,sizeof(DNODE) );
		pdl->head->prior = NULL;
		pdl->last->next  = NULL;
		pdl->head->next = pdl->last;
		pdl->last->prior = pdl->head;
		pdl->length=0;
		return pdl;
}

//插入节点
int insertDLinkNode(pDLIST pdl,int iPos,void *data,int dataSize){
	int i=1 ;
	pDNODE pTargetNode = NULL;
	pDNODE pNewNode = NULL;
	if (NULL == pdl || iPos < 1  || NULL == data) exit(-1);
	pNewNode = (pDNODE) malloc( sizeof(DNODE) );
	if( NULL == pNewNode ) exit(-2);
	//pNewNode->next=NULL;
	//pNewNode->prior=NULL;
	pNewNode->data=malloc(dataSize);
	if( NULL == pNewNode->data ) exit(-3);
	memcpy(pNewNode->data,data,dataSize);

	pTargetNode = pdl->head->next; //取得第一个有效的节点

	// do a  traversal on bidirect-linklist to target the iPos node
	for ( ; i < pdl->length; i++ ){
		if ( i == iPos )
			break;
		pTargetNode = pTargetNode->next;
	}


	// 定位节点后，重新定义节点关系 !! 注意顺序！先把新节点挂起，再把旧节点挂到新节点上！
	pNewNode->next = pTargetNode;		//新节点的后续为原节点
	pNewNode->prior = pTargetNode->prior; //新节点的前驱为原节点的前驱
	pTargetNode->prior->next=pNewNode; //原来在该位置的节点的前驱节点，其后续变更为新的节点
	pTargetNode->prior = pNewNode ; //原来在该位置的节点，其前驱变更为新的节点
    
//	free(pTargetNode);
	pdl->length++;
	return 0;

}


// 打印链表

int printfList(void *data){
	 pSTU pstu = (pSTU) data;
	 printf("name:%s\n",pstu->cStuName);
	return 0;
}

int deleteDNode(pDLIST pdl,int iPos){
	int i = 1;
	pDNODE pTargetNode = NULL;	//保存需要删掉的节点位置

	if ( NULL == pdl ||  iPos < 1 || iPos > pdl->length)
		exit(-1);
	pTargetNode = pdl->head->next; //取得第一个有效的节点
	for ( ; i < pdl->length; i++ ){
		if ( i == iPos )
			break;
		pTargetNode = pTargetNode->next;
	}

	//重新设置节点关系，以删除节点
	pTargetNode->prior->next=pTargetNode->next;
	pTargetNode->next->prior=pTargetNode->prior;

	free(pTargetNode);
	pdl->length--;
	return 0;
}

int swapDNode(pDLIST pdl,int iPosA,int iPosB){
		pDNODE pTmpNODE = (pDNODE) malloc( sizeof(DNODE) );
		int i = 1;
	pDNODE pTargetNodeA = NULL,pTargetNodeB=NULL;	//保存需要删掉的节点位置

	if ( NULL == pdl ||  iPosA < 1 || iPosA > pdl->length  ||  iPosB < 1 || iPosB > pdl->length)
		exit(-1);
	pTargetNodeA = pdl->head->next; //取得第一个有效的节点
	for ( ; i < pdl->length; i++ ){
		if ( i == iPosA )
			break;
		pTargetNodeA = pTargetNodeA->next;
	}

	pTargetNodeB = pdl->head->next; //取得第一个有效的节点
	for ( i=1; i < pdl->length; i++ ){
		if ( i == iPosB )
			break;
		pTargetNodeB = pTargetNodeB->next;
	}

	//swap:顺序：先处理前驱和后置，再处理节点本身，防止关系弄乱
		//pTargetNodeA->prior->next = pTargetNodeB; // x->B
		//pTargetNodeA->next->prior = pTargetNodeB;	 // B<-x
		//pTargetNodeB->prior->next = pTargetNodeA; // y->A
		//pTargetNodeB->next->prior = pTargetNodeA;	 // A<-y
		//pTargetNodeB->prior = pTargetNodeA->prior;      
		//pTargetNodeB->next  = pTargetNodeA->next;
		//pTargetNodeA->prior = pTargetNodeB->prior;
		//pTargetNodeA->next  = pTargetNodeB->next;
	//以上交换有问题，如何修改？优化？

	//通过临时中介节点来交换
	if ( NULL == pTmpNODE ) exit(-1);
	pTmpNODE->data  = pTargetNodeB->data;
	//用pTmpNODE 替换pTargetNodeA
	pTmpNODE->next  = pTargetNodeA->next;
	pTmpNODE->prior  = pTargetNodeA->prior;
	pTargetNodeA->prior->next = pTmpNODE; 
	pTargetNodeA->next->prior = pTmpNODE;	

	//重设pTargetNodeA的关系
		pTargetNodeA->prior  = pTargetNodeB->prior;
		pTargetNodeA->next   = pTargetNodeB->next;
		pTargetNodeB->prior->next = pTargetNodeA;
		pTargetNodeB->next->prior = pTargetNodeA;
	
	free(pTargetNodeB);
	return 0;
}



int emptyDList(pDLIST pdl){
/**
	//int i = 1;
	pDNODE targetNode = NULL;
	targetNode = pdl->head->next; // deleteDNode ~  i = 1;
	if( NULL == pdl ) exit(0);

	while( targetNode->next != NULL ){
		deleteDNode(pdl,1);
		targetNode = pdl->head->next;
//	i++;
//这个方法有点繁，见下：
 **/

	
	/**
	int i = pdl->length;
	do
	{
		deleteDNode(pdl,1);
	}while(--i)
	;
	**/
	//or 
	/**
	int i = pdl->length;
	while(i--){
		deleteDNode(pdl,1);
	}
	**/

	/**or**/
	//这是最简单的 ,因为 pdl->length 每做完一次deleteDNode都自减
	while(pdl->length){
		deleteDNode(pdl,1);
	}

return 0;
}


int destroyDList(pDLIST * pdl){
	if ( NULL == pdl ) exit(-1);
	emptyDList(*pdl);
	free((*pdl)->head);
	free((*pdl)->last);
	free(*pdl);
	*pdl = NULL;
	return 0;
}
