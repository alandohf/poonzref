/*
 * =====================================================================================
 *
 *       Filename:  sqlpluss.c
 *
 *    Description:  for security , using c system() to wrap sqlplus user/password
 *
 *        Version:  1.0
 *        Created:  06/19/2010 11:24:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include	<stdlib.h>

#include	<stdlib.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	int ret;
	ret = system("sqlplus pzw/oracle");
	return ret;
}				/* ----------  end of function main  ---------- */
