/*
 * =====================================================================================
 *
 *       Filename:  getc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/03/2010 09:17:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>

int main ()
{
  FILE *file;
  char c;
  int n = 0;

  file = fopen("m.txt", "r");
  
  if (file==NULL) 
      perror ("Error on reading file");
  else
  {
    do {
      c = getc (file);
      if (c == '$') 
          n++;
      } while (c != EOF);
    fclose (file);
    printf ("my.txt contains %d $.\n",n);
  }
  return 0;
}

