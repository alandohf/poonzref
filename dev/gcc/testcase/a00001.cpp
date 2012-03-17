/**
* example: test getc 并屏蔽空格输入 in c 
*
**/

//~ #include <iostream>
//~ using namespace std;

//~ int 
//~ main(){
	//~ cout<<"hello world!"<<endl;
//~ return 0;	
//~ }


#include <stdio.h>

int main(int argc, char *argv[]) {
	int i = 0 ,c,retc, sum = 0;
	do{
		while( 1 ){
		c=getchar();
			if(' ' == c ||  '1' == c ) // 跳过特定字符 ， 如 ' ' 和 '1' ; 存在问题：如果是11 也会跳过！
			{
				;
			}else{
				break;
			}
		} //end w
	//
		retc=ungetc(c,stdin);	// 先取一个字符，判断是否要跳过，再回退，供scanf读取。
		sum += i;				// 第一次与0相加，等到第二次循环才和读入的i相加。
		if (c == '\n') break;
	} while (scanf("%d",&i) == 1);
	
	printf("%d\n",sum);
	return 0;
}
