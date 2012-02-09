;100*10
;100*10000
assume cs:code

code segment
start:
		mov al,100
		mov bl,10
		mul bl
		;
		mov ax,10000
		mov bx,100
		mul bx
		mov ax,4c00h
		int 21h
code ends
end start
