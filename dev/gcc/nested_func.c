#include <stdio.h>

int
main()
{
  int swap (int *a, int *b)
    {
      int c;

      c = *a;
      *a = *b;
      *b = c;

      return 0;
    }

  int first = 12, second = 34;

  printf("f is %d and s is %d\n", first, second);

  swap(&first, &second);

  printf("f is %d and s is %d\n", first, second);

  return 0;
}
     
