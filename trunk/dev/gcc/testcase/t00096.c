//~ *ȫ�ֱ��� 
        //~ ��.data,.data?.const�������ı������ҿ����ڳ�����κεط����ʡ���Ϊȫ�ֱ������ڻ�������б���û���������ơ� 
//~ ��ֻ��һ�鿪�ٳ������ڴ档.const���ǳ������������ͱ���һ�����ڴ�������һ��ռ䡣���ǵ��������.const�ε��ڴ治 
//~ �����޸ġ� 

static int s = 9;
int main(void){
static int i = 3;
	i++;
static int j = 4;
	
return s+i+j;
}

 //~ .comm           ����Ϊδ��ʼ����ͨ���ڴ�����
    //~ .lcomm          ����Ϊδ��ʼ���ı����ڴ�����
//~ .lcomm i.0,16

	//~ incl	i.0
	//~ movl	i.0, %eax

//~ static int i = 3;
//~ static int j = 4;
//~ ����������ģ�����ȫ�ֱ�����������������main ���������塣
//~ i.0:
	//~ .long	3
	//~ .align 4
//~ j.1:
	//~ .long	4
	//~ .text


//~ ��static int i ��ʼ��Ϊ0ʱ��ָ�����£�
//~ .lcomm i.0,16

//~ .lcomm name, size, alignment
//~ The .lcomm directive allocates storage in the .bss section. The storage is referenced by the symbol name, and has a size of size bytes. Name cannot be predefined, and size must be a positive integer. If alignment is specified, the address of name is aligned to a multiple of alignment bytes. If alignment is not specified, the default alignment is 4 bytes.
	
