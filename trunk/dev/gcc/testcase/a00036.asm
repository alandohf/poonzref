;9.1
;注意判断对象时字节，不是字
assume cs:scode

data segment
data ends

scode segment
start:
mov ax,0b5bh
mov ds,ax
mov bx,40h
s:
mov cx,0
mov cl,[bx]
jcxz ok
inc bx

jmp short s 
ok:
mov dx,bx

;return
		mov ax,4c00h
		int 21h
	scode ends
end start
