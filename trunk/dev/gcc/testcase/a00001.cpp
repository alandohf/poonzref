/**
* example: test getc �����οո����� in c 
*
**/

//~ #include <iostream>
//~ using namespace std;

//~ int 
//~ main(){
	//~ cout<<"hello world!"<<endl;
//~ return 0;	
//~ }


#include <stdio.h>

int main(int argc, char *argv[]) {
	int i = 0 ,c,retc, sum = 0;
	do{
		while( 1 ){
		c=getchar();
			if(' ' == c ||  '1' == c ) // �����ض��ַ� �� �� ' ' �� '1' ; �������⣺�����11 Ҳ��������
			{
				;
			}else{
				break;
			}
		} //end w
	//
		retc=ungetc(c,stdin);	// ��ȡһ���ַ����ж��Ƿ�Ҫ�������ٻ��ˣ���scanf��ȡ��
		sum += i;				// ��һ����0��ӣ��ȵ��ڶ���ѭ���źͶ����i��ӡ�
		if (c == '\n') break;
	} while (scanf("%d",&i) == 1);
	
	printf("%d\n",sum);
	return 0;
}
