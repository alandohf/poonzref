;purpose:将a段前8字逆序存入b
;为什么先定义a段时,内存a段的数据不一致？
assume cs:scode
a segment 
db 'uNiX'
a ends 
scode segment
start:
	mov al,'u'
	;return
		mov ax,4c00h
		int 21h
	scode ends
end start
;d cs-1:0
