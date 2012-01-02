/**
"abcdefgh"
全局变量区
**/
#include <stdio.h>
int 
main()
{ 
	char str[16]="abcdefgh";
	char *ptr_str="abcdefgh";
	printf("%s\n",str);
	printf("%s\n",ptr_str);
	return 0;
}
