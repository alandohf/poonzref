/**
name:test  overfow
purpose:
compiler: tcc
�ں�����ͨ��ָ���޸ı���ֵ
**/

#include <stdio.h>
void testptr(int *);
int main(int argc,char *argv[]){
int i=1;
while(i< 2^31){
i=i^2;
printf("%d\n",i);
}
return 0;
}







