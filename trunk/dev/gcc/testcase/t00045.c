/**
name:  test �ڴ�Խ��
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:


refs: 
**/

#include <stdio.h>
int main(int argc,char *argv[]){
int i=0;
int a[10] = {0}; // ��ʼ��Ϊ0;
for (i=0;i<=10;i++){ // �޸�i���Ͻ�������
a[i]=i;
printf("%d\n",a[i]);
}
return 0;

}
