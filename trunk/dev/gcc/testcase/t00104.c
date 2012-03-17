/*
*举例说明数组当形参的本质是：只传数组的首元素地址。不会拷贝数组。注意看汇编代码
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
