/*
* 举例说明空指针的使用和定义。根据汇编可知，空指针是语法规则，在汇编层面，空指针仅仅是一块值为0的内存。

*/
#include <stdio.h>
int fn(int a[]);

int main(int argc, char *argv[]) {
		int * p ;
		int * q ;
		 p = (int *) 0;
		 q = NULL;
		printf("%p %p\n",p,q);
	
return 0;

}
