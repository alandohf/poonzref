;db 'uNiX' ²»¿É¸ÄÐ´£¿
assume cs:scode
a segment 
db 'uNiX'
a ends 
scode segment
start:
	mov bx,0
	mov cx,4
	mov ax,a
	mov ds,ax
s:	
	 mov al,ds:[bx]
	 and al,11011111b;to upper case
	 ;or al,00100000b;to lower case
	 ;and al,1011b
	 mov ds:[bx],al
	 inc bx
	 loop s
	;return
		mov ax,4c00h
		int 21h
	scode ends
end start
