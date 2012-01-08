/**
name:test  overfｌow
purpose:
compiler: tcc
*C语言对整数是不检测溢出的
**/

#include <stdio.h>
#include <math.h> 

void testptr(int *);
int main(int argc,char *argv[]){
int i=2;
int prev_val;
while( i< pow(2,31)  ){
prev_val = i;
i=(int)pow(i,2);
printf("%d\n",i);
	if( sqrt(i) != prev_val ){
		printf("variable i overflow\n");
		return -1;
	}
}
return 0;
}







