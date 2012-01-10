/**
name:  test strtok  
purpose: 将字符串按指定字符分割
dependence: 
compiler: tcc/dev-cpp
summary:
char *strtok(char *restrict s1, const char *restrict delimiters);
work with  tcc , not work with gcc
refs:
http://blog.csdn.net/libuding/article/details/5870089
说明：首次调用时，s指向要分解的字符串，之后再次调用要把s设成NULL。
        strtok在s中查找包含在delim中的字符并用NULL('/0')来替换，直到找遍整个字符串。

返回值：从s开头开始的一个个被分割的串。当没有被分割的串时则返回NULL。
           所有delim中包含的字符都会被滤掉，并将被滤掉的地方设为一处分割的节点。
**/
// without  windows.h/string.h , vc6 not recognize  strchr,strcmp...
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
int main(int argc, char* argv[]) 
{ 
//char *strA="my,name,is,poon"; // strtok 试图修改全局常量的值？
char strA[]="my..,name,is,poon";

printf("strtok:%s\n",strtok(strA,","));  // "",not ''
printf("strtok:%s\n",strtok(NULL,","));  // "",not ''
printf("strtok:%s\n",strtok(NULL,","));  // "",not ''
printf("strtok:%s\n",strtok(NULL,","));  // "",not ''
printf("strtok:%s\n",strtok(strA,",")+2);  // "",not ''


return 0;

} 
