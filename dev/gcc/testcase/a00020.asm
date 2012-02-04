;db 'uNiX' 不可改写？可以！
assume cs:scode
a segment 
db 'uNiX'
a ends 
b segment 
db '0000'
b ends 
scode segment
start:
	mov bx,0
	mov cx,4
	mov ax,a
	mov ds,ax
	mov ax,b
	mov es,ax
s:	
	 mov al,ds:[bx]
	 and al,11011111b;to upper case
	 ;or al,00100000b;to lower case
	 ;and al,1011b
	 mov es:[bx],al
	 inc bx
	 loop s
	;return
		mov ax,4c00h
		int 21h
	scode ends
end start
