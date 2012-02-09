;9.3
;本题要注意,cx先自减1！！如果cx=1,则只执行一次！！,当执行到loop s 时，根据cx决定 s的内容是否执行.
;如果cx=0，那么s的内容也执行，并且在loop s前先减1，那么cx将永远小于1，执行到cx越界为止
;即在loop s 前，总要先判断cx是否为0！
assume cs:code
stack segment
db 0ffffh dup(0)
stack ends

code segment
start:
       mov cx,0
	   s: 
	   mov ax,cx
	   add ax,1
	   push ax
	   loop s

		mov ax,4c00h
		int 21h
code ends
end start
