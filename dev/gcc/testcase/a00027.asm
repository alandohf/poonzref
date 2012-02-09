;test dd
assume cs:scode
d segment
dd 'AB'
dw 'AB'
db 'AB'
d ends

d1 segment
dd 'ABCD'
d1 ends

d2 segment
dw 'AB'
d2 ends

d3 segment
db 'ABC'
d3 ends


scode segment
start:
	;return
		mov ax,4c00h
		int 21h
	scode ends
end start
