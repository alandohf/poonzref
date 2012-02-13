int main(void){
 register int a = 9;
	int b = 10;
return a+b;
}

	//~ movl	$9, %eax
	//~ movl	$10, -4(%ebp)
	//~ addl	-4(%ebp), %eax

//~ 可见register 的作用是，直接将数据存入寄存器，而非栈中！

