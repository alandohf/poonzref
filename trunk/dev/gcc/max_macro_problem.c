#include <stdio.h>
#define MAX(a, b) (a > b ? a : b)

int
main()
{
  int cows = 10, sheep = 12;

  printf("We have %d of our most common animal\n", MAX(cows, sheep));

  printf("Hang on, we just bought another one.\n");
  printf("Now we have %d.\n", MAX(cows, ++sheep));

  return 0;
}
