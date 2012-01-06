/**
gcc:
t.c:4: error: initializer element is not constant

计算机只会“取 i 的地址，把3 放到 i 的地址中，取 i 的地址，读取这个地址中的内容，取 j 的地址，把这个内容 写入j 的地址。” 它不会思考，不懂因果，只是机械地执行指令。编译器无法在编译时求得一个非常量的值，它只能在运行时通过读取变量地址来间接得到变量的值，而全局变量在编译时就必须确定其值，故C有静态存储区数据必须用常量初始化的规定。
and static变量必须使用常量初始化。
**/

#include <stdio.h>

static int si=9;
int a = 1,b=si;

int
main(){
printf("a:%d b:%d si:%d\n",a,b,si);
return 0;	
}
