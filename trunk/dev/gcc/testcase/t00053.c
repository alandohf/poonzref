// sizeof test
#include <stdio.h>
#include <string.h>

int main()
{
int i = 0;
	switch ( i ) {
		case 0:
		    printf("right");
		break;
		case 1:
		    printf("sec");
		break;
		default:
			break;
		
		}
	//~ if( i > 1) {
				    //~ printf("sec");

		//~ }
		return 0;
}


	//~ call	__alloca
	//~ call	___main
	//~ movl	$4, -4(%ebp)
	//~ movl	$0, %eax

//~ 由于sizeof 是关键字，而非函数，所以汇编直接给出的是立即数，没有函数调用。
//~ 关键字是由编译器处理的。


/**
name:  test free()
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.错误的free() 不会报错，但会引起内存泄漏
**/
/**
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
 **/
