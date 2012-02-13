// sizeof test
#include <stdio.h>
#include <string.h>
//~ int f();
int main()
{
	//~ int f();
//~ int i = 0;
	//~ switch ( i ) {
		//~ case 0:
		//~ {int a = 0;}
			//~ break;
		//~ case 1:
		//~ {int b = 0;}
		//~ break;
		//~ default:
			//~ break;
		
		//~ }
	//~ if( i > 1) {
				  //~ int a = 0;

		//~ } else 
		//~ {
							  //~ int b = 0;

		//~ }
		//~ return 0;
}

//~ int f(){
	//~ return 0;
	//~ }

	//~ call	__alloca
	//~ call	___main
	//~ movl	$4, -4(%ebp)
	//~ movl	$0, %eax

//~ 由于sizeof 是关键字，而非函数，所以汇编直接给出的是立即数，没有函数调用。
//~ 关键字是由编译器处理的。
