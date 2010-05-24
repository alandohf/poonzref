#include	<stdio.h>
//#include "display.h"
//#include "prices.h"
//#include "bubbleSort.h"
#include	"myh.h"

int
main()
{

/*  
 * // test display();
  display_options();
  calculate_price();
  display_price();
*/

/*  
 * // test  bubbleSort
int array[10] = {10,9,8,7,6,5,4,3,2,1};
    bubbleSort( array, 10);
    printArray( array, 10);
*/
//test array type
    TwoElementArray array={1,2,3,4,5,6,7,8};
    TwoElementArray array={1,2,3,4,5,6,7,8};
//    C_TwoElementArray array={'1','2','3','4','5','6','7','8'};
//    array = { 0, 9 };

    printArray( array, 8);


  return 0;
}
