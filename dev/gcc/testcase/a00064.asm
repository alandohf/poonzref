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
	;db 'abcdefghijklmnop',0
	;mov ax,0
	;mov es,ax
	;mov di,200h   这种方法不行！
	;push cx
	push di
	;push es  ?? 为什么加了压栈语句程序卡死了？ 写在了upper: 里面！
	push cx
	
upper:
	;push es  ?? 为什么加了压栈语句程序卡死了？ 写在了upper: 里面！
	;如何决定要push 哪些寄存器？看下面的代码中哪些可能被修改！！
	mov cl,es:[di]
	mov ch,0
	jcxz irt 
	and cl,11011111b
	mov es:[di],cl
	inc di
	jmp upper

irt:
	;pop es
	pop di
	pop cx
	iret
	
;mov ax,4c00h
;int 21h
		
end_toupper:
			nop
			
code ends
end start
