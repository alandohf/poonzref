/**
i++ and ++i 
http://zhidao.baidu.com/question/2414662.html?an=0&si=1
�򵥵���˵��++i �� i++,�ڵ���ʹ��ʱ������ i=i+1��
�� a = ++i���൱�� i=i+1; a = i;
�� a = i++���൱�� a = i; i=i+1;
������ʱ���������淵��ֵ���������ˣ�
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
