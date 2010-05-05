/*
 * =====================================================================================
 *
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

int main()
{ 
 FILE *fp;
 int i;
 scanf("%d",&i);
 fp=fopen("/home/pzw/fopen.txt","wb+"); 
 putw(i,fp);
 i=getw(fp);
 printf("%d",i);
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
