;purpose:将a段前8字逆序存入b
;为什么先定义a段时,内存a段的数据不一致？
assume cs:scode


b segment
	dw 0,0,0,0,0,0,0,0
b ends

a segment
	dw 01h,02h,03h,04h,05h,06h,07h,08h,0ah,0bh,0ch,0dh,0eh,0fh
a ends


scode segment
	startp:
	;init
		mov bx,0
		mov cx,8
	;set ds
		mov ax,a
		mov ds,ax
	;set ss
		mov ax,b
		mov ss,ax
		mov sp,16
	;move data
	s:
		push ds:[bx]
		add bx,2
		loop s
	;return
		mov ax,4c00h
		int 21h
	scode ends
end startp
