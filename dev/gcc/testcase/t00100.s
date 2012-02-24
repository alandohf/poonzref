	.file	"t00100.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	call	__alloca
	call	___main
	movb	$97, -8(%ebp)
	movb	$98, -7(%ebp)
	movb	$99, -6(%ebp)
	movb	$100, -5(%ebp)
	movl	$0, -12(%ebp)
L2:
	cmpl	$3, -12(%ebp)
	jg	L3
	movl	%ebp, %eax
	addl	-12(%ebp), %eax
	leal	-4(%eax), %edx
	movl	%ebp, %eax
	addl	-12(%ebp), %eax
	subl	$8, %eax
	movzbl	(%eax), %eax
	movb	%al, (%edx)
	leal	-12(%ebp), %eax
	incl	(%eax)
	jmp	L2
L3:
	movl	$0, %eax
	leave
	ret
