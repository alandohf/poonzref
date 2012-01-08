/**
name: test how the array item arrange
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
1.数组元素从低地址向高地址排列
2.内层数组按外层的顺序依次排列
a[0],[a1]..表达的是外层数组；
要表达最小的内层数组元素，需要所有维度参与a[i][j]。
3.维度越多[][][]..，表达的元素越细，否则越粗。
refs: 4.2.3 c in deep
**/

#include <stdio.h>

int main(int argc,char *argv[]){

int a[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};

int i=0,j=0;

for (i=0;i<3;i++){
    for(j=0;j<4;j++){
	    printf("a[%d][%d]\t%p\t%d\ta[%d]=%d\n"
				,i,j,&a[i][j],a[i][j],i,*(a[i]));
	}
}

return 0;

}
