#include <stdio.h>

int
main()
{
  int apples = 2;

printf("I have %d apple%c\n", apples, (apples == 1) ? ' ' : 's');
printf("I have %d apple%c\n", apples, (apples == 1) ? "" : 's');
printf("I have %d apple%s\n", apples, (apples == 1) ? "" : "s");

  return 0;
}
