assume cs:scode
data segment 
db 'welcome to masm!'
db '................'
data ends 
scode segment
start:
	mov ax,data
	mov ds,ax
	mov si,0
	mov di,16
	mov cx,8
s:	
	 mov ax,[si]
	 mov [di],ax
	 add si,2
	 add di,2
	 loop s
	;return
		mov ax,4c00h
		int 21h
	scode ends
end start
