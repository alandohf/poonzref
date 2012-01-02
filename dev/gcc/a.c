/**
1.%c
2. char [10]
3. sizeof
**/
#include <stdio.h>
int
main()
{

int i = 0;

char mystr[10]="abcdef";
	
	int n = 6;
printf("address : %p \n" , &n);
printf("%d\n",(sizeof mystr)/sizeof(char));
while (i < (sizeof mystr)/sizeof(char) )
{
printf("%c\n",mystr[i]);
i = i+1;
} ;

printf("This is a string value. Beep! Beep! \7\n");
return 0;
}
