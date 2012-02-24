
int main()
{

	char a[4][4];
	char b[4][4]={{'a','b','c','d'},{'A','B','C','D'},{'m','n','o','p'},{'D','E','F','G'}};
	int i,j ;
	for ( i = 0 ; i < 4 ; i++){
		for ( j = 0 ; j < 4 ; j++){
			a[i][j] =  b[i][j];
		}
	}
	
		return 0;
}



二维数组：
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -60(%ebp)
	movl	-60(%ebp), %eax
	call	__alloca
	call	___main
	movb	$97, -40(%ebp)
	movb	$98, -39(%ebp)
	movb	$99, -38(%ebp)
	movb	$100, -37(%ebp)
	movb	$65, -36(%ebp)
	movb	$66, -35(%ebp)
	movb	$67, -34(%ebp)
	movb	$68, -33(%ebp)
	movb	$109, -32(%ebp)
	movb	$110, -31(%ebp)
	movb	$111, -30(%ebp)
	movb	$112, -29(%ebp)
	movb	$68, -28(%ebp)
	movb	$69, -27(%ebp)
	movb	$70, -26(%ebp)
	movb	$71, -25(%ebp)
	movl	$0, -44(%ebp)
L2:
	cmpl	$3, -44(%ebp)
	jg	L3
	movl	$0, -48(%ebp)
L5:
	cmpl	$3, -48(%ebp)
	jg	L4
	movl	-44(%ebp), %eax	# i
	sall	$2, %eax  			#相当于乘4，index*scale
	addl	-48(%ebp), %eax	# i*4+j
	leal	-8(%ebp), %edx		# 传a的地址?
	addl	%edx, %eax
	leal	-16(%eax), %edx	# a数组首元素，
	
	
	movl	-44(%ebp), %eax
	sall	$2, %eax
	addl	-48(%ebp), %eax
	leal	-8(%ebp), %ecx
	addl	%ecx, %eax
	subl	$32, %eax
	movzbl	(%eax), %eax
	movb	%al, (%edx)		  #赋值
	leal	-48(%ebp), %eax  #i
	incl	(%eax)				#i++
	jmp	L5
L4:
	leal	-44(%ebp), %eax
	incl	(%eax)
	jmp	L2
L3:
	movl	$0, %eax
	leave
	ret

# 二维数组计算元素地址复杂一点，总的来讲就是先算index，再和base addr 以及 disp 做运算得出 a[i][j],b[i][j]的地址，然后赋值。
