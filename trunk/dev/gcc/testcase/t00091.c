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

	//~ movl	$0, -4(%ebp) // ��ʼ�� c
	//~ movl	$3, 4(%esp) // �޸�ջ����ֵ���൱�ڰ���ֵѹ��ջ�С�push stack from right to left with addtwo(2,3)
	//~ movl	$2, (%esp)
	//~ call	_addtwo
	//~ movl	%eax, -4(%ebp) // ��ֵ��c
	//~ movl	$0, %eax
	//~ leave
	//~ ret
//~ .globl _addtwo
	//~ .def	_addtwo;	.scl	2;	.type	32;	.endef
//~ _addtwo:
	//~ pushl	%ebp # ����ɵ�bp (bp is a frame pointer)
	//~ movl	%esp, %ebp # �����µ�bp -- the frame pointer
	//~ movl	12(%ebp), %eax # ȡ��3 // ��bp����ջ������;Ϊʲô��12�� ��Ϊ �ڲ���2�Ͳ���1֮ǰ����һ��ebp��
	//~ addl	8(%ebp), %eax  #ȡ��2���ټ���3��%eax ��Ϊʲô��8?ͬ�ϣ�ebp+4 ȡ���Ǿɵ�ebp��ebp+8 ȡ���ǲ���2��ebp+12 ȡ���ǲ���1.���ݶ��ǰ�32λ��ŵġ�
	//~ popl	%ebp
	//~ ret
	//~ .def	_addtwo;	.scl	3;	.type	32;	.endef

