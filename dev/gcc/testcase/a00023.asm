;error A2030: multiple index registers not allowed
;多重循环 怎么写？ cx?
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
