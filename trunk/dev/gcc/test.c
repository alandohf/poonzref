#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
//#include <unistd.h>

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
//t7.4 
//	char linebuf[80];
//	char *lines[100];
//	int i;
////printf("start..\n");
//	FILE *fp;
//	if((fp= fopen("file.dat", "r"))==NULL){
//		fprintf(stderr, " %s\n", strerror(errno));
//		exit(1);
//	}	
////printf("trace..\n");
//	for(i = 0; i < 100; i++) {
//		char *p = fgets(linebuf, 40, fp);
//		if(p == NULL) break;
//printf("trace..\n");		
//		lines[i] = p;
//		printf("%s\n",&lines);
//	}
//	fclose(fp);
//
// t2.7 strcpy()
// char *p ; // crash 	
//char *p="1"; // not crash
//char p[1];	// crash
//char p[10];	// not crash
//char a[100];p=a;	
//strcpy(p, "abc");
//printf("%s\n",p);	// if no (char a[100];p=a;	) , the program crash!
// t2.6 test strcat()
//char a[100]="abcd";
//char b[10]="1234";
/**	
char *a = "abcdefg";
char *b = "1234";	
printf("%d\n",sizeof a );
printf("%d\n",sizeof b );
//printf("%s\t%d\n",strcat(a,b),sizeof (strcat(a,b)));
	char *a = "Hello, ";
	char *b = "world!";	
char *c=strcat(a,b);
printf("%s\t%d\n",c,sizeof c);
printf("%s\t\n",a);
**/	
//This function has undefined results if the strings overlap.
	
// t2.5 test gets()
/**	
char answer[10]	;
gets(answer);
printf("\nyou type:%s\n",answer);	
// gets will get crash if input greater than (sizeof answer)
**/
	
//t.2.4 test fgets()
//char answer[100], *p;
//printf("Type something:\n");
//fgets(answer, sizeof answer, stdin);
//if((p = strchr(answer, '\n')) != NULL)
//	*p = '\0';
//printf("You typed \"%s\"\n", answer);
/**
char answer[10],*p;
fgets(answer,sizeof answer,stdin);	
printf("\n");
if( (p=strchr(answer,'\n')) != NULL ){
	*p='\0';
}	
printf("%s\n",answer); //  *answer is not correct!
printf("%d\n",*answer); 
**/	
// fgets will get only (sizeof answer) when stdin is greater than (sizeof answer)

//t2.3 test array bound 

//int a[4]={1,2,3,4};
//f_t_a(a);

//t2.2
	
// printf("%d\n",sizeof(int ***));	
	
 //t2.1 test 2d array 
 int *p = NULL;  // a pointer to int 
 //int (*ap1)[3]; // an 1-d int-array   pointer 
 int (*ap)[3][4]; //数组指针	// 加（） ，使得指针优先 , [][] 修饰 *ap
 int **pp= NULL; // a int pointer to a int pointer	
 int a[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};
 int i , j;
 // addr where store values
 for (i = 0 ; i <3; i++)
 {
 	for(j = 0 ; j <4 ; j++)
 	printf("%p\t%d\n",&a[i][j],a[i][j]);
 }
 
 printf("p\ta\t&a\n");	
 printf("%p\t%p\t%p\n", p,a,&a);
 // p : a pointer to int
 //*p: an int
 //ap1 :  a pointer to a 1-d-int-array
 
 // a: a pointer to a[0] , a[0] is an array.
 // a[0] : a reference  to first element of array: a[0][y]. i.e a[0][0] . differ it from &a[0]
 // a[0][0] : an int
 
 // &a : a reference to a 2-d array
//&a[0]: a reference of 
printf("addr of &a[0]:%p\n",(&a[0]));

//&a[0][0] a reference of   an int : a[0][0]
 
 
//ap1=&a[0]; // same type ; a pointer to a 1-d-int-array
 p=a;	// deffernt type  ; p is a int pointer; a is a pointer to a[0]
 printf("%d\n",*p);
 // turn to 
 p=a[0];	// the same type
 //p=a[0][0]; // different type ; p is a int pointer , a[0][0] is an int. & will make the program crash
 p=&a[0][0]; ; // 
 *p=a[0][0]; // same type ; *p is a int , a[0][0] is an int.
 
 //printf("addr of a[0]:%p\n",(a[0]));
 //printf("valueof a[0]:%d\n",*(a[0]));
 
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

