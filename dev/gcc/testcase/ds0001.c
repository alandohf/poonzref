/**
ds:data structure : 

**/

#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
char *p = NULL;
int a[100];
//	sizeof (int) *p; // not work !
	sizeof ((int) *p);
printf("%d\n",sizeof ((int*) p));
printf("%d\n",sizeof ((int) *p));

/////////	
printf("%d\n",sizeof(p));
printf("%d\n",sizeof(*p)); // eq  : sizeof (int)
printf("%d\n",sizeof(a));  // the whole array
printf("%d\n",sizeof(a[100])); // eq: sizeof(int)
printf("%d\n",sizeof(&a)); // eq: sizeof(ptr)
printf("%d\n",sizeof(&a[0])); // eq: sizeof(ptr)
	return 0;
}
