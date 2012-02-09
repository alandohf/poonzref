;test dd
assume cs:scode
d segment
dd 100001
dw 100
dw 0
d ends

scode segment
start:
	mov ax,d
	mov ds,ax
	mov bx,0
	mov ax,0[bx]
	mov dx,2[bx]
	mov cx,4[bx]
	div cx
	mov 6[bx],ax
;return
		mov ax,4c00h
		int 21h
	scode ends
end start
