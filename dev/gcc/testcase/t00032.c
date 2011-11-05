/**
name: test  address
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:

名字a 一旦
与这块内存匹配就不能被改变。a[0],a[1]等为a 的元素，但并非元素的名字。数组的每一个
元素都是没有名字的。那现在再来回答第一章讲解sizeof 关键字时的几个问题：
sizeof(a)的值为sizeof(int)*5，32 位系统下为20。
sizeof(a[0])的值为sizeof(int)，32 位系统下为4。

2.。a 作为右值时其意义与&a[0]是一样，代表的是数组首元素的首地址，而不是数组
的首地址。

3.a 不能作为左值！这个错误几乎每一个学生都犯过.

4.。其实我们完全可以把a 当一个普通的变量来看，只不过这个变量内部分为很多小块，
我们只能通过分别访问这些小块来达到访问整个变量a 的目的。

refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){
int a[5];
printf("size:%d\n",sizeof(a));
printf("size:%d\n",sizeof(a[0]));
printf("size:%d\n",sizeof(a[9])); 
/**而关键字sizeof 求值是在编译的时候。虽然并不存在
a[5]这个元素，但是这里也并没有去真正访问a[5],而是仅仅根据数组元素的类型来确定其
值。所以这里使用a[5]并不会出错。 **/

system("PAUSE");
return 0;
}


