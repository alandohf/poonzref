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
	cld ; ��©��
	rep movsb ;rep , not dup
	
	;setup
	mov ax,0
	mov es,ax
	mov word ptr es:[7ch*4],200h ;int 7ch ; ע����word ptr!!!
	mov word ptr es:2[7ch*4],0 ; h �Ǳ���ģ������c
	
mov ax,4c00h
int 21h
		
toupper:
	;db 'abcdefghijklmnop',0
	;mov ax,0
	;mov es,ax
	;mov di,200h   ���ַ������У�
	;push cx
	push di
	;push es  ?? Ϊʲô����ѹջ���������ˣ� д����upper: ���棡
	push cx
	
upper:
	;push es  ?? Ϊʲô����ѹջ���������ˣ� д����upper: ���棡
	;��ξ���Ҫpush ��Щ�Ĵ�����������Ĵ�������Щ���ܱ��޸ģ���
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
