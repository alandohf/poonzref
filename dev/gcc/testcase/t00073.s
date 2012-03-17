	.file	"t00073.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC2:
	.ascii "%d loops in %f seconds\12\0"
LC3:
	.ascii "PAUSE\0"
	.align 8
LC0:
	.long	0
	.long	1083129856
	.align 8
LC1:
	.long	0
	.long	1076101120
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
	movl	$0, -12(%ebp)
L2:
	leal	-12(%ebp), %eax
	incl	(%eax)
	call	_clock
	pushl	%eax
	fildl	(%esp)
	leal	4(%esp), %esp
	fldl	LC0
	fdivrp	%st, %st(1)
	fstpl	-8(%ebp)
	fldl	-8(%ebp)
	fldl	LC1
	fucompp
	fnstsw	%ax
	sahf
	jae	L2
	fldl	-8(%ebp)
	fstpl	8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC2, (%esp)
	call	_printf
	movl	$LC3, (%esp)
	call	_system
	movl	$0, %eax
	leave
	ret
	.def	_system;	.scl	3;	.type	32;	.endef
	.def	_printf;	.scl	3;	.type	32;	.endef
	.def	_clock;	.scl	3;	.type	32;	.endef