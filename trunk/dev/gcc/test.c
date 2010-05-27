#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "bubbleSort.h"
#define size 7
int t1();
int t2(int *arr);
int t3();
int t_struct();
int t_struct2 ();
int t_ptr1 ();
int count_distinct();
int t_self_incr();

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	//t1();
	//int a[10]  = { 10, 55, 9, 4, 234, 20, 30, 40, 22, 34 };
	//int a[3]  = { 40, 22, 34 };
	//printf("the smallest one :%d\n",t2(a));
	//t3();
//	t_struct();
//	t_ptr1 ();
	count_distinct();
//int array[10] = {10,9,8,7,6,5,4,3,2,1};
//    bubbleSort( array, 10);
//    printArray( array, 10);
//t_self_incr();
	return 0;
}				/* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  t_ptr1
 *  Description:  
 * =====================================================================================
 */
int	
t_ptr1 ()
{
	int p[6] = {0,1,2,3,4,5};
//	int* q = malloc(sizeof(int)*6);
        int* q = p;
//	printf("%d\n",(++*p));
	printf("%d\n",(*++q));
	printf("%d\n",(*++q));
// 	http://topic.csdn.net/t/20010824/21/255240.html
/* 我又看了看书，明白了  
 *   我一直把p当成了char   *,实际上p是char   []  
 *     两者之间还是有很大区别的  
 *       char   *可以作为lvalue，char[]就不行  
 *         p作为rvalue时可以implicit转换为char   *;  
 *           hehe */
//	printf("%d\n",(*p++));
//	printf("%d\n",(*++p));
	return 0;
}		/* -----  end of function t_ptr1  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  t_struct2
 *  Description:  
 * =====================================================================================
 */
int	
t_struct2 ()
{

    struct Flags TapeInfo;

    TapeInfo.Online  = 1;
    TapeInfo.Mounted = 0;
	return 0; 
}		/* -----  end of function t_struct2  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  t_struct
 *  Description:  
 * =====================================================================================
 */
int	
t_struct ()
{
	ST_MIN m ;
	m.m_num=0;
	return m.m_num;
//	return 0;
}		/* -----  end of function t_struct  ----- */

int t1()
{
int i ;
i = 0 ;
char mystr[]="aaabbb";
char *p_mystr = "ghijkl";
printf("%s\n",mystr);
printf("%s\n",p_mystr);
//printf(mystr);
printf("\n");
//printf(p_mystr);
printf("\n");
printf("\n");
printf("%d\n",mystr[0]);
printf("%d\n",mystr[1]);
printf("%d\n",mystr[2]);
printf("%d\n",mystr[3]);
printf("%d\n",mystr[4]);
printf("%d\n",mystr[5]);
printf("\n");

return 0;

}


int t2(int *arr)
{
 int i=0;
 int min=arr[0];

 while(arr[i] != '\0' )  {
  i++;
}

printf("%d\n",i);

for(int j=0;j<i;j++)
 {
  if(min>arr[j]){min=arr[j];}
 }
return min;
} 

//array copy
int t3()
{
  int age[4]; 
  int same_age[4];
  
  age[0]=23; 
  age[1]=34; 
  age[2]=65;
  age[3]=74;
//  same_age= age;
//  not ok
/* 
  same_age[0]=age[0];
  same_age[1]=age[1];
  same_age[2]=age[2];
  same_age[3]=age[3];

// ok 
 */
memcpy (same_age,age,sizeof age) ;
  printf("%d\n", same_age[0]);
  printf("%d\n", same_age[1]);
  printf("%d\n", same_age[2]);
  printf("%d\n", same_age[3]);
  return 0;
}

int count_distinct(){
//   int size = 7;
   int array[size] = {0,0,0,1,2,3,3};
//   int array[7] = {0,0,0,1,2,3,3};
//http://stackoverflow.com/questions/698739/why-am-i-not-getting-a-compile-error-when-declaring-a-c-array-with-variable-size
   int unique = 1; //incase we have only one element; it is unique!
   for(int i = 0; i < size -1 /* since we don't want to compare last element with junk*/; i++)
    {
     if(array[i]==array[i+1])
       continue;
     else
       unique++;
    }
  printf("The number of unique elements is %d\n",unique);
  return 0;
}
 

int t_self_incr(){
	for(int i = 0 ; i < 10 ; ++i)	
		printf("%d ",++i);
		printf("\n");
	for(int i = 0 ; i < 10 ; ++i)	
		printf("%d ",i++);
		printf("\n");
	return 0;

}
