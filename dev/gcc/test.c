#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int t1();
int t2(int *arr);
int t3();

int 
main()
{
//t1();
//int a[10]  = { 10, 55, 9, 4, 234, 20, 30, 40, 22, 34 };
//int a[3]  = { 40, 22, 34 };
//printf("the smallest one :%d\n",t2(a));
t3();
return 0;
}


int t1(){
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

