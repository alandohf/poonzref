;fishc 实验7
;1.如何一次性向内存写入多于一个字的值
;2.ds,ss,es的安排有技巧！
assume cs:scode

stack segment
dw 'a','b','c','d','0','0','0','0'
stack ends
scode segment
start:
		mov ax,stack
		mov ss,ax
		push ax
		;return
		mov ax,4c00h
		int 21h
	scode ends
end start
