	.file	"t00096.c"
	.data
	.align 4
_s:
	.long	9
	.def	___main;	.scl	2;	.type	32;	.endef
	.align 4
i.0:
	.long	3
	.align 4
j.1:
	.long	4
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
	incl	i.0
	movl	i.0, %eax
	addl	_s, %eax
	addl	j.1, %eax
	leave
	ret
