;error A2030: multiple index registers not allowed
;����ѭ�� ��ôд�� cx?
assume cs:scode

data segment
db 'abcdefgh'
db '54321'
data ends


x segment
db 'xxxxxx'
x ends



scode segment
start:
	;return
		mov ax,4c00h
		int 21h
	scode ends
end start
