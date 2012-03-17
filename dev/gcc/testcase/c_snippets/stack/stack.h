#ifndef _STACK_H
#define _STACK_H

#define STACK_SIZE 10
typedef struct Node {
	void * data;
} NODE,PNODE;


typedef struct Stack{
	NODE * base;
	NODE * top;	
	
}STACK,PSTACK;


#endif
