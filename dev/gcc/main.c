#include	<stdio.h>
//#include "display.h"
//#include "prices.h"
#include "./bubbleSort.h"

int
main()
{
//  display_options();
//  calculate_price();
//  display_price();
int array[10] = {10,9,8,7,6,5,4,3,2,1};
    bubbleSort( array, 10);
    printArray( array, 10);
  return 0;
}
