/**
本质上C只有传值，没有传址。按值的类型，分为传址和传值！
**/

#include <stdio.h>

int copyval(int a );
int modval (int *a );

int main() {
int i;
int b = 99;
int c = 999;
//printf("%d\n",copyval(b));
//printf("%d\n",modval(&c));
for(i=1;i<=2 ; i++){
copyval(b);
modval(&c);
printf("%d\n",b);
printf("%d\n",c);
}
return 0;
}

int copyval(int a ){
a=a+1;
printf("%d\n",a);
}

int modval(int *a ){
*a=*a+1;
printf("%d\n",*a);
}

