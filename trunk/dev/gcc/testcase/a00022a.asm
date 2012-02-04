;error A2030: multiple index registers not allowed
;多重循环 怎么写？ cx? 外循环无法退出！！！
;通过栈来解决！ push - pop!! 或者额外的寄存器来保存；或者内存（栈；内存段）
;而用栈最佳，他解决了寄存器不足的问题！！
assume cs:scode

scode segment
start:
	mov ax,0e00h
	mov ds,ax
;outsize loop init 
mov dx,0
mov bx,0
mov cx,16
oloop:	
;insize loop init 	 
	push cx
	mov cx,16
	mov si,0
	iloop:
			mov [si+bx],dx	;si indice column
			inc si
	loop iloop
add bx,10h
pop cx
loop oloop

;return
mov ax,4c00h
int 21h
	scode ends
end start
