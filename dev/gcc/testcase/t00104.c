/*
*����˵�����鵱�βεı����ǣ�ֻ���������Ԫ�ص�ַ�����´�����顣ע�⿴������
*/
#include <stdio.h>
int fn(int a[]);

int main(int argc, char *argv[]) {
	
	int a[8] = {1,2,3,4,5,6,7,8};
	fn(a);
return 0;

}

int fn(int a[]){
	*(a+1) = 100;
	printf("%d\n",sizeof(a));
	return 0;
}
