#include	<stdio.h>
#include	<stdlib.h>
#include 	"bubbleSort.h"

int
main()
{
//  display_options();
//  calculate_price();
//  display_price();
	    int array[10] = {10,9,8,7,6,5,4,3,2,1};
	    bubbleSort( array, 10);
	    printArray( array, 10);
	
system("PAUSE");
  return 0;
}
