;purpose:��a��ǰ8���������b
;Ϊʲô�ȶ���a��ʱ,�ڴ�a�ε����ݲ�һ�£�
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
