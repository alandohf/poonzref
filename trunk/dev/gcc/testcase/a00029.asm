;test dd
assume cs:scode
d segment
dd 8 dup(41h)
dw 16 dup(42h)
db 32 dup(43h)
db 16 dup('a','B') ;16*length(db)*2
dw 8 dup('A','B') ;8*length(dw)*2
dw 8 dup('pA','pB');8*length(dw)*2
db '1999'
d ends

scode segment
start:
	
;return
		mov ax,4c00h
		int 21h
	scode ends
end start
