/**
name: test  malloc &  var life
purpose: 
dependence: 
compiler: tcc/dev-cpp
summary:
refs:
http://topic.csdn.net/u/20080406/00/9c51e071-d358-4a78-a4de-5ef635603a81.html
http://topic.csdn.net/u/20070411/19/8c787f29-0c01-4f09-9e73-46d71adc1613.html
可以通过建立一个指针fp保存函数返回的p，free(fp)来间接销毁p;
**/

#include <stdio.h>
#include <stdlib.h>

char *testmalloc(void);
int main(int argc,char *argv[]){
	char* fp; // p's value is an address , fp save this value.
	printf("----------------------------------------------------\n");
	printf("addr_of_p:%p\n",testmalloc()); // testmalloc() 's address value = fp 's address value; 
	printf("addr_of_p:%p\n",testmalloc()); // testmalloc() 's address value = fp 's address value; 
	
	fp=testmalloc();
	printf("addr:%p\tvalue:%s\n",fp,fp); // fp = p 's address value
	 //free(p); // 'p' undeclared
	free(fp);
	printf("addr:%p\tvalue:%s\n\n\n",fp,fp);
	printf("----------------------------------------------------\n");
	
	fp=testmalloc();
	printf("addr:%p\tvalue:%s\n",fp,fp);
	free(fp);
	printf("addr_of_p:%p\tvalue:%s\n",testmalloc(),testmalloc()); // testmalloc() 's address value = fp 's address value; 
	//如果前一次调用函数，函数内的p未被释放，再次调用就会新开一快内存来保存p;
	printf("----------------------------------------------------\n");
	fp=testmalloc();	
	printf("addr:%p\tvalue:%s\n",fp,fp);	// 返回值p的地址
	//	printf("addr:%p\tvalue:%s\n",testmalloc(),testmalloc());
	printf("addr_of_func_itself:%p\tvalue:%s\n",testmalloc,fp); //函数本身的地址
	printf("addr_of_func_itself:%p\tvalue:%s\n",(*testmalloc)(),fp); //通过函数地址求函数返回的p
//	printf("addr:%p\tvalue:%s\n",testmalloc,testmalloc());
	free(fp);
	printf("addr:%p\tvalue:%s\n",fp,fp);	
	system("PAUSE");
	return 0;
}

char *testmalloc(void){
	char *p;
	char str[100];
	p=(char*)malloc(100);
	sprintf(p,"%s\n","abcdefg");
	//sprintf(str,"%s\n",p); // str=p ; not work !
	//free(p); // after free,p's value is reset!
	//printf("%s\n",str);
	printf("INSIDE_FUNCTON:addr:%p\tvalue:%s\n",p,p);
	//return str; //warning: address of local variable `str' returned
	return p;
}

