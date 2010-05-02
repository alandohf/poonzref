#include <stdio.h>
#include <stdlib.h>
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
char mystr[]="aaabbb";
char *p_mystr = "ghijkl";
printf("%s\n",mystr);
printf("%s\n",p_mystr);
printf(mystr);
printf("\n");
printf(p_mystr);
printf("\n");
printf("\n");
printf("%d\n",mystr[0]);
printf("%d\n",mystr[1]);
printf("%d\n",mystr[2]);
printf("%d\n",mystr[3]);
printf("%d\n",mystr[4]);
printf("%d\n",mystr[5]);
printf("\n");
/**do
{
printf("%s\n",mystr[i]);
i = i+1;
} while (i < 3 );
**/
//**********end of test**************************/
/*********start of test***********
printf("This is a string value. Beep! Beep! \7\7\7\7\7\7");
**********end of test**************************/
}
