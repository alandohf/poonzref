;fishc ʵ��7
;1.���һ�������ڴ�д�����һ���ֵ�ֵ
;2.ds,ss,es�İ����м��ɣ�
assume cs:scode

stack segment
dw 'a','b','c','d','0','0','0','0'
stack ends
scode segment
start:
		mov ax,stack
		mov ss,ax
		push ax
		;return
		mov ax,4c00h
		int 21h
	scode ends
end start
