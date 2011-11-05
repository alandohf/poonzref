/**
name: test how the array item arrange
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.对指针进行加1 操作，得到的是下一个元素的地址，而不是原有地址值直接加1。
2.一个类型为T 的指针的移动，以sizeof(T) 为移动单位

refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

int a[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};

int i=0,j=0;

for (i=0;i<3;i++){
    for(j=0;j<4;j++){
	    printf("%p\t%d\n",&a[i][j],a[i][j]);
	}
}

return 0;
}


