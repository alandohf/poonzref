#include <stdio.h>

int
main()
{
  int number_of_bicycles;
  int number_of_wheels;

  number_of_bicycles = 6;
  number_of_wheels = number_of_bicycles * 2;

  printf("I have %d bicycles\n", number_of_bicycles);
  printf("So I have %d wheels\n", number_of_wheels);

  return 0;
}
