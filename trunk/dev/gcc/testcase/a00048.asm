;100*10
;100*10000
;使用内存操作，不使用栈
assume cs:code

data segment
dw 1 ,2 ,3 ,4 ,5, 6 ,7 ,8
dw 8 dup(0)
data ends

code segment
start:
		mov ax,data
		mov ds,ax
		add ax,1
		;mov ss,ax
		;mov sp,16
		mov cx,8
		mov bx,0
	lp:
		mov dl,ds:[bx]
		call s
		mov ds:16[bx],ax
		add bx,2
		;push ax
		loop lp
		;return
		mov ax,4c00h
		int 21h
	s:
		mov al,dl
		mul dl
		mul dl
		ret
code ends
end start
