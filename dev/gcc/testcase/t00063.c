/**
name: restrict
purpose:  
dependence: 
compiler: tcc/dev-cpp
summary:

refs:
http://bymeok.blog.163.com/blog/static/11865813220094312429783/

�ڴ��������memcpy��memccpy��memmove��memcmp...  

2009-03-30 14:26:25|  ���ࣺ c++ |�ֺ� ����
�ڴ��������memcpy��memccpy��memmove��memcmp...
 
����ԭ�ͣ�extern void *memcpy(void *dest, void *src, unsigned int count);
����˵����destΪĿ���ַ�����srcΪԴ�ַ�����countΪҪ�������ֽ�����
        
���ڿ�����#include <string.h>

�������ܣ����ַ���src�е�ǰn���ֽڿ�����dest�С�

����˵����src��dest��ָ�ڴ��������ص�����������void*ָ�롣 //ע��memcpy���ص���void*����


����ԭ�ͣ�extern void *memccpy(void *dest, void *src, unsigned char ch, unsigned int count);

����˵����destΪĿ���ַ�����srcΪԴ�ַ�����chΪ��ֹ���Ƶ��ַ�(�����ƹ���������ch��ֹͣ����)��countΪҪ�������ֽ�����
        
���ڿ�����#include <string.h>

�������ܣ����ַ���src�е�ǰn���ֽڿ�����dest�У�ֱ�������ַ�ch��ֹͣ���ơ�

����˵����src��dest��ָ�ڴ��������ص�����������void*����ָ��

����ԭ�ͣ�extern void *memmove(void *dest, const void *src, unsigned int count)

����˵����destΪĿ���ַ�����srcΪԴ�ַ�����countΪҪ�������ֽ�����
        
���ڿ�����#include <string.h>

�������ܣ����ַ���src�е�ǰn���ֽڿ�����dest�С�

����˵����dest��src��ָ�ڴ���������ص��������ƺ�src���ݻᱻ���ġ���������ָ��dest��ָ�롣

ԭ�ͣ�extern void *memchr(void *buf, char ch, unsigned count);

�÷���#include <string.h>

���ܣ���buf��ָ�ڴ������ǰcount���ֽڲ����ַ�ch��

˵��������һ�������ַ�chʱֹͣ���ҡ�����ɹ�������ָ���ַ�ch��ָ�룻���򷵻�NULL��

ԭ�ͣ�extern int memcmp(void *buf1, void *buf2, unsigned int count);
        
�÷���#include <string.h>

���ܣ��Ƚ��ڴ�����buf1��buf2��ǰcount���ֽڡ�

˵����
        ��buf1<buf2ʱ������ֵ<0
        ��buf1=buf2ʱ������ֵ=0
        ��buf1>buf2ʱ������ֵ>0
ԭ�ͣ�extern int memicmp(void *buf1, void *buf2, unsigned int count);
        
�÷���#include <string.h>

���ܣ��Ƚ��ڴ�����buf1��buf2��ǰcount���ֽڵ���������ĸ�Ĵ�Сд��

˵����memicmpͬmemcmp��Ψһ������memicmp�����ִ�Сд��ĸ��
        ��buf1<buf2ʱ������ֵ<0
        ��buf1=buf2ʱ������ֵ=0
        ��buf1>buf2ʱ������ֵ>0
ԭ�ͣ�extern void *memset(void *buffer, int c, int count);
        
�÷���#include <string.h>

���ܣ���buffer��ָ�ڴ������ǰcount���ֽ����ó��ַ�c��

˵��������ָ��buffer��ָ�롣
**/


