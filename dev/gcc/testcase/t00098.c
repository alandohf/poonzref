// static : 在汇编中就是去掉.globl
#include <stdio.h>

static int f();

int main(void){
f();
return 0;
}

static int f(){
;
return 0;
}
