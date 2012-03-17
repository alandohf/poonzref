#include <stdio.h>
#include "list.h"

	STU stu[3] = {
		 { "S001","MING"  ,"ÄÐ",11,99 }
		,{ "S002","MARY"  ,"Å®",12,78 }
		,{ "S003","BOB "  ,"ÄÐ",10,86 }
	};
	STU S005= { "S005","TAO"  ,"ÄÐ",12,60 };
int
main(){

	int i = 0;
	pDNODE  resNode = NULL;
	pDLIST  ll = initDLinkList ();
	insertDLinkNode(ll,1,&stu[0],sizeof(stu[0]));
	insertDLinkNode(ll,1,&stu[1],sizeof(stu[1]));
	insertDLinkNode(ll,1,&stu[2],sizeof(stu[2]));
	insertDLinkNode(ll,2,&S005,sizeof(STU));



	resNode = ll->head->next;
	for ( i = 1 ; i <= ll->length;i++){	
		printfList(resNode->data);
		resNode=resNode->next;
	}
	
		//deleteDNode(ll,4);
	swapDNode(ll,1,3);
printf("-------------after swap-------------------\n");	
	resNode = ll->head->next;
	for ( i = 1 ; i <= ll->length;i++){
		printfList(resNode->data);
		resNode=resNode->next;
	}

	emptyDList(ll);

	printf("length : %d \n",ll->length);

	 destroyDList(&ll);

	 ( NULL == ll ) ? printf("NULL\n") : printf("NOT NULL\n");

	return 0;
}


