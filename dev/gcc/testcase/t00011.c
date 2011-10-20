/**
test const keyword

Const 作用

1.   const类型定义：指明变量或对象的值是不能被更新,引入目的是为了取代预编译指令

2.   可以保护被修饰的东西，防止意外的修改，增强程序的健壮性。

3.   编译器通常不为普通const常量分配存储空间，而是将它们保存在符号表中，这使得它成为一个编译期间的常量，没有了存储与读内存的操作，使得它的效率也很高。

4.    可以节省空间，避免不必要的内存分配。


ps. const  可以修饰很多东西 ， 如数组，指针，函数，参数，等。见 1.11.5  c深度剖析
**/

#include <stdio.h>

int main(int argc,char *argv[]){
const int a = 9;
int const b = 9;
const int c ;
a++; //t00011.c:11: warning: assignment of read-only location
b++;
c++;
printf("a=%d,b=%d c=%d\n",a,b,c);
return 0;
}


