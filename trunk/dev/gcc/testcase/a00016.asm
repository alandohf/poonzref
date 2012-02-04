;将数据入栈
;声明栈空间
;purpose:翻转字存放的顺序;利用栈和数据段结构

assume cs:scode

a segment
	dw 1,2,3,4,5,6,7,8
a ends

b segment
	dw 8,7,6,5,4,3,2,1
b ends

d segment
	dw 0,0,0,0,0,0,0,0
d ends

scode segment
startp:

;init
	mov bx,0
	mov cx,8
;set ds
	mov ax,a
	mov ds,ax
;set es
	mov ax,d
	mov es,ax
;move data
s:
	mov ax,ds:[bx]
	mov es:[bx],ax
	add bx,2
	loop s
;init
	mov bx,0
	mov cx,8
;set ds
	mov ax,b
	mov ds,ax
;do add operation
s2:
	mov ax,ds:[bx]
	add es:[bx],ax
	add bx,2
	loop s2

	mov ax,4c00h
	int 21h
scode ends
end startp
