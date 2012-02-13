;check point 13.2
;procedure
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
		;dec cx　　　　; jmp 不同于loop，不需要循环因子
		;jcxz lpret ; jmp 不同于loop，不需要循环因子　，i make it ! yeah!
		add [bp+2],bx
lpret:
		pop bp
		iret ;注意iret 和 int 是成对执行的，执行了一个int，就要对应执行一个iret!
		
;mov ax,4c00h
;int 21h
		
end_toupper:
			nop
			
code ends
end start
