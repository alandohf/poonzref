/*
* 
*大端模式（Big_endian） ：字数据的高字节存储在低地址中，而字数据的低字节则存放
*在高地址中。
*小端模式（Little_endian） ：字数据的高字节存储在高地址中，而字数据的低字节则存放
*在低地址中。
*
*/
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
	int idata = 0x1;
	char * p = (char*) &idata;
	if ( *p == 1 ){
		printf("It's Little endian on current system!\n");
	}
	else{
		printf("It's Big endian on current system!\n");		
	}
	system("pause");
return 0;

}
