#ifndef _LIST_H
#include "student.h"
#define _LIST_H
#define LIST_INIT_SIZE 10
#define LIST_INCR_SIZE 10

typedef struct List {
	stElemType *Elem;
	int length;
	int size;
}LIST;

LIST* initList(int);
int insertList(LIST *,stElemType *,int);
int deleteList(LIST *l,int iPos);
void destroyList(LIST *);
stElemType *getElem( LIST *l,int i );

#endif
