#include <stdio.h>

int get_next_square(void);

int
main()
{
  int i;

  for(i = 0; i < 10; i++){
    printf("i: %6d\n", get_next_square());
  }
  printf("and %6d\n", get_next_square());

  return 0;
}

int
get_next_square()
{
  static int count = 1;

  count += 1;

  return count * count;
}

