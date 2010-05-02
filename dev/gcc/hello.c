#include <stdio.h>

int
main()
{
  int wages = 1000;
  int tax_allowance = 400;
  float tax_rate = 0.22;
  int tax_due;

  tax_due = (wages - tax_allowance) * tax_rate;

  printf("Tax Due: %d euro\n", tax_due);

  return 0;
}
     
