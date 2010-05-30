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
#include	<stdlib.h>

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

int     syscall(){
    char file[20];
    printf("input file name:");
    scanf("%s", file);
    char cmd[40];
    sprintf(cmd, "mkdir %s", file);
    system(cmd);
    return 0;
}


void addr_comp(){
int a[10],*p1,*p2;
p1=a;
p2=&a[5];
    printf("p1-p2:%ld\n",p1-p2);
}
/* 
 * an instance of array of pointers;
 */
int ptr_array()
{
 int a[12]={1,2,3, \
            4,5,6,\
            7,8,9,\
            10,11,12},\
      *p[4], i;
 
 for(i=0;i<4;i++)
   p[i]=&a[i*3];
   printf("%d\n",p[3][2]);
 return 0;
} 
 
