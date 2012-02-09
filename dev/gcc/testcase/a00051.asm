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
		
		mov ax,0abch
		mov dx,0000h
		mov cx,0ah
		call divdw
		call retp
divdw:
;除数为16位，被除数为32位的防溢出除法
;输入：ax 被除数，cl 除数
;输出：ax 商低位,dx 商高位;cx 余数 

;push dx ;save 被除数 的高低位
	   push ax	   ;作为商数的高位
	   mov ax,dx
	   mov dx,0
	   div cx ;get int(h/n) & rem(h/n)
	   pop bx ;把低位取出来
	   push ax ;商;余数dx直接做下次除法的高位
	   ;mov dx,dx ;余数作高位 rem(h/n)*10000h
	   mov ax,bx   ;取出低位,直接放在ax做低位
	   div cx
	   mov cx,dx;保存余数
	   pop dx ;恢复商数的高位到dx
	   ret
retp:
		mov ax,4c00h
		int 21h

code ends
end start


