#include <stdio.h>
int addtwo(int,int);
int main(){
int c  = 0;
	c = addtwo(2,3);
	
	char a[]={'a','b','c','d'};
	char b[]="cdef";
	printf("%d\t%d\n",sizeof(a),sizeof(b));
	printf("%c\n",*a);
	printf("%c\n",*(a+1));
	
		int ia[]={1,2,3,4,5,6,7,8};
		int i[] = {ia[0],ia[1],ia[2],ia[3]};
	printf("%d\n",sizeof(i));
	printf("%d\n",*(&i[8]));
	printf("%d\n",*(&i));
	printf("%p\t%p\t%p\n",&i[0],&i[0]+1,&i[1]);
	printf("%p\t%p\n",&i,&i+1);
	printf("%p\t%p\t%p\n",i,i+1,i+2);
		
		
	
		return 0;
}

int addtwo(int a, int b)
{
	return a+b;
}

	//~ movl	$0, -4(%ebp) // 初始化 c
	//~ movl	$3, 4(%esp) // 修改栈内数值。相当于把数值压入栈中。push stack from right to left with addtwo(2,3)
	//~ movl	$2, (%esp)
	//~ call	_addtwo
	//~ movl	%eax, -4(%ebp) // 赋值给c
	//~ movl	$0, %eax
	//~ leave
	//~ ret
//~ .globl _addtwo
	//~ .def	_addtwo;	.scl	2;	.type	32;	.endef
//~ _addtwo:
	//~ pushl	%ebp # 保存旧的bp (bp is a frame pointer)
	//~ movl	%esp, %ebp # 设置新的bp -- the frame pointer
	//~ movl	12(%ebp), %eax # 取出3 // 用bp操作栈内数据;为什么是12？ 因为 在参数2和参数1之前还有一个ebp。
	//~ addl	8(%ebp), %eax  #取出2，再加上3到%eax ；为什么是8?同上，ebp+4 取的是旧的ebp，ebp+8 取的是参数2，ebp+12 取的是参数1.数据都是按32位存放的。
	//~ popl	%ebp
	//~ ret
	//~ .def	_addtwo;	.scl	3;	.type	32;	.endef

