;1.�ȱ���call��һ��ָ��ĵ�ַ
;2.call��ƫ����=��Ŵ���ַ-call���һ���ֽڵ�ַ
;ָ��eb0100 ebΪ��������0100 �ǵ�ַ 01 �ǵ�λ��00 �Ǹ�λ �� ��0001h
assume cs:code

code segment
start:
		mov ax,0
		call s
		inc ax
		s:pop ax
		mov ax,4c00h
		int 21h
code ends
end start
