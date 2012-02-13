	.file	"t00091.c"
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
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	call	__alloca
	call	___main
	movl	$0, -4(%ebp)
	movl	$3, 4(%esp)
	movl	$2, (%esp)
	call	_addtwo
	movl	%eax, -4(%ebp)
	movl	$0, %eax
	leave
	ret
.globl _addtwo
	.def	_addtwo;	.scl	2;	.type	32;	.endef
_addtwo:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	addl	8(%ebp), %eax
	popl	%ebp
	ret
	.def	_addtwo;	.scl	3;	.type	32;	.endef
