/*
* 
* ascii ����ձ�
*
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int i ;
	printf("%-10s%-10s%-10s","10����","16����","ASCII��");
	printf("%-10s%-10s%-10s\n","10����","16����","ASCII��");
for (i = 0 ; i < 64; i++){
	if (i == '\n'|| i == '\r' || i== 7 || i == 8 || i == 9){
		printf("%-10d%-10x%-10c",i,i,'-');
		printf("%-10d%-10x%-10c\n",i+64,i+64,i+64);		
	}else{
		printf("%-10d%-10x%-10c",i,i,i);
		printf("%-10d%-10x%-10c\n",i+64,i+64,i+64);				
	}

}
	printf("\nע��10���Ƶ�7,8,9,10,13 ��ascii�ַ�����������Ϊ'-',�Ա�����ܶ��룡\n");
	system("pause");
return 0;

}
