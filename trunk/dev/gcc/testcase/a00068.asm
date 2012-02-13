assume cs:code

code segment
start:
		;shl 01010100h,3
		mov al,01010100b
		mov cl,3
		shl al,cl
		
	
mov ax,4c00h
int 21h
			
code ends
end start
