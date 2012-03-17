/*
* 
* ascii 码对照表
*
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int i ;
	printf("%-10s%-10s%-10s","10进制","16进制","ASCII码");
	printf("%-10s%-10s%-10s\n","10进制","16进制","ASCII码");
for (i = 0 ; i < 64; i++){
	if (i == '\n'|| i == '\r' || i== 7 || i == 8 || i == 9){
		printf("%-10d%-10x%-10c",i,i,'-');
		printf("%-10d%-10x%-10c\n",i+64,i+64,i+64);		
	}else{
		printf("%-10d%-10x%-10c",i,i,i);
		printf("%-10d%-10x%-10c\n",i+64,i+64,i+64);				
	}

}
	printf("\n注：10进制的7,8,9,10,13 的ascii字符经过处理，置为'-',以便输出能对齐！\n");
	system("pause");
return 0;

}
