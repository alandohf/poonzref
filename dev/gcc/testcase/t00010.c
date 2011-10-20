/**
test extern keyword
1. auto init to zero
2.global var
3. can be omitted when in single file

**/

#include <stdio.h>

extern int a;
a=9;
int b = 10;
int c;
int main(int argc,char *argv[]){
printf("a=%d,b=%d c=%d\n",a,b,c);
return 0;
}
