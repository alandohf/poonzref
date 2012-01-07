/**
test strcpy(p,s)
summary: 
1. need to initailize p first. or strcpy will crash the program.
**/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

int main(int argc,char *argv[]){
//char * p;strcpy(p,"def"); // illegal

//char *p= "xxx";printf("address:%p\n",p);strcpy(p,"def"); // legal but depend on compiler,not legal in gcc
char *p= (char*)malloc(100);printf("address:%p\n",p);strcpy(p,"def"); // legal
	
printf("address:%p\n",p);	
char *p2 ;
p2="aaaaaaaaaa";

char s[10]="abc";

p = s;
printf("value:%p\n",&p);
printf("value:%p %p\n",p,&s);
printf("value:%s\n",p);
//p="aaaaaaaaaa"; 改变了p的指向后（指向常量区），不能再strcpy(p,"def");
//p=p2;
printf("value:%p\t%p\n",p,p2);
printf("value:%s\t%s\n",p,p2);

printf("value:%s\t addr:%p\t%p\t%p\n",p,p,&p,&s);

strcpy(p,"def");
printf("value:%s\n",p); 

return 0;

}
