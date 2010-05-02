#include <stdio.h>

int
main()
{
  int apples = 1;

  printf("I have %d apple%s\n", apples, (apples == 1) ? "" : "s");

  return 0;
}
