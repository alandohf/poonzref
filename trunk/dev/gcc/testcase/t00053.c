/**
name:  test free()
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.错误的free() 不会报错，但会引起内存泄漏
**/

#include <stdio.h> 
#include <stdlib.h> 

int main(int argc, char* argv[]) 
{ 
	typedef struct BSTNode {
	   int value; 
	   struct BSTNode* left;
	   struct BSTNode* right;
	} BSTNode;


	BSTNode* temp   = (BSTNode*) calloc(1, sizeof(BSTNode));
	temp->left 		= (BSTNode*) calloc(1, sizeof(BSTNode));
	free(temp->left);
	free(temp); // WRONG! don't do this!
	//free(a);

    return 0; 
} 
 