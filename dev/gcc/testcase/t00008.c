/**
test local variable

the two function show us that 局部变量 出作用域 则销毁

**/
#include <stdio.h>

int Add();
int Min();

int main(int argc,char *argv[]){
Add();
Min();
return 0;

}

int Add()
{
	int i=10,j=5; 
	printf("%x\n",&i);
	printf("%x\n",&j);
	return i+j;
}
int Min()
{

	int k=10,m=5;
	printf("%x\n",&k);
	printf("%x\n",&m);
	return k-m;
}

