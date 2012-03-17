#ifndef _DATA_H
#define _DATA_H

typedef struct Stu {
	char cStuNo[5] ;
	char cStuName[16];
	char cSex[4];
	int  iAge;
	int  iScore;
} ElemType, * pElemType;

#endif
