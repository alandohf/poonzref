assume cs:scode

scode segment
start:
;除数为8位时
mov ax,7fh
mov bl,3h
;result: ah=01h ; al=2ah ;2a*3h+01 = 7f 
;div bl
div byte ptr bl;the same
;除数为16位时
mov ax,07ffh
mov dx,0100h
mov bx,7ffh;2047d
;div bx
div word ptr bx;the same
;result:ax=2005h;dx=0004h ; 2005h*7ffh+0004h=010007ffh
	;return
		mov ax,4c00h
		int 21h
	scode ends
end start
;16779259
;dxax:16779263