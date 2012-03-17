#ifndef _STUDENT_H
#define _STUDENT_H

typedef struct Stu {
	char cStuNo[5] ;
	char cStuName[16];
	char cSex[4];
	int  iAge;
	int  iScore;
} STU,*pSTU;

#endif
