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

//~ ����sizeof �ǹؼ��֣����Ǻ��������Ի��ֱ�Ӹ���������������û�к������á�
//~ �ؼ������ɱ���������ġ�


/**
name:  test free()
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.�����free() ���ᱨ�����������ڴ�й©
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
