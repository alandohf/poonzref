;purpose:��a��ǰ8���������b
;Ϊʲô�ȶ���a��ʱ,�ڴ�a�ε����ݲ�һ�£�
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
