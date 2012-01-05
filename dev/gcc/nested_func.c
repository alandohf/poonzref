#include <stdio.h>
  int swap (int *a, int *b);
int
main()
{

  int first = 12, second = 34;

  printf("f is %d and s is %d\n", first, second);

  swap(&first, &second);

  printf("f is %d and s is %d\n", first, second);

  return 0;
}
     
  int swap (int *a, int *b)
    {
      int c;

      c = *a;
      *a = *b; //a地址上的值被改变
      *b = c;  //b地址上的值被改变

      return 0;
    }
