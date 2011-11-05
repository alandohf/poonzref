/**
name: creative test  
purpose: print a dynamic wait-sign
compiler: dev c++ , not tcc
summary:
**/

#include <stdio.h>
//#include <windows.h>
#include <unistd.h>
void testptr(int *);
int main(int argc,char *argv[]){
	while (1){
	printf("/");putchar(8);
	sleep(100);
	printf("-");putchar(8);
	sleep(100);
	printf("\\");putchar(8);
	sleep(100);
	printf("|");putchar(8);
	sleep(100);
} 
printf("\n");	
return 0;
}







