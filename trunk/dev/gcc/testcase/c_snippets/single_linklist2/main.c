#include <stdio.h>
//#include "student.h"
#include "list.h"

int
main(){
	
	int i = 0;
	NODE * resNode = NULL;
	stLinkList * ll = initLinkList ();
	stElemType stu[3] = {
		 { "S001","MING"  ,"��",11,99 }
		,{ "S002","MARY"  ,"Ů",12,78 }
		,{ "S003","BOB "  ,"��",10,86 }
	};
	

	for ( ; i < 3 ; i++)
	{
		insertLinkList(ll,&stu[i],sizeof(stu[i]));
	}
	
	//resNode=findNodeByKey(ll,"S003",compareBySno);
	resNode=findNodeByKey(ll,"MARY",compareBySname);
	

	//destroyList(list);
	//freeLinkList(ll);
	freeLinkList(&ll,freeStuNodeData);
		;
	return 0;
}

