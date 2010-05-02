#include <stdio.h>
int get_size(void);
int get_toppings(void);

int
calculate_price()
{
  /* insert code here.  Will call get_size() and get_toppings(). */
  printf("we are calculating how much y should pay: \n");
  return get_size()*get_toppings();
}

int
get_size()
{
  /* insert code here */
  return 0;
}

int get_toppings()
{
  /* insert code here */
  return 0;
}
     
