/**
name: restrict
purpose:  
dependence: 
compiler: tcc/dev-cpp
summary:

refs:
http://bymeok.blog.163.com/blog/static/11865813220094312429783/

内存操作函数memcpy，memccpy，memmove，memcmp...  

2009-03-30 14:26:25|  分类： c++ |字号 订阅
内存操作函数memcpy，memccpy，memmove，memcmp...
 
函数原型：extern void *memcpy(void *dest, void *src, unsigned int count);
参数说明：dest为目的字符串，src为源字符串，count为要拷贝的字节数。
        
所在库名：#include <string.h>

函数功能：将字符串src中的前n个字节拷贝到dest中。

返回说明：src和dest所指内存区域不能重叠，函数返回void*指针。 //注意memcpy返回的是void*类型


函数原型：extern void *memccpy(void *dest, void *src, unsigned char ch, unsigned int count);

参数说明：dest为目的字符串，src为源字符串，ch为终止复制的字符(即复制过程中遇到ch就停止复制)，count为要拷贝的字节数。
        
所在库名：#include <string.h>

函数功能：将字符串src中的前n个字节拷贝到dest中，直到遇到字符ch便停止复制。

返回说明：src和dest所指内存区域不能重叠，函数返回void*类型指针

函数原型：extern void *memmove(void *dest, const void *src, unsigned int count)

参数说明：dest为目的字符串，src为源字符串，count为要拷贝的字节数。
        
所在库名：#include <string.h>

函数功能：将字符串src中的前n个字节拷贝到dest中。

返回说明：dest和src所指内存区域可以重叠，但复制后src内容会被更改。函数返回指向dest的指针。

原型：extern void *memchr(void *buf, char ch, unsigned count);

用法：#include <string.h>

功能：从buf所指内存区域的前count个字节查找字符ch。

说明：当第一次遇到字符ch时停止查找。如果成功，返回指向字符ch的指针；否则返回NULL。

原型：extern int memcmp(void *buf1, void *buf2, unsigned int count);
        
用法：#include <string.h>

功能：比较内存区域buf1和buf2的前count个字节。

说明：
        当buf1<buf2时，返回值<0
        当buf1=buf2时，返回值=0
        当buf1>buf2时，返回值>0
原型：extern int memicmp(void *buf1, void *buf2, unsigned int count);
        
用法：#include <string.h>

功能：比较内存区域buf1和buf2的前count个字节但不区分字母的大小写。

说明：memicmp同memcmp的唯一区别是memicmp不区分大小写字母。
        当buf1<buf2时，返回值<0
        当buf1=buf2时，返回值=0
        当buf1>buf2时，返回值>0
原型：extern void *memset(void *buffer, int c, int count);
        
用法：#include <string.h>

功能：把buffer所指内存区域的前count个字节设置成字符c。

说明：返回指向buffer的指针。
**/


