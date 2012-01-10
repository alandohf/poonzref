/**
name:  test strtok  
purpose: ���ַ�����ָ���ַ��ָ�
dependence: 
compiler: tcc/dev-cpp
summary:
char *strtok(char *restrict s1, const char *restrict delimiters);
work with  tcc , not work with gcc
refs:
http://blog.csdn.net/libuding/article/details/5870089
˵�����״ε���ʱ��sָ��Ҫ�ֽ���ַ�����֮���ٴε���Ҫ��s���NULL��
        strtok��s�в��Ұ�����delim�е��ַ�����NULL('/0')���滻��ֱ���ұ������ַ�����

����ֵ����s��ͷ��ʼ��һ�������ָ�Ĵ�����û�б��ָ�Ĵ�ʱ�򷵻�NULL��
           ����delim�а������ַ����ᱻ�˵����������˵��ĵط���Ϊһ���ָ�Ľڵ㡣
**/
// without  windows.h/string.h , vc6 not recognize  strchr,strcmp...
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
int main(int argc, char* argv[]) 
{ 
//char *strA="my,name,is,poon"; // strtok ��ͼ�޸�ȫ�ֳ�����ֵ��
char strA[]="my..,name,is,poon";

printf("strtok:%s\n",strtok(strA,","));  // "",not ''
printf("strtok:%s\n",strtok(NULL,","));  // "",not ''
printf("strtok:%s\n",strtok(NULL,","));  // "",not ''
printf("strtok:%s\n",strtok(NULL,","));  // "",not ''
printf("strtok:%s\n",strtok(strA,",")+2);  // "",not ''


return 0;

} 
