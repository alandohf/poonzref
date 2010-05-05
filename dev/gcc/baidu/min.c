/*
 * =====================================================================================
 *
 *       Filename:  min.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/04/2010 05:54:48 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include	<stdlib.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int min(int *arr);
int min2(int *arr);

	int
main ( int argc, char *argv[] )
{
       int array[10] = {11,2,3,4,5,6,7,8,9,10};
return	min2(array);
	
}				/* ----------  end of function main  ---------- */

int min(int *arr)
{
 int max,min,len,i=0,sn;
 max=min=arr[0];
 len=sizeof(arr)/sizeof(*arr); 
for(i=0;i<len;i++)
 {
  if(min>arr[i]){min=arr[i];sn = i+1;}
 }
return min;
} 

int min2(int *arr)
{
 int max,min,len,i=0,sn;
 max=min=arr[0];

 while(arr[i] != '\0' )  {
  len++;  
  i++;
}

for(i=0;i<len;i++)
 {
  if(min>arr[i]){min=arr[i];sn = i+1;}
 }
return min;
} 
