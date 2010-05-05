/*
 * =====================================================================================
 *
 *       Filename:  memset.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/04/2010 09:44:23 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	int a[10],i;
	memset(a,0,sizeof(a));
	for (i=0;i<10;i++) printf("%d\n",a[i]);
	for (i=0;i<10;i++) printf("%d\n",a[i]+1);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
