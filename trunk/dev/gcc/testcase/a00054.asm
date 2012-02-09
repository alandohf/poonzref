assume cs:code

stack segment
dw 32 dup(0)
stack ends


data segment
db 16 dup(0)
data ends


code segment
start:
		mov bx,01000h
		mov ax,021eh
		cmp ah,bh
		jne s
		add ah,ah
		jmp short ok
		ret
	s:  add ah,bh
	ok:
		ret
		
retp:
		mov ax,4c00h
		int 21h

code ends
end start
