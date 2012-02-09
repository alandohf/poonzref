	.file	"t00076.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "abcdefgh\0"
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
	movl	LC0, %eax
	movl	LC0+4, %edx
	movl	%eax, -8(%ebp)
	movl	%edx, -4(%ebp)
	movb	$-33, %dl
	leal	-8(%ebp), %eax
	andb	%dl, (%eax)
	movl	$-1, %eax
	leave
	ret
