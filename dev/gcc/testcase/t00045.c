/**
name:  test 内存越界
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:


refs: 
**/

#include <stdio.h>
int main(int argc,char *argv[]){
int i=0;
int a[10] = {0}; // 初始化为0;
for (i=0;i<=10;i++){ // 修改i的上界来测试
a[i]=i;
printf("%d\n",a[i]);
}
return 0;

}
