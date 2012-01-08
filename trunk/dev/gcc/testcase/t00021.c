/**
name: using enum
purpose: 
compiler: tcc/dev-cpp
summary:
refs:
http://wenku.baidu.com/view/17193729cfc789eb172dc818.html
http://www.west263.com/info/html/chengxusheji/C-C--/20080224/9672.html
枚举实际是一系列具有共性的整型变量的集合。枚举变量名是这一系列变量的抽象。
**/

#include <stdio.h>
int main(int argc,char *argv[]){
	
	enum weekday {Sunday, Monday, Tuesday,Wednesday, Thursday, Friday, Saturday};
	enum weekday wd;

	printf("%d\n",Sunday);
	printf("%d\n",Friday);
	printf("%d\n",sizeof(wd));
	//printf("%d\n",wd.Sunday); //error: `Sunday' is not a type sunday 是一个值。

	struct Test
	{
		int Num;
		char *pcName;
		short sDate;
		char cha[2];
		short sBa[4];
	} *p;

	printf("%d\n",sizeof(struct Test));
	printf("%d\n",sizeof( unsigned int));

return 0;

}







