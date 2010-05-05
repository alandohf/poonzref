/*
 * =====================================================================================
 *
 *       Filename:  putc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/03/2010 11:07:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
    #include <stdio.h>
     
    int main()
    {
      int ch;
      FILE *input;


      input = fopen("stuff", "rt");
        ch = getc(input);
        while (ch != EOF)
        {
          putc(ch, stdout);
          ch = getc(input);
        }
        fclose(input);
      return 0;
    }
