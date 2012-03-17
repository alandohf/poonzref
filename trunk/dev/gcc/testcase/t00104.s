	.file	"t00104.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
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
	movl	%eax, -44(%ebp)
	movl	-44(%ebp), %eax
	call	__alloca
	call	___main
	movl	$1, -40(%ebp)
	movl	$2, -36(%ebp)
	movl	$3, -32(%ebp)
	movl	$4, -28(%ebp)
	movl	$5, -24(%ebp)
	movl	$6, -20(%ebp)
	movl	$7, -16(%ebp)
	movl	$8, -12(%ebp)
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	_fn
	movl	$0, %eax
	leave
	ret
	.section .rdata,"dr"
LC0:
	.ascii "%d\12\0"
	.text
.globl _fn
	.def	_fn;	.scl	2;	.type	32;	.endef
_fn:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	addl	$4, %eax
	movl	$100, (%eax)
	movl	$4, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	$0, %eax
	leave
	ret
	.def	_printf;	.scl	3;	.type	32;	.endef
	.def	_fn;	.scl	3;	.type	32;	.endef
