/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/10/2010 07:58:04 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//char* strrev(char** s);
char* strrev(char* s);
char *itoa(int);
int t_printf( );
int 	
t_opr_addr ();

int 
main()
{

//t_printf( );
t_opr_addr ();
	/*  
    //long int a=0,b=0,c=0,d=0,e=0,dao=0,len=0;
//    long int z=0;
int z;	
//    printf("%d",(int) strlen("123423"));
    printf("Qing shu ru yi ge 5 wei shu:");
    scanf("%d", &z);
    printf("zhe ge shu shi: %d\n", z);
    char* buffer = itoa(z);
    printf("%d wei shu\n",(int) strlen(buffer));
    printf("zhe ge shu fan guo lai shi %s\n",strrev(buffer));
    return 0;
    if (z>=10000 && z<=99999)
    printf("%d wei shu\n",len=5);
//    len = 5;
    else if(z>=1000 && z<10000)
    printf("%d wei shu\n",len=4);
//    len = 4;
    else if(z<1000 && z>=100)
    printf("%d wei shu\n",len=3);
//    len = 3;
    else if(z<100 && z>=10)
    printf("%d wei shu\n",len=2);
//    len = 2;
    else
    printf("%d wei shu\n",len=1);
//    len = 1;
    switch(len){
     case 5:
                printf("\n%d ",z%10000);
            printf("%d ",z/1000%10);
            printf("%d ",z/100%10);
            printf("%d ",z/10%10);
            printf("%d ",z%10);break;
     case 4:
            printf("%d ",z/1000%10);
            printf("%d ",z/100%10); 
                printf("%d ",z/10%10);  
                printf("%d ",z%10);break;  
     case 3:
    printf("%d ",z/100%10);
            printf("%d ",z/10%10);       
            printf("%d ",z%10);break;
     case 2:
            printf("%d ",z/10%10);       
            printf("%d ",z%10);break;
     case 1:
            printf("%d ",z%10);break;   
            } 
     switch(len){
          
 
  case 5:           a=z%10;    
    b=z/10%10; 
    c=z/100%10;
    d=z/1000%10;
    e=z/10000;
    dao=a*10000+b*1000+c*100+d*10+e;
    printf("zhe ge shu fan guo lai shi %ld",dao);break;
  case 4:           a=z%10;    
    b=z/10%10; 
    c=z/100%10;
    d=z/1000%10;
    dao=a*10000+b*1000+c*100+d;
    printf("zhe ge shu fan guo lai shi %ld",dao);break;
  case 3:           a=z%10;    
    b=z/10%10; 
    c=z/100%10;
    dao=a*10000+b*1000+c;
    printf("zhe ge shu fan guo lai shi %ld",dao);break;
  case 2:           a=z%10;    
    b=z/10%10; 
    dao=a*10000+b;
    printf("zhe ge shu fan guo lai shi %ld",dao);break;
  case 1:           a=z%10;
    dao=a*10000;
    printf("zhe ge shu fan guo lai shi %ld",dao);break;
    }
*/
 } 
/*
 * Recursive Reverse String Algorithm
 *
 * The Shortest function to reverse a string.
 *
 * Written by: Sanchit Karve
 *             born2c0de AT hotmail.com
 *             [born2c0de]
 *             */

/*
char* strrev(char** s)
{
    int   i = 0 ;
    int   l = (int) strlen(*s);
    printf("l: %d \n",(int) l);
     for (i = 0 ; i< l ;i++){
    printf("c%d : %c\n",i,*((*s)+i));
	     *((*s)+i) = *((*s)+(l-i));
    printf("%d : %c\n",i,*((*s)+i));

     }
    printf("zhe ge shu shi: %s\n",*(s));
    return *s;
}
*/
char* strrev(char *s)
{
	  int i, j;
	  char *t = malloc(sizeof(char)*strlen(s));
	      strcpy(t,s);
    	  printf(" shi: %s\n", t);
	        for(i = 0 , j = strlen(s) - 1 ; j >= 0 ; i++, j--)
			     *(s + i) = *(t + j);
	return s;
}

#define INT_DIGITS 19		/*  enough for 64 bit integer */

char *itoa(i)
     int i;
{
  /*  Room for INT_DIGITS digits, - and '\0' */
  static char buf[INT_DIGITS + 2];
  char *p = buf + INT_DIGITS + 1;	/*  points to terminating '\0' */
  if (i >= 0) {
    do {
      *--p = '0' + (i % 10);
      i /= 10;
    } while (i != 0);
    return p;
  }
  else {			/*  i < 0 */
    do {
      *--p = '0' - (i % 10);
      i /= 10;
    } while (i != 0);
    *--p = '-';
  }
  return p;
}


/*
int t_main()
{
   ret_str("born2c0de");
   return 0;
}
 *
*/

#include	<stdlib.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
t_printf( )
{
	printf("%*.*d \n", -10, -10, 20);
	printf("%*.*d \n", 5, 5, 20);
	printf("%*.*d \n", -5, 5, 20);
	printf("%*.*d \n", 5, -5, 20);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  t_opr_addr
 *  Description:  
 * =====================================================================================
 */
int 	
t_opr_addr ( )
{
	int *pa=NULL, *pb;
	pb=&pa;
	return 0;
}		/* -----  end of function t_opr_addr  ----- */
