;int 7ch
assume cs:code

data segment
db 'abcdefghijklmnop',0
data ends


code segment
start:
	mov ax,data
	mov es,ax
	mov di,0
	int 7ch

mov ax,4c00h
int 21h
		
code ends
end start
