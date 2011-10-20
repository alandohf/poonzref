/**
test perror()

　perror ( )用 来 将 上 一 个 函 数 发 生 错 误 的 原 因 输 出 到 标 准 设备 (stderr) 。参数 s 所指的字符串会先打印出,后面再加上错误原因字符串。此错误原因依照全局变量error 的值来决定要输出的字符串。
　　在库函数中有个error变量，每个error值对应着以字符串表示的错误类型。当你调用"某些"函数出错时，该函数已经重新设置了error的值。perror函数只是将你输入的一些信息和现在的error所对应的错误一起输出。


**/
#include <stdio.h>


int main(int argc,char *argv[]){
//char * p;strcpy(p,"def"); // illegal
FILE *fp;
fp = fopen( "/root/noexitfile", "r+" );
if ( NULL == fp )
{
perror("/root/noexitfile");
}
extern error ;
error = -100;
while ( error < 100)
{
perror("test");
error++;
}
return 0;

}
