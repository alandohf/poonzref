;视频提供代码：有bug，死循环
assume cs:code

stack segment
db 8,11,8,1,8,5,63,38
stack ends


data segment
db 8,11,8,1,8,5,63,38
data ends


code segment
start:
		mov bx,data
		mov ds,bx
		mov bx,0
		mov ax,0
		mov cx,0
	s:
		cmp byte ptr [bx],8
		jne next
		inc ax
    next:
		inc bx
		loop s
retp:
		mov ax,4c00h
		int 21h

code ends
end start
