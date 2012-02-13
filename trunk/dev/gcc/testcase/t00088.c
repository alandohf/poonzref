//http://www.youtube.com/watch?v=Z6zMxp6r4mc&NR=1&feature=endscreen
#include <stdio.h>

int main(void){
	int x = 0;
	x=x+++x; // (x++)+x ; 相当于 x=x+x  ; x=x+1
	int y = 0;
	y=++y+y; // y=y+1;y=y+y
	
	printf("x=%d,y=%d\n",x,y);
	

	int p=3,c;
	c=(++p)+(++p)+(++p); // p=p+1; 此时p=4 ;p=p+1; 此时p=5; c=p+p+(++p) ;--> c=10+(++p) = 10+6
	printf("c=%d\n",c);
	
	//~ movl	$3, -12(%ebp)
	//~ leal	-12(%ebp), %eax
	//~ incl	(%eax)
	//~ leal	-12(%ebp), %eax
	//~ incl	(%eax)
	//~ movl	-12(%ebp), %eax
	//~ movl	-12(%ebp), %edx
	//~ addl	%eax, %edx # 5+5 = 10 -> %edx
	//~ leal	-12(%ebp), %eax # 5-> (%eax)
	//~ incl	(%eax)	#(%eax) = 6
	//~ movl	%edx, %eax  # %eax = 10 
	//~ addl	-12(%ebp), %eax # 6+10  -> %eax
	//~ movl	%eax, -16(%ebp) # c= 16
	int q=3,d;
	d=(++q)+(++q)+(++q)+(++q)+(++q); // 同上理，d值应该是 31
	printf("d=%d\n",d);

	return 0;
}


	//~ movl	$0, -4(%ebp)
	//~ movl	-4(%ebp), %edx
	//~ leal	-4(%ebp), %eax
	//~ addl	%edx, (%eax)
	//~ leal	-4(%ebp), %eax
	//~ incl	(%eax)

	//~ movl	$0, -8(%ebp)
	//~ leal	-8(%ebp), %eax
	//~ incl	(%eax)
	//~ movl	-8(%ebp), %edx
	//~ leal	-8(%ebp), %eax
	//~ addl	%edx, (%eax)
// for printf
	//~ movl	-8(%ebp), %eax
	//~ movl	%eax, 8(%esp)
	//~ movl	-4(%ebp), %eax
	//~ movl	%eax, 4(%esp)
	//~ movl	$LC0, (%esp)
	//~ call	_printf


	//~ movl	$0, -4(%ebp)
	//~ movl	-4(%ebp), %edx
	//~ leal	-4(%ebp), %eax
	//~ addl	%edx, (%eax)
	//~ leal	-4(%ebp), %eax
	//~ incl	(%eax)
	//~ movl	$0, -8(%ebp)
	//~ leal	-4(%ebp), %eax
	//~ incl	(%eax)
	//~ movl	-4(%ebp), %eax
	//~ addl	-4(%ebp), %eax
	//~ movl	%eax, -8(%ebp)
	

