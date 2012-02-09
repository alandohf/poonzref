;1000001/100
;1001/100
assume cs:scode

scode segment
start:
mov ax,86a1h
mov dx,1
mov bx,0064h
div word ptr bx;
mov ax,1001
mov bl,100
div bl
	;return
		mov ax,4c00h
		int 21h
	scode ends
end start
