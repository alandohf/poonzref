;实验10-2; 小甲鱼实现
assume cs:code

data segment
db 'This is a show string program',0
data ends

code segment
start:
		mov dh,8
		mov dl,8
		mov cl,2
		
		mov ax,data
		mov ds,ax
		mov si,0
		
		call show_str
		mov ax,4c00h
		int 21h
show_str:
	
		push cx
		push si
		mov al,0a0h
		dec dh
		mul dh
		mov bx,ax
		mov al,2
		mul dl
		sub ax,2
		add bx,ax
		mov ax,0b800h
		mov es,ax
		mov di,0
		mov al,cl
		mov ch,0
s:	    mov cl,ds:[si]
		jcxz ok
		mov es:[bx+di],cl
		mov es:[bx+di+1],al
		inc si
		add di,2
		jmp short s
ok : pop si
	 pop cx
	 ret 
code ends
end start
