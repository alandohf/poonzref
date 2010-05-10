/*
 * =====================================================================================
 *
 *       Filename:  ptr2ptr.c
 *
 *    Description:  test ptr to ptr 
 *
 *        Version:  1.0
 *        Created:  05/10/2010 09:20:01 AM
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	int i = 0;
	char* str = "abc";
	char** p_str= &str;
	while(*(str+i)){
		printf("str element:%c\n",*(str+i));
		i++;
	}
		printf("------------------\n");
	i = 0;
	while(p_str[0][i]){
		printf("str element:%c\n",p_str[0][i]);
		i++;
	}
		printf("------------------\n");
	i = 0;
	while( *((*p_str)+i) ){
		printf("str element:%c\n",*((*p_str)+i) );
		i++;
	
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
