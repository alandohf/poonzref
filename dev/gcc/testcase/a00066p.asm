; 1.SP和BP默认是SS是硬件结构决定的，所有的段跨越前缀，都是要耗时的。
; 2.要先知道堆栈的大小才能计算。SS指向的是堆栈段的起始地址，而不是堆栈的地址，用它加上堆栈的容量就得出栈底的位置，
;然后再减去堆栈中数据的个数，就得出SP的位置了。
; BP主要在编写子程序时才用。因为子程序中经常使用局部变量，而局部变量的空间是在堆栈上申请的，
;这时就先让BP=SP，然后每定义一个局部变量，就把它压入堆栈。等子程序结束时，
;只要简单地一句mov sp,bp就可以从堆栈找到原先的返回地址，同时也归还了局部变量所占的空间。然后用ret指令，顺利返回。 
;!!!!!

;int 7ch
assume cs:code

code segment
start:
	
	mov ax,cs
	mov ds,ax
	mov ax,0
	mov es,ax
	mov si ,offset toupper
	mov di,0200h
	mov cx , offset end_toupper - offset toupper
	cld ; 别漏了
	rep movsb ;rep , not dup
	
	;setup
	mov ax,0
	mov es,ax
	mov word ptr es:[7ch*4],200h ;int 7ch ; 注意是word ptr!!!
	mov word ptr es:2[7ch*4],0 ; h 是必须的，就算带c
	
mov ax,4c00h
int 21h
		
toupper:
	
		push bp
		mov bp,sp
		dec cx
		jcxz lpret
		add [bp+2],bx
lpret:
		pop bp
		iret
		
;mov ax,4c00h
;int 21h
		
end_toupper:
			nop
			
code ends
end start
