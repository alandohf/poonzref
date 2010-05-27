/*
 * =====================================================================================
 *
 *       Filename:  bubbleSort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/21/2010 08:59:51 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include	<stdio.h>

int bubbleSort(int a[], int array_size)
{
     int i, j, temp;
     for (i = 0; i < (array_size - 1); ++i)
     {
          for (j = 0; j < array_size - 1 - i; ++j )
          {
               if (a[j] > a[j+1])
               {
                    temp = a[j+1];
                    a[j+1] = a[j];
                    a[j] = temp;
               }
          }
     }
	return 0;
}

int    I_printArray( int array[], int array_size){
	for (int i = 0 ; i < array_size ; i++)
		printf("%d ",array[i]);
//		printf("%c ",array[i]);
		printf("\n");
		return 0;

}
int    C_printArray( char array[], int array_size){
	for (int i = 0 ; i < array_size ; i++)
		printf("%c ",array[i]);
		printf("\n");
		return 0;

}

