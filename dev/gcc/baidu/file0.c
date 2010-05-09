/* * ===================================================================================== *
 *       Filename:  file1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/03/2010 10:55:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
int putw(int i,FILE *fp);
int getw(FILE *fp);
int filecp();

int main()
{ 
 int i;
 FILE *fp;
 fp=fopen("/tmp/fopen.txt","at"); 
// rewind(fp);
//  scanf("%d",&i);
//  putc(i,fp);
 while ( scanf("%d",&i)  == 1)
{ 
// rewind(fp);
 putc(i,fp);
}
 fclose(fp);
// filecp(); 
 return 0;
}

int  putw(int i,FILE *fp)
{ 
 char *s;
 s=(char*)&i;
 putc(s[0],fp);
 putc(s[1],fp);
 return i;
}

int getw(FILE *fp)
{ 
 char *s;
 int i;
 s=(char*)&i;
 s[0]=getc(fp);
 s[1]=getc(fp);
 return i;
} 
int filecp(){
     int ch;
     FILE *input, *output;
     input = fopen( "/tmp/tmp.c", "r" );
     output = fopen( "/tmp/tmpCopy.c", "w" );
     ch = getc( input );
     while( ch != EOF ) {
       putc( ch, output );
       ch = getc( input );
     }
     fclose( input );
     fclose( output );
     return 0;
}

