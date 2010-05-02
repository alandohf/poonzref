#include <stdio.h>
int
main()
{
  int person[10];
  float hourly_wage[5] = {2, 4.9, 10, 123.456,111.11};
  int index;

  index = 4;
  person[index] = 56;

  printf("the %dth person is number %d and earns $%f an hour\n",
         (index + 1), person[index], hourly_wage[index]);

  return 0;
}
  
