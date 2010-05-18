/*
 * =====================================================================================
 *
 *       Filename:  c.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/16/2010 01:49:28 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
int* buffer;
buffer = (int*)malloc(sizeof(int) * 99);
if ( buffer == NULL ) //do some NULL checking before using pointer !
{
	   printf("No memory!\n") ;
}
else
{
	   /* *****
	    *    do something with the memory...
	    *       *******/
}
