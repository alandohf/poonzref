#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "student.h"
#include "list.h"


//˫������Ĳ���
//��ʼ��
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

//����ڵ�
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

	pTargetNode = pdl->head->next; //ȡ�õ�һ����Ч�Ľڵ�

	// do a  traversal on bidirect-linklist to target the iPos node
	for ( ; i < pdl->length; i++ ){
		if ( i == iPos )
			break;
		pTargetNode = pTargetNode->next;
	}


	// ��λ�ڵ�����¶���ڵ��ϵ !! ע��˳���Ȱ��½ڵ�����ٰѾɽڵ�ҵ��½ڵ��ϣ�
	pNewNode->next = pTargetNode;		//�½ڵ�ĺ���Ϊԭ�ڵ�
	pNewNode->prior = pTargetNode->prior; //�½ڵ��ǰ��Ϊԭ�ڵ��ǰ��
	pTargetNode->prior->next=pNewNode; //ԭ���ڸ�λ�õĽڵ��ǰ���ڵ㣬��������Ϊ�µĽڵ�
	pTargetNode->prior = pNewNode ; //ԭ���ڸ�λ�õĽڵ㣬��ǰ�����Ϊ�µĽڵ�
    
//	free(pTargetNode);
	pdl->length++;
	return 0;

}


// ��ӡ����

int printfList(void *data){
	 pSTU pstu = (pSTU) data;
	 printf("name:%s\n",pstu->cStuName);
	return 0;
}

int deleteDNode(pDLIST pdl,int iPos){
	int i = 1;
	pDNODE pTargetNode = NULL;	//������Ҫɾ���Ľڵ�λ��

	if ( NULL == pdl ||  iPos < 1 || iPos > pdl->length)
		exit(-1);
	pTargetNode = pdl->head->next; //ȡ�õ�һ����Ч�Ľڵ�
	for ( ; i < pdl->length; i++ ){
		if ( i == iPos )
			break;
		pTargetNode = pTargetNode->next;
	}

	//�������ýڵ��ϵ����ɾ���ڵ�
	pTargetNode->prior->next=pTargetNode->next;
	pTargetNode->next->prior=pTargetNode->prior;

	free(pTargetNode);
	pdl->length--;
	return 0;
}

int swapDNode(pDLIST pdl,int iPosA,int iPosB){
		pDNODE pTmpNODE = (pDNODE) malloc( sizeof(DNODE) );
		int i = 1;
	pDNODE pTargetNodeA = NULL,pTargetNodeB=NULL;	//������Ҫɾ���Ľڵ�λ��

	if ( NULL == pdl ||  iPosA < 1 || iPosA > pdl->length  ||  iPosB < 1 || iPosB > pdl->length)
		exit(-1);
	pTargetNodeA = pdl->head->next; //ȡ�õ�һ����Ч�Ľڵ�
	for ( ; i < pdl->length; i++ ){
		if ( i == iPosA )
			break;
		pTargetNodeA = pTargetNodeA->next;
	}

	pTargetNodeB = pdl->head->next; //ȡ�õ�һ����Ч�Ľڵ�
	for ( i=1; i < pdl->length; i++ ){
		if ( i == iPosB )
			break;
		pTargetNodeB = pTargetNodeB->next;
	}

	//swap:˳���ȴ���ǰ���ͺ��ã��ٴ���ڵ㱾����ֹ��ϵŪ��
		//pTargetNodeA->prior->next = pTargetNodeB; // x->B
		//pTargetNodeA->next->prior = pTargetNodeB;	 // B<-x
		//pTargetNodeB->prior->next = pTargetNodeA; // y->A
		//pTargetNodeB->next->prior = pTargetNodeA;	 // A<-y
		//pTargetNodeB->prior = pTargetNodeA->prior;      
		//pTargetNodeB->next  = pTargetNodeA->next;
		//pTargetNodeA->prior = pTargetNodeB->prior;
		//pTargetNodeA->next  = pTargetNodeB->next;
	//���Ͻ��������⣬����޸ģ��Ż���

	//ͨ����ʱ�н�ڵ�������
	if ( NULL == pTmpNODE ) exit(-1);
	pTmpNODE->data  = pTargetNodeB->data;
	//��pTmpNODE �滻pTargetNodeA
	pTmpNODE->next  = pTargetNodeA->next;
	pTmpNODE->prior  = pTargetNodeA->prior;
	pTargetNodeA->prior->next = pTmpNODE; 
	pTargetNodeA->next->prior = pTmpNODE;	

	//����pTargetNodeA�Ĺ�ϵ
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
//��������е㷱�����£�
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
	//������򵥵� ,��Ϊ pdl->length ÿ����һ��deleteDNode���Լ�
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
