/**

test static
但有时候我们需要在两次调用之间对变量的值进行保存。通常的想法是定义一个全局变量来实现。但这样一来，变量已经不再属于函数本身了，不再仅受函数的控制，
给程序的维护带来不便。
　　静态局部变量正好可以解决这个问题。静态局部变量保存在全局数据区，而不是保存在栈中，每次的值保持到下一次调用，直到下次赋新值。
为什么要引入static
　　函数内部定义的变量，在程序执行到它的定义处时，编译器为它在栈上分配空间，大家知道，函数在栈上分配的空间在此函数执行结束时会释放掉，
这样就产生了一个问题: 如果想将函数中此变量的值保存至下一次调用时，如何实现？ 最容易想到的方法是定义一个全局的变量，
但定义为一个全局变量有许多缺点，最明显的缺点是破坏了此变量的访问范围（使得在此函数中定义的变量，不仅仅受此函数控制）。
summary:
1.在 {} 外定义的，是 全局
2.在{}内定义的 , 是 局部于 {} 内的。
3.自动初始化为0
4.teststatic and teststatic2,initialize use the same memory address. and the value is not reset. 所以初始化很重要！！
5.静态数据（即使是函数内部的静 态局部变量）也存放在全局数据区。
　　静态全局变量不能被其它文件所用；
　　其它文件中可以定义相同名字的变量，不会发生冲突；
6. 静态局部变量在程序执行到该对象的声明处时被首次初始化，即以后的函数调用不再进行初始化；
它始终驻留在全局数据区，直到程序运行结束。但其作用域为局部作用域，当定义它的函数或语句块结束时，其作用域随之结束；
7. teststatic,teststatic2,teststatic3 对比说明函数两次运行b,c用的是同一栈内存，与变量名无关。
**/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

static int a ;
int x=3;
int ftest();
int teststatic();
int teststatic2();
int teststatic3();

int main(int argc,char *argv[]){

// test if a is initialize to 0. 
printf("a=%d\n",a);
a=9;
ftest();
ftest();
int b = 999; //  不会影响ftest里的b.
ftest();
ftest();

printf("a=%d\t x=%d\n",a,x);



//int b;	
//printf("a=%d b=%d\n",a,b);
	
//b only effects in ftest();
	
int i= 0;

while( i < 10 ){
//initialize();
teststatic();
teststatic2();
teststatic3();
i++;
}



return 0;

}

int ftest(){
static int b = 99;
printf("a=%d\tb=%d\n",a,b);
b++;
a++;
x++;
return 0;
}

int initialize(){
int d=0;
return 0;
}

int teststatic(){
int b;
b++;
printf("addr:%p\tvalueb:%d\n",&b,b);
return 0;
}

int teststatic2(){
int c;
c++;
printf("addr:%p\tvaluec:%d\n",&c,c);
return 0;
}

int 
teststatic3(){
int c;
c++;
printf("addr:%p\tvaluec:%d\n",&c,c);
return 0;
}
