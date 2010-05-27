/*
 * =====================================================================================
 *
 *       Filename:  bubbleSort.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/21/2010 08:58:50 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
// * self-defined type 
#define intArraySize 8
#define charArraySize 8
typedef  int I_TwoElementArray[intArraySize];
typedef  char C_TwoElementArray[charArraySize];

//function declaration

int 	bubbleSort(int a[], int array_size);
int     I_printArray( int array[], int array_size);
int     C_printArray( char array[], int array_size);
