// sizeof test
#include <stdio.h>
#include <string.h>
//~ int f();

int caller();
int bycall(int a,int b , int c);
int recusive(int);
int dead_recusive(int a);
int run_cnt=0;
int main()
{
	//~ int a=0;
	//~ int b=1;
	//~ int c=2;
	//~ int d=9;
	//caller();	
	//recusive( 5 );
	printf("%p\n",dead_recusive);
	dead_recusive(1); //129975 //64876
//	printf("run_cnt : %d\n",run_cnt);
	//printf("%d\n",recusive( 5 ));
//	a|b=b?c:d;
	//printf("addr:%p\n%p\n%p\n",&a,&b,&c);
	//~ int ovar=34;
	//~ asm("movl %0, %%ebx\n\t":"+b"(ovar):"g"(100));
	//char b[3][5];
	//b[0]="abcd";
	//~ char a[4][4];
	//~ char b[4][4]={{'a','b','c','d'},{'A','B','C','D'},{'m','n','o','p'},{'D','E','F','G'}};
	//~ int i,j ;
	//~ for ( i = 0 ; i < 4 ; i++){
		//~ for ( j = 0 ; j < 4 ; j++){
			//~ a[i][j] =  b[i][j];
		//~ }
	//~ }
	
	//~ int a;
	//~ for ( a= 0 ; a<10;a++){
		   //~ if ( a == 3 ) {
			   //~ continue;
			   //~ }
			//~ if ( a == 5 ) {
				//~ break ;
				//~ }
			   
		//~ }
	
	//~ int f();
//~ int i = 0;
	//~ switch ( i ) {
		//~ case 0:
		//~ {int a = 0;}
			//~ break;
		//~ case 1:
		//~ {int b = 0;}
		//~ break;
		//~ default:
			//~ break;
		
		//~ }
	//~ if( i > 1) {
				  //~ int a = 0;

		//~ } else 
		//~ {
							  //~ int b = 0;

		//~ }
		return 0 ;
}

//~ int f(){
	//~ return 0;
	//~ }

	//~ call	__alloca
	//~ call	___main
	//~ movl	$4, -4(%ebp)
	//~ movl	$0, %eax

//~ 由于sizeof 是关键字，而非函数，所以汇编直接给出的是立即数，没有函数调用。
//~ 关键字是由编译器处理的。

int caller(){
	int a = 1,b=2,c=3;
	bycall(a,b,c);
	return 0;
	}
	
int bycall(int a,int b , int c){
 return a+b+c;	
}

int recusive(int n){
	if ( 1 ==  n )
		return 1;
	else 
		return recusive( n -1 ) * n;
}

int dead_recusive(int a){
			printf("%p\n",&a);
			dead_recusive(a);
	return 0;
	}
