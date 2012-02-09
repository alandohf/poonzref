;9.1
assume cs:scode

data segment
;db 0,0
dw 0
data ends

scode segment
start:
mov ax,data
mov ds,ax
mov bx,0
jmp word ptr [bx+1]
;return
		mov ax,4c00h
		int 21h
	scode ends
end start
