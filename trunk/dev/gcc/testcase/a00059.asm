assume cs:code



data segment
;db 'Welcome to masm!'
db 16 dup(0)
data ends


code segment
start:
		mov bx,0ffffh
		mov ds,bx
		add bx,data
		mov es,bx
		
		mov si,0
		mov di,0
	    mov cx,16
		cld
		rep movsb 
		mov bx,data
		mov es,bx
		mov bx,0f000h
		mov ds,bx
		mov si,0ffffh
		mov di,0fh
		mov cx,16
		std
		rep movsb
retp:
		mov ax,4c00h
		int 21h

code ends
end start
