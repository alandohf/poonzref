/**
i++ and ++i 
http://zhidao.baidu.com/question/2414662.html?an=0&si=1
简单的来说，++i 和 i++,在单独使用时，就是 i=i+1。
而 a = ++i，相当于 i=i+1; a = i;
而 a = i++，相当于 a = i; i=i+1;
引入临时变量来保存返回值，就明了了！
**/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
int main(int argc,char *argv[]){
int a , b;
a = 0;
b = 0;
printf("a=%d,b=%d \n",a,b);
printf("a=%d,b=%d \n",a++,++b);
printf("a=%d,b=%d \n",a,b);
a++;
b++;
printf("a=%d,b=%d \n",a,b);
return 0;
}
