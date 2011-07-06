#include <stdio.h>
int
main()
{
  int *pa = NULL;
  char *pb = NULL;
  char a[200];
  printf("sizeof(char) == %d\n", sizeof(char));
  printf("sizeof(short) == %d\n", sizeof(short));
  printf("sizeof(int) == %d\n", sizeof(int));
  printf("sizeof(long) == %d\n", sizeof(long));
  printf("sizeof(long long) == %d\n", sizeof(long long));
//	
  printf("sizeof(int*) == %d\n", sizeof(int*));
//	
  printf("sizeof(pa) == %d\n", sizeof(pa));
  printf("sizeof(&pa) == %d\n", sizeof(&pa));
printf("%d\n",&pa);	
  printf("sizeof(*pa) == %d\n", sizeof(*pa));
//	
  printf("sizeof(pb) == %d\n", sizeof(pb));
  printf("sizeof(*pb) == %d\n", sizeof(*pb));
//
  printf("sizeof(a) == %d\n", sizeof(a));
  printf("sizeof(&a) == %d\n", sizeof(&a));
  printf("sizeof(&a[0]) == %d\n", sizeof(&a[0]));

  return 0;
}
