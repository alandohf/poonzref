;1.先保存call下一条指令的地址
;2.call的偏移量=标号处地址-call后第一个字节地址
;指令eb0100 eb为操作符，0100 是地址 01 是低位，00 是高位 ， 即0001h
assume cs:code

code segment
start:
		mov ax,0
		call s
		inc ax
		s:pop ax
		mov ax,4c00h
		int 21h
code ends
end start
