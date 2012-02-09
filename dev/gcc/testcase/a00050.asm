;除法溢出问题
;Divide error
assume cs:code

data segment
db 'This is a show string program',0
data ends

code segment
start:
		;mov ax,1000
		;mov bl,1
		;div bl
		
		;16bit
		mov ax,1000h
		mov dx,1
		mov bx,1
		div bx
retp:		
		mov ax,4c00h
		int 21h

code ends
end start
