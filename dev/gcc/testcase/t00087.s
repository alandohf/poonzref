	.file	"t00087.c"
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
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	call	__alloca
	call	___main
	movl	$5, -4(%ebp)
	movl	$0, -8(%ebp)
	movl	$0, %eax
	leave
	ret
