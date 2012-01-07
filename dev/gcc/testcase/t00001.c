/**
test strrchr
　　strrchr() 函数查找字符在指定字符串中从后面开始的第一次出现的位置，如果成功，则返回指向该位置的指针，如果失败，则返回 false。

**/
#include <stdio.h> 
#include <string.h>
int main(int argc,char *argv[]){
char* str;
str=strrchr("hello, world", ',');
printf(str);
printf("\n");
return 0;
}


