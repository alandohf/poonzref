;除法溢出问题
;Divide error
assume cs:code

stack segment
dw 8 dup(0)
stack ends

code segment
start:
		mov ax,stack
		mov ss,ax
		mov sp,0010h
		mov ax,4240h
		mov cl,2h
		mov ch,0
		call div8
		call retp
div8:
	   ;push dx ;save 被除数 的高低位
	   mov bl,al  ;取得低位
	   mov bh,0
	   push bx	   ;保存低位
	   mov al,ah
	   mov ah,0
	   ;mov ax,bx ;高位做被除数
	   div cl ;get int(h/n) & rem(h/n)
	   ;al 为商 ah 为余数 保存商到栈，作为整个商数的高位；余数作下一次除法的高位
	   pop bx ;把低位取出来
	   mov dl,al ;保存商数
	   mov dh,0
	   push dx
	   mov al,bl ;把低位做ax的低位
	   div cl
	   mov  cl,ah;dx高位，ax低位，cx余数
	   mov ch,0
	   pop bx
	   mov ah,bl
	   mov dx,0
	   ret
retp:
		mov ax,4c00h
		int 21h

code ends
end start


