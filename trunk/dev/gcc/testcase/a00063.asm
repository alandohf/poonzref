;int 7ch
assume cs:code

code segment
start:
	
	mov ax,cs
	mov ds,ax
	mov ax,0
	mov es,ax
	mov si ,offset cal_sqr
	mov di,0200h
	mov cx , offset end_cal_sqr - offset cal_sqr
	cld ; 别漏了
	rep movsb ;rep , not dup
	
	;setup
	mov ax,0
	mov es,ax
	mov word ptr es:[7ch*4],200h ;int 7ch ; 注意是word ptr!!!
	mov word ptr es:2[7ch*4],0 ; h 是必须的，就算带c
	
mov ax,4c00h
int 21h
		
cal_sqr:

	mul ax
	iret ; 
mov ax,4c00h
int 21h
		
end_cal_sqr:
			nop
			
code ends
end start
