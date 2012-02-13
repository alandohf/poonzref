int addtwo(char,char);
int main(){
int c  = 0;
	c = addtwo(1,2);
		return 0;
}

int addtwo(char a, char b)
{
	return a+b;
}


//~ _addtwo:
	//~ pushl	%ebp
	//~ movl	%esp, %ebp
	//~ subl	$4, %esp
	//~ movl	8(%ebp), %eax
	//~ movl	12(%ebp), %edx
	//~ movb	%al, -1(%ebp)
	//~ movb	%dl, -2(%ebp)
	//~ movsbl	-1(%ebp),%eax
	//~ movsbl	-2(%ebp),%edx
	//~ addl	%edx, %eax
	//~ leave
	//~ ret
	//~ .def	_addtwo;	.scl	3;	.type	32;	.endef