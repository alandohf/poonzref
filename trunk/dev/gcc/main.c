#include	<stdio.h>
//#include "display.h"
//#include "prices.h"
//#include "bubbleSort.h"
#include	"myh.h"

int
main()
{

//printf("i1 = %ld\n",mypow10(10));
long res = 0 ;
int i ;	
for( i = 1; i < 10; i++){
printf("i%d = %ld\n",i,t_math_pow(1,i));
     res+=t_math_pow(1,i);
}
printf("res = %ld\n",res);
//printf("i1 = %ld\n",t_solution());
  return 0;
 
/*   ptr_array();
  return 0;
 */
/* addr_comp();
  return 0;
 */
/* int i , j , k= 9;
    i = j;
    j = 0 ;
    printf("%d,%d,%d\n",i,j,k);
  return 0;
 */
/* //05/29/2010 07:34:52 AM (EDT)  
syscall();
  return 0;
*/

/* long int i = 4294967290;
printf("i1 = %ld\n",i);
printf("i1 = %ld\n",i*2);
printf("i1 = %ld\n",i*2*2);
	i /= 2;
printf("i2 = %ld\n",i);
printf("i3 = %ld\n",sizeof(int));
printf("i3 = %ld\n",sizeof(long int));

printf("i4 = %d\n",2147483647);
printf("i4 = %ld\n",9223372036854775807);
  return 0;
 */

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

/* 
//test array type//05/27/2010 10:52:36 AM (EDT)  
    I_TwoElementArray array1={1,2,3,4,5,6,7,8};
    C_TwoElementArray array2={'a','b','c','d','e','f','g','h'};
//    array = { 0, 9 };

    I_printArray( array1, 15);
    C_printArray( array2, 15);
*/ 
}
