/**
name:  test free()
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.�����free() ���ᱨ�����������ڴ�й©
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
 