/**
name: test ++ sign
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
refs:
**/

#include <stdio.h>
#include <stdlib.h>


int main(int argc,char *argv[]){
	
	int i = 1,j = 9 ;
	int a=2,b=-2;
//”““∆
	printf("%d\n",i);
	i=i>>1;
	printf("%d\n",i);
	i=i>>10;
	printf("%d\n",i);
	i=i<<1;
	printf("%d\n",i);
	
//◊Û“∆
	printf("%d\n",j);
	j=j<<10;
	printf("%d\n",j);
	j=j>>10;
	printf("%d\n",j);
//À„ ı
	printf("%d\n",a/b);
	printf("%d\n",a%b);
	printf("%d\n",a%-b);

system("PAUSE");
return 0;
}

