/**
test pointer modify
�ں�����ͨ��ָ���޸ı���ֵ
**/

#include <stdio.h>
void testptr(int *);
int main(int argc,char *argv[]){
int i=0;
printf("%d\n",i);
testptr(&i);
printf("%d\n",i);
return 0;
}



void testptr(int *a){
*a=10;
}





