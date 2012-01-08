/**
name: creative test  
purpose: print a dynamic wait-sign
compiler: dev c++ , not tcc
summary:
**/

#include <stdio.h>
//#include <windows.h>
#include <unistd.h>

//using mingw on windows :¡¡use windows Sleep()
#include <windows.h>
#define sleep(n) Sleep(n)


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







