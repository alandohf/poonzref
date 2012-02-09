stack segment
dw 'a','b','c','d','0','0','0','0'
stack ends
scode segment
start:
mov ax,0
mov bx,0
jmp far ptr s
db 256 dup (0)
s:add ax,1
  inc ax
;return
		mov ax,4c00h
		int 21h
	scode ends
end start
