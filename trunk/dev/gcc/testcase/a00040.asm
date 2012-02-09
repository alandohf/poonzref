;此例考察对jmp 的机器码的特点的了解！
;偏移=要跳转到的偏移地址-jmp的下一条指令地址
;so: f6h=-9 = 0 -09h
assume cs:code
code segment
		mov ax,4c00h
		int 21h
start:
		mov ax,0
	s:  nop
		nop 
		
		mov di,offset s 
		mov si,offset s2
		mov ax,cs:[si]
		mov cs:[di],ax; s2 -> s
	s0:
		jmp short s
	s1:
		mov ax,0
		int 21h
		mov ax,0
	s2:
		jmp short s1
		nop
code ends
end start
