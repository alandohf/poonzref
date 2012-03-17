;the source file for code test
;cf 对于无符号数才有意义
;of 对于符号数才有意义
assume cs:code,ds:data

data segment
dw 'AB'
data ends

code segment
start:
		;mov ax,00020h
		; mov cx,00002h
		;div cx
		
		;mov ax,1234h
		;mov al,ah
		; nop
		; 进位
		;mov al,98h
		;add al,al
		;借位
		;mov al,97h
		;mov bl,98h
		;sub al,bl ;al - bl -> al
		; sub bl,al ; bl - al -> bl
		;test overflow 1
		; mov al,10001000b
		; mov bl,11110000b
		; add al,bl
		;test overflow 2
		; mov al,01100010b
		; add al,01100011b

		; mov al,98h ;这种写法AX=0098h;可以理解为无符号的152d;如果是有符号，则可以理解为-104d。
		; mov bl,98h
		; add al,bl
				; !!!!!既可以看作为无符号的进位，也可以理解为有符号（负数）的溢出

		; mov al,78h ;对比98h，78h = 120d ，没有超出127d,所以默认al作为*有符号*来存储，做加法时，就会溢出，而不是进位。
		; mov bl,78h
		; add al,bl
		;test default flag bits values
		;pushf
		
		; test divide overflow
		;mov ax,1000h
		;mov bl,1h
		;div bl
		
		;test int 
		; mov ax,0b800h
		; mov es,ax
		; mov byte ptr es:[12*160+40*2],'!'
		
		;int 0
		
		;test int 7ch a00064
		;int 7ch
		;test assume ds:data
		; mov ax,data
		; mov ds,ax
		mov ax,ds:[0]
		
		
retp:
		mov ax,4c00h
		int 21h

code ends
end start

