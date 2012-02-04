;1.end [tag] 标签要放在程序最后，tag所标的位置可以再end前的任何一个段定义中。
;2.如果只有end，没有[tag],段的位置安排不会影响程序的编译，但是执行顺序就会按编写的顺序来。所以在没有指明入口时，要把代码段放前面。
;3.没有end的程序是错误的
;4.接2，先定义的短占据低地址，后定义的占据高地址。这种分配方式证明了2点.
assume cs:code,ds:data,ss:stack


code segment

	mov ax,stack
	mov ss,ax
	mov ax,data
	mov ds,ax
	mov sp,16
	;
	mov bx,0
	mov cx,8
	s1:
	push [bx]
	add bx,2
	loop s1
	;
	mov bx,0
	mov cx,8
	s2:
	pop [bx]
	add bx,2
	loop s2


	mov ax,4c00h
	int 21h
code ends




data segment
	dw 1200h,5634h,9A78h,0debch,0dcfeh,98bah,5476h,1032h
data ends


stack segment
	dw 0,0,0,0,0,0,0,0
stack ends




end 
