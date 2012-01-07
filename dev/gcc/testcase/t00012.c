/**
test const keyword no.2

Const 作用

1.   const类型定义：指明变量或对象的值是不能被更新,引入目的是为了取代预编译指令

2.   可以保护被修饰的东西，防止意外的修改，增强程序的健壮性。

3.   编译器通常不为普通const常量分配存储空间，而是将它们保存在符号表中，这使得它成为一个编译期间的常量，没有了存储与读内存的操作，使得它的效率也很高。

4.    可以节省空间，避免不必要的内存分配。


ps. const  可以修饰很多东西 ， 如数组，指针，函数，参数，等。见 1.11.5  c深度剖析
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alter1(void);
void alter2(void);
void alter3(void);
int main(int argc,char *argv[]){
	alter1();
	alter2();
	alter3();	
return 0;
}

void alter1(void){
printf("alter1: \n");

//p:所指的对象的值不能改变，可以更换所指的对象。
char *p1= "abc";
char *p2= "def";
const char *p; //可以理解为 对某块类型为char的内存 限制为const,这块内存将会由p指向。通过p操作这块内存时，不可改变内存对象的值。 即location read-only
p=p1;
printf("p=%s \n",p);
p=p2;
printf("p=%s \n",p);
//*p=*p1;
printf("p=%s \n",p);
//*p=*p2; //error: assignment of read-only location
printf("p=%s \n",p);

}



void alter2(void){
printf("alter2: \n");

//p:不可以更换所指的对象，可以修改所指对象的值。	
char *p1= "abc";
char *p2= "def";
//char * const p; // error: uninitialized const `p'
char * const p = p1; // correct 可以理解为 定义了一个指针，这个指针所指向的地址（对象的位置）是不可改变的，当然，对象的值的可以改变的。即variable p read-only
//p=p1;
printf("p=%s \n",p);
//p=p2; //error: assignment of read-only variable `p'
printf("p=%s \n",p);
*p=*p1;
*(p+1)=*(p1+1);
*(p+2)=*(p1+2);
printf("p=%s \n",p);
//strcpy(p,p1);  // illegal usage , becasue p has not allocated memory space 
//*p=*p2;
printf("p=%s \n",p);

}



void alter3(void){
printf("alter3: \n");
	
//p:既不可以更换所指的对象，也不可以修改所指对象的值。	
char *p1= "abc";
char *p2= "def";
//const char * const p; //error: uninitialized const `p'
const char * const p=p2; // both location & variable p are read-only
//p=p1;
printf("p=%s \n",p);
//p=p2;
printf("p=%s \n",p);
//*p=*p1;
printf("p=%s \n",p);
//*p=*p2;
printf("p=%s \n",p);

}

