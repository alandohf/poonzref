;purpose:将a段前8字逆序存入b
;为什么先定义a段时,内存a段的数据不一致？
assume cs:scode
scode segment
	mov al,11110000b
	and al,00111111b
	or  al,11110000b
	;return
		mov ax,4c00h
		int 21h
	scode ends
end 
