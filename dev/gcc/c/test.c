#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[]){
char* str;
str=strrchr("hello, world", ',');
printf(str);
printf("\n");
return 0;
}


