int main(void){
 register int a = 9;
	int b = 10;
return a+b;
}

	//~ movl	$9, %eax
	//~ movl	$10, -4(%ebp)
	//~ addl	-4(%ebp), %eax

//~ �ɼ�register �������ǣ�ֱ�ӽ����ݴ���Ĵ���������ջ�У�

