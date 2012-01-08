/**
creative test:
**/

#include <stdio.h>
//#include <windows.h>
#include <unistd.h>

//using mingw on windows :¡¡use windows Sleep()
#include <windows.h>
#define sleep(n) Sleep(n)

int main(int argc,char *argv[]){
int i = 0;
	while (i < 100){
	printf(".");
	i++;
	sleep(100);
} 
printf("\n");	
return 0;
}







