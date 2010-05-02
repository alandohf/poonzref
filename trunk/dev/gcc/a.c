#include <stdio.h>
int
main()
{
/*********start of test***********
   int n = 6;
   printf("address : %p \n" , &n);
**********end of test**************************/
///*********start of test***********

int i ;
i = 0 ;
char mystr[10]="abcdef";
do
{
printf("%s\n",mystr[i]);
i = i+1;
} while (i < 10 );
 
//**********end of test**************************/
/*********start of test***********
printf("This is a string value. Beep! Beep! \7\7\7\7\7\7");
**********end of test**************************/
}
