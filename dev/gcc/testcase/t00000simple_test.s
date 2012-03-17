	.file	"t00000simple_test.c"
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
	movl	$5, (%esp)
	call	_recusive
	movl	$0, %eax
	leave
	ret
.globl _caller
	.def	_caller;	.scl	2;	.type	32;	.endef
_caller:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$1, -4(%ebp)
	movl	$2, -8(%ebp)
	movl	$3, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	_bycall
	movl	$0, %eax
	leave
	ret
.globl _bycall
	.def	_bycall;	.scl	2;	.type	32;	.endef
_bycall:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	addl	8(%ebp), %eax
	addl	16(%ebp), %eax
	popl	%ebp
	ret
.globl _recusive
	.def	_recusive;	.scl	2;	.type	32;	.endef
_recusive:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpl	$1, 8(%ebp)
	jne	L5
	movl	$1, -4(%ebp)
	jmp	L4
L5:
	movl	8(%ebp), %eax
	decl	%eax
	movl	%eax, (%esp)
	call	_recusive
	imull	8(%ebp), %eax
	movl	%eax, -4(%ebp)
L4:
	movl	-4(%ebp), %eax
	leave
	ret
	.def	_bycall;	.scl	3;	.type	32;	.endef
	.def	_recusive;	.scl	3;	.type	32;	.endef
