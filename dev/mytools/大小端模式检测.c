/*
* 
*���ģʽ��Big_endian�� �������ݵĸ��ֽڴ洢�ڵ͵�ַ�У��������ݵĵ��ֽ�����
*�ڸߵ�ַ�С�
*С��ģʽ��Little_endian�� �������ݵĸ��ֽڴ洢�ڸߵ�ַ�У��������ݵĵ��ֽ�����
*�ڵ͵�ַ�С�
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
