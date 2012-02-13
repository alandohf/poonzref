//~ *全局变量 
        //~ 在.data,.data?.const段申明的变量并且可以在程序的任何地方访问。称为全局变量。在汇编语言中变量没有类型限制。 
//~ 他只是一块开辟出来的内存。.const段是常量变量。他和变量一样在内存中申请一块空间。他们的区别就是.const段的内存不 
//~ 允许修改。 

static int s = 9;
int main(void){
static int i = 3;
	i++;
static int j = 4;
	
return s+i+j;
}

 //~ .comm           声明为未初始化的通用内存区域
    //~ .lcomm          声明为未初始化的本地内存区域
//~ .lcomm i.0,16

	//~ incl	i.0
	//~ movl	i.0, %eax

//~ static int i = 3;
//~ static int j = 4;
//~ 是这样定义的：放在全局变量区，尽管他是在main 中声明定义。
//~ i.0:
	//~ .long	3
	//~ .align 4
//~ j.1:
	//~ .long	4
	//~ .text


//~ 当static int i 初始化为0时，指令如下：
//~ .lcomm i.0,16

//~ .lcomm name, size, alignment
//~ The .lcomm directive allocates storage in the .bss section. The storage is referenced by the symbol name, and has a size of size bytes. Name cannot be predefined, and size must be a positive integer. If alignment is specified, the address of name is aligned to a multiple of alignment bytes. If alignment is not specified, the default alignment is 4 bytes.
	
