/*
 * =====================================================================================
 *
 *       Filename:  typedef.c
 *
 *    Description: G
 *
 *        Version:  1.0
 *        Created:  05/02/2010 09:08:18 PM
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
	int
main ( int argc, char *argv[] )
{
typedef struct treenode* Tree;
struct treenode {
   int data;
   Tree smaller, larger;   // equivalently, this line could say
};                         // "struct treenode *smaller, *larger"
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
