	.file	"t00098.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	call	__alloca
	call	___main
	call	_f
	movl	$0, %eax
	leave
	ret
	.def	_f;	.scl	3;	.type	32;	.endef
_f:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
