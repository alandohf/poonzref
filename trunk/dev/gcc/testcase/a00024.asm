;error A2030: multiple index registers not allowed
;多重循环 怎么写？ cx?
assume cs:scode

data segment
db '1. display......'
db '2. browser......'
db '3. replace......'
db '4. modify.......'
data ends

scode segment
start:
mov ax,data
mov ds,ax
mov bx,0
mov cx,4
loopout:
push cx
mov cx,4
mov si,0
loopin:
mov dl,3[bx+si]
and dl,11011111b
mov 3[bx+si],dl
inc si
loop loopin
pop cx
add bx,10h
loop loopout
	;return
		mov ax,4c00h
		int 21h
	scode ends
end start
