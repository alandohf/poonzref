/**
name:  test strstr  
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
0.��������ƥ���ַ���
1.����ָ���һ�γ���needleλ�õ�ָ�룬���û�ҵ��򷵻�NULL��
refs:
http://baike.baidu.com/view/745156.htm
**/
// without  windows.h/string.h , vc6 not recognize  strchr,strcmp...
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
int main(int argc, char* argv[]) 
{ 
char *strA="ababcd";
char *strB="abc";

printf("strstr:%s\n",strstr(strA,strB)); 


return 0;

} 
