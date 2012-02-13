	.file	"t00090e.c"
.globl _var
	.data
	.align 4
_var:
	.long	9
	.section .rdata,"dr"
LC0:
	.ascii "var:%d\12\0"
	.text
.globl _printvar
	.def	_printvar;	.scl	2;	.type	32;	.endef
_printvar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	$0, %eax
	leave
	ret
	.def	_printf;	.scl	3;	.type	32;	.endef
