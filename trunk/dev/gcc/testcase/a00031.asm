;fishc 实验7
;1.如何一次性向内存写入多于一个字的值
;2.ds,ss,es的安排有技巧！
assume cs:scode

scode segment
start:

mov ax,0123
mov ax,ds:[0123]
push ds:[0123]

mov ax,0
jmp s
add ax,1
add ax,1
add ax,1
s: inc ax
		;return
		mov ax,4c00h
		int 21h
	scode ends
end start
