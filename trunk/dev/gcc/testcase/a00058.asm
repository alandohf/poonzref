assume cs:code



data segment
db 'Welcome to masm!'
db 16 dup(0)
data ends


edata segment
db 8 dup(0)
edata ends

code segment
start:
		mov bx,data
		mov ds,bx
		add bx,1
		mov es,bx
		
		mov si,0
		mov di,0
	    mov cx,16
		cld
		rep movsb 
		
retp:
		mov ax,4c00h
		int 21h

code ends
end start
