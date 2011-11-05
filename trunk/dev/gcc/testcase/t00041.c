/**
name: test ptr & array
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
C 语言中，当一维数组作为函数参数的时候，编译器总是把它解析成一个指向其首元
素首地址的指针。
这么做是有原因的。在C 语言中，所有非数组形式的数据实参均以传值形式（对实参
做一份拷贝并传递给被调用的函数，函数不能修改作为实参的实际变量的值，而只能修改
传递给它的那份拷贝）调用。然而，如果要拷贝整个数组，无论在空间上还是在时间上，
其开销都是非常大的。更重要的是，在绝大部分情况下，你其实并不需要整个数组的拷贝，
你只想告诉函数在那一刻对哪个特定的数组感兴趣。这样的话，为了节省时间和空间，提
高程序运行的效率，于是就有了上述的规则。同样的，函数的返回值也不能是一个数组，
而只能是指针。这里要明确的一个概念就是：函数本身是没有类型的，只有函数的返回值
才有类型。很多书都把这点弄错了，甚至出现“XXX 类型的函数”这种说法。简直是荒唐
至极！
refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

void fun(char a[10]);
char b[10] ="abcdefg";
fun(b);
//fun(b[10]);
//fun(b[0]);
//fun(&b);


	
return 0;
}




void fun(char a[10])
{
int i = sizeof(a);
char c = a[3];
printf("%c\n",c);
printf("sizeof:%d\n",i);
}