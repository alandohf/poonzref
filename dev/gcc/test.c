#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"


int t1();
int t2(int *arr);
int t3();
int t_struct();
int t_struct2 ();
int t_ptr1 ();
int count_distinct();
int t_self_incr();
int *f_modpointer3();
int *f_modpointer4();
int t_of_fp();

////////////////////////////////////the main function/////////////////////////////////////
// use tcc a.c b.c c.c -o out.exe for multi-c-source files
int
main ( int argc, char *argv[] )
{
	
//t2.1 test 2d array 
int *p = NULL;
int (*ap)[3][4]; //数组指针	
//int  ap[x][y] 指针数组
int **pp= NULL;	
int a[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};
int i , j;
for (i = 0 ; i <3; i++)
{
	for(j = 0 ; j <4 ; j++)
	printf("%p\t%d\n",&a[i][j],a[i][j]);
}

printf("p\ta\t&a\n");	
printf("%p\t%p\t%p\n", p,a,&a);	
p=a;	// deffernt type
printf("%d\n",*p);
// turn to 
p=a[0];	// the same type
printf("%d\n",*p);
//or 
ap=&a;
printf("%d\t%d\t%d\n", ap,ap+1,ap+2);	

printf("%p\t%p\t%p\n", p,a,&a);	
p=&a;	// deffernt type
printf("%p\t%p\t%p\n", p,a,&a);	
// ==>>
p=&a[0][0]; //same type
printf("%p\t%p\t%p\n", p,a,&a);	

//p=&a[0]; // deffernt type
//printf("%p\t%p\t%p\n", p,a,&a);	
//p=&a[0][0]; //same type
//printf("%p\t%p\t%p\n", p,a,&a);	
//p=a[0];	    //same type	
//printf("%p\t%p\t%p\n", p,a,&a);	


//
printf("pp\ta\t&a\n");	
printf("%p\t%p\t%p\n", pp,a,&a);	
pp=a;	// deffernt type
printf("%p\t%p\t%p\n", pp,a,&a);
pp=a[0];	// deffernt type
printf("%p\t%p\t%p\n", pp,a,&a);

pp=&a[0]; // deffernt type
printf("%p\t%p\t%p\n", pp,a,&a);
*pp=&a[0][0]; //same type
printf("%p\t%p\t%p\n", pp,a,&a);	
*pp=a[0];	    //same type	
printf("%p\t%p\t%p\n", pp,a,&a);		
	

	
//t1.9 test array & pointer	
//char a[] = "abcdefg";
//char *p ;
//p=&a[1];
//printf("%d\t%d\n",sizeof a[1] , sizeof p);	
//printf("%p\t%p\n", &a ,  p);	
//printf("%p\t%p\n", &a[0] ,  p);	
//printf("%p\t%p\n", &a[1] ,  p);	
//printf("%c\t%c\n", a[1],p[1]+1 );
	
//t1.8 test default init .	
//static int iVar;
//static float fVar;
//static int *ip;
//printf("%d\t %p\n",iVar,&iVar)	;
//printf("%f\t %p\n",iVar,&fVar)	;
//printf("ip:\t %p\n",ip)	;
	
//t1.7 test of function pointer	
//int (*fp)() = NULL;
//int ret;	
//printf("%p\t%d\n",fp,*fp);	
//	
//fp=t_of_fp;
//printf("%p\t%d\n",fp,*fp);	
//
//	ret=(*fp)();
//
//printf("%d\n",ret);	
//printf("%d\n",(*fp)());	
//	
	
//t1.6 null pointer	
//printf("0L\n");	
//
//	int *p = 0L;
//printf("%p\n",p);	
//printf("%p\n",&p);
//if(NULL == p) printf("NULL pointer!\n");

//printf("%s\n",*p); // should be %d
	
//t1.5 test function pointer
//int (*fn_p)();
//int a;	
//printf("%s\n",typeof(a))	;  //wrong usage
	
//fn_p=f_modpointer4;
//	printf("addr of f_modpointer4:%p\n",fn_p);
	
	
//t.1.4
//void * p;
//printf("size of void : %d\n",sizeof (void *));
//printf("size of void : %d\n",sizeof (p));
//printf("value of void : %d\n",(*p));
//printf("addr of void : %p\n",(p));
//int *ip;
//p=ip;	
//printf("value of ip : %d\n",*ip);
//printf("value of p : %d\n",*p);
//printf("addr of ip : %p\n",ip);
//printf("addr of p : %p\n",p);
	
//t1.3
//char *a[]={"abc","def","ghk"};	
//	t_arg(0,a);
//test result: works!
	
//t1.2
//printf("argc:%d\t argv:%s\t%s\n",argc,argv[0],argv[1]);
	
//int *ip ;
//printf("addr of ip : %p\n",ip);	
//f_modpointer(*ip);
//printf("addr of ip : %p\n",ip);	
//f_modpointer2(&ip);
//printf("addr of ip : %p\n",ip);	
//ip= f_modpointer3();
//printf("addr of ip : %p\n",ip);		
//
//ip= f_modpointer4();
//printf("addr of ip : %p\n",ip);		
	
	
//t1.1
	
	//t1();
	//int a[10]  = { 10, 55, 9, 4, 234, 20, 30, 40, 22, 34 };
	//int a[3]  = { 40, 22, 34 };
	//printf("the smallest one :%d\n",t2(a));
	//t3();
//	t_struct();
//	t_ptr1 ();
//	count_distinct();
//int array[10] = {10,9,8,7,6,5,4,3,2,1};
//    bubbleSort( array, 10);
//    printArray( array, 10);
//t_self_incr();
/**	
	float f_a=100000000.00;
	float f_b=0.000000001;
	printf("%f\n",f_a+f_b);
	同样的也不要在很大的浮点数和很小的浮点数之间进行运算,否则：	
	精度丢失!
	**/

	
	return 0;
}				/* ----------  end of function main  ---------- */

