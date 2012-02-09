;;;a00039.asm(4) : error A2075: jump destination too far : by 1 byte(s)
assume cs:code
code segment
start:
		jmp short s
		;db 128 dup(0)
		db 127 dup(0)
       s:
		mov ax,4c00h
		int 21h
code ends
end start
