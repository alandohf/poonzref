
int main()
{

	char a[4];
	char b[4]={'a','b','c','d'};
	int i;
	for ( i = 0 ; i < 4 ; i++){
			a[i] =  b[i];
	}
	
		return 0;
}

//~ call	__alloca
	//~ call	___main
	//~ movb	$97, -8(%ebp)		# a #b[4]={'a','b','c','d'}  a,b,c,d�ӵ͵��ߣ���ַҲ�Ǵӵ͵��ߡ�
	//~ movb	$98, -7(%ebp)		# b
	//~ movb	$99, -6(%ebp)		# c
	//~ movb	$100, -5(%ebp)		# d
	//~ movl	$0, -12(%ebp)		# i = 0
//~ L2:
	//~ cmpl	$3, -12(%ebp)	 	# i < 4
	//~ jg	L3
	//~ movl	%ebp, %eax			# ȡ�û���ַ 
	//~ addl	-12(%ebp), %eax	#ȡ�� iֵ ��Ϊ����index
	//~ leal	-4(%eax), %edx	    # -4 �� a[]���׸�Ԫ�ص�ƫ������-4(%eax) ~ a[i] ~ a[0] i �� #disp(base,index,scale)
	//~ movl	%ebp, %eax			#ȡ�û���ַ 
	//~ addl	-12(%ebp), %eax	#-12(%ebp)ȡ�� iֵ ��Ϊ����index,�������õ�
	//~ subl	$8, %eax			#ebp - 4 �� a ���׵�ַ��ebp -8 ��b���׵�ַ -12��%ebp) ��ƫ����i
	//~ movzbl	(%eax), %eax   # %eax��ַ�Ϸ���b[i], %eax ���b[i]��ֵ	
	//~ movb	%al, (%edx)		# %edx �� a[i] �ĵ�ַ �� (%edx) �� %edx�ϵ�ֵ , %al ��Ԫ��ֵ
	//~ leal	-12(%ebp), %eax # ȡ��i
	//~ incl	(%eax)			 # i++
	//~ jmp	L2
//~ L3:
	//~ movl	$0, %eax
	//~ leave
	//~ ret

//~ ���̣�
//~ 1.����a[i]:ȡ�û���ַ->ȡ��index
//~ 2.����b[i]:ȡ�û���ַ->ȡ��index->����b�������bp��ƫ��
//~ 3.ץȡ b[i]��ֵ�����浽�Ĵ���
//~ 4.�ӼĴ�����b[i]��ֵ����a[i]
//~ 5.i�Լ�

	char a[4][4];
	char b[4][4]={{'a','b','c','d'},{'A','B','C','D'},{'m','n','o','p'},{'D','E','F','G'}};
	int i,j ;
	for ( i = 0 ; i < 4 ; i++){
		for ( j = 0 ; j < 4 ; j++){
			a[i][j] =  b[i][j];
		}
	}
