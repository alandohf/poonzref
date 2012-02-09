assume cs:code



data segment
db 8,11,8,1,8,5,63,38
data ends


edata segment
db 8 dup(0)
edata ends

code segment
start:
		mov bx,data
		mov ds,bx
		mov bx,edata
		mov es,bx
		
		mov si,0
		mov di,0
	    mov cx,8
		rep movsb 
		
retp:
		mov ax,4c00h
		int 21h

code ends
end start
