/**
test pointer modify
在函数中通过指针修改变量值
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





