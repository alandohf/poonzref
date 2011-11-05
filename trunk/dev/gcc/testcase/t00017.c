/**
name:test  overfow
purpose:
compiler: tcc
在函数中通过指针修改变量值
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







