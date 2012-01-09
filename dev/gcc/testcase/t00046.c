/**
name:  test 内存越界
purpose:  test heap size
dependence: 
compiler: tcc/dev-cpp
summary:
valgrind , gdb

2.申请效率的比较
　　栈由系统自动分配，速度较快。但程序员是无法控制的。  
　　堆是由new分配的内存，一般速度比较慢，而且容易产生内存碎片,不过用起来最方便.

3.申请大小的限制  
　　栈：在Windows下,栈是向低地址扩展的数据结构，是一块连续的内存的区域。这句话的意思是栈顶的地址和栈的最大容量是系统预先规定好的，在 WINDOWS下，栈的大小是2M（也有的说是1M，总之是一个编译时就确定的常数），如果申请的空间超过栈的剩余空间时，将提示overflow。因此，能从栈获得的空间较小。  
　　堆：堆是向高地址扩展的数据结构，是不连续的内存区域。这是由于系统是用链表来存储的空闲内存地址的，自然是不连续的，而链表的遍历方向是由低地址向高地址。堆的大小受限于计算机系统中有效的虚拟内存。由此可见，堆获得的空间比较灵活，也比较大。 

refs: 
http://topic.csdn.net/u/20090922/10/dbf7a5b7-f426-4d89-a3e9-38d843cca94a.html
http://wenku.baidu.com/view/a943ebc589eb172ded63b76e.html
http://c.group.iteye.com/group/wiki/784-c-exception-handling-mechanism
example:
http://topic.csdn.net/u/20071229/15/54aa6ae5-0527-4809-9f56-177768e0f5b3.html 

**/

#include <stdio.h>
#include <stdlib.h>
#define I 1024
#define J 2070 // adj this value
char* heapsize();

int 
main(int argc,char *argv[]){
/**	char *p1,*p2;
	p1 = (char*)malloc(10);
	p2 = (char*)malloc(1000000000);

	//p2 = (char*)malloc(100000000000000000);
	//printf("%p\n",p1);
	//printf("%p\n",p2); // overflow
	free(p1);
	free(p2);
	
**/

char  c_a[I][J]={'a'};

int i=0 , j=0;
do{
i++;
do{
j++;
//if(c_a[I][J] != 0){
printf("%d\t%d\t%d\n",i,j,c_a[I][J]);
//;
//}
}while(j<J);
}while(i < I );

	/**
int i=0 , j=0;
for(i=0;i<I;i++) {
	for (j = 0 ; j<J;j++){
		c_a[i][j]='a';
		if(c_a[i][j]!='a'){
		printf("%d\t%d\t%c\n",i,j,c_a[i][j]);
		}

	}
	
}
**/

/**
	int i = 0;
	int n = 1;
	char*	p_init = (char*)malloc(1024*1024);
	while(1){
		i++;
		n=i*1024*1024;
		p2 = (char*)malloc(n);
		printf("%p\t%d\ti:%fMB\n",p2,n,i*1.00/1024); // overflow
		if(NULL ==p2){
			char*	p_init = (char*)malloc(1024*1024);
		free(p2);
		break;	
		}
		free(p2);

	}
	
**/


// heap memory allocate test:

/**
char *cptr_heap[10];
int i = 0;
for ( i = 0 ; i < 10 ; i++){
		cptr_heap[i]=heapsize();
		printf("the heap memory allocated above start at:%p\n",cptr_heap[i]);
}
**/
	return 0;

}


char*
heapsize(){
//char* cp_initaddr = (char*) malloc(1);
//printf("%p\n",cp_initaddr);
int n = 1024*2*2;
	while(1){
	//char* cp_prevaddr = (char*) malloc(n);
	n=n+1024*2*2; // 4KByte的步长
	//printf("%d\n",n);
	char* cp_endaddr = (char*) malloc(n);

		if (n%(1024*1024*2*2) == 0){
			printf("start at %p\tallocated:%d MByte\t end at %p\n"
			,cp_endaddr , n/1024/1024,cp_endaddr+n);
		}
		
		if(NULL == cp_endaddr){
			//printf("%p\n",cp_prevaddr);
			//printf("%d\n",cp_prevaddr - cp_initaddr);
			//printf("%d\n",n);
			printf("---------------------------------------------------------------------\n");
			return (char*) malloc(n-1024*2*2);
			//return n;
		}
		else{
			free(cp_endaddr);
		}
	}
}
