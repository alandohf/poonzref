assume cs:code

stack segment
dw 32 dup(0)
stack ends


data segment
db 16 dup(0)
data ends


code segment
start:
		mov bx,0f000h
		mov ax,001eh
		mov dx,0020h
		mov cx,1000h
		add bx,cx
		adc ax,dx
		
		
retp:
		mov ax,4c00h
		int 21h

code ends
end start
