	.file	"t00088.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "x=%d,y=%d\12\0"
LC1:
	.ascii "c=%d\12\0"
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	call	__alloca
	call	___main
	movl	$0, -4(%ebp)
	movl	-4(%ebp), %edx
	leal	-4(%ebp), %eax
	addl	%edx, (%eax)
	leal	-4(%ebp), %eax
	incl	(%eax)
	movl	$0, -8(%ebp)
	leal	-8(%ebp), %eax
	incl	(%eax)
	movl	-8(%ebp), %edx
	leal	-8(%ebp), %eax
	addl	%edx, (%eax)
	movl	-8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	$3, -12(%ebp)
	leal	-12(%ebp), %eax
	incl	(%eax)
	leal	-12(%ebp), %eax
	incl	(%eax)
	movl	-12(%ebp), %eax
	movl	-12(%ebp), %edx
	addl	%eax, %edx
	leal	-12(%ebp), %eax
	incl	(%eax)
	movl	%edx, %eax
	addl	-12(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	$0, %eax
	leave
	ret
	.def	_printf;	.scl	3;	.type	32;	.endef
