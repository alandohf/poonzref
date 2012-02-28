//#include "student.h"
#include "list.h"
#include <stdio.h>


int
main(){
	
	int i = 0;
	LIST *list  = initList(1);
	stElemType *pStuA;
	stElemType stu[3] = {
		 { "S001","MING"  ,"ÄÐ",11,99 }
		,{ "S002","MARY"  ,"Å®",12,78 }
		,{ "S003","BOB "  ,"ÄÐ",10,86 }
	};
	

	//list->Elem = stu;
	//list->length = 3;

	for ( ; i < 3 ; i++)
	{
		insertList(list,&stu[i],1);
	}


	pStuA = getElem(list,2);

	//deleteList(list , 2);


	destroyList(list);

	return 0;
}
