
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
	//~ movb	$97, -8(%ebp)		# a #b[4]={'a','b','c','d'}  a,b,c,d从低到高，地址也是从低到高。
	//~ movb	$98, -7(%ebp)		# b
	//~ movb	$99, -6(%ebp)		# c
	//~ movb	$100, -5(%ebp)		# d
	//~ movl	$0, -12(%ebp)		# i = 0
//~ L2:
	//~ cmpl	$3, -12(%ebp)	 	# i < 4
	//~ jg	L3
	//~ movl	%ebp, %eax			# 取得基地址 
	//~ addl	-12(%ebp), %eax	#取得 i值 作为索引index
	//~ leal	-4(%eax), %edx	    # -4 是 a[]的首个元素的偏移量。-4(%eax) ~ a[i] ~ a[0] i 的 #disp(base,index,scale)
	//~ movl	%ebp, %eax			#取得基地址 
	//~ addl	-12(%ebp), %eax	#-12(%ebp)取得 i值 作为索引index,加起来得到
	//~ subl	$8, %eax			#ebp - 4 是 a 的首地址，ebp -8 是b的首地址 -12（%ebp) 是偏移量i
	//~ movzbl	(%eax), %eax   # %eax地址上放着b[i], %eax 存放b[i]的值	
	//~ movb	%al, (%edx)		# %edx 是 a[i] 的地址 ， (%edx) 是 %edx上的值 , %al 是元素值
	//~ leal	-12(%ebp), %eax # 取得i
	//~ incl	(%eax)			 # i++
	//~ jmp	L2
//~ L3:
	//~ movl	$0, %eax
	//~ leave
	//~ ret

//~ 过程：
//~ 1.索引a[i]:取得基地址->取得index
//~ 2.索引b[i]:取得基地址->取得index->计算b数组相对bp的偏移
//~ 3.抓取 b[i]的值，保存到寄存器
//~ 4.从寄存器把b[i]的值赋给a[i]
//~ 5.i自加

	char a[4][4];
	char b[4][4]={{'a','b','c','d'},{'A','B','C','D'},{'m','n','o','p'},{'D','E','F','G'}};
	int i,j ;
	for ( i = 0 ; i < 4 ; i++){
		for ( j = 0 ; j < 4 ; j++){
			a[i][j] =  b[i][j];
		}
	}
