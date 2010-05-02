#include <stdio.h>
int swap(int , int);
int swap_ints(int *first_number, int *second_number);

int
main()
{
  int a = 4, b = 7;

  printf("pre-swap values are: a == %d, b == %d\n", a, b);

  swap_ints(&a, &b);

  printf("post-swap values are: a == %d, b == %d\n", a, b);

  printf("pre-swap values are: a == %d, b == %d\n", a, b);

  swap(a, b);

  printf("post-swap values are: a == %d, b == %d\n", a, b);

  return 0;
}

int
swap_ints(int *first_number, int *second_number)
{
  int temp;

  /* temp = "what is pointed to by" first_number; etc... */
  temp = *first_number;
  *first_number = *second_number;
  *second_number = temp;

  return 0;
}
  
int 
swap(int first_num, int second_num)
{
  int temp;

  temp = first_num;
  first_num = second_num;
  second_num = temp;

  return 0;
}
