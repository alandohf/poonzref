;fishc ʵ��7
;1.���һ�������ڴ�д�����һ���ֵ�ֵ
;2.ds,ss,es�İ����м��ɣ�
assume cs:scode

scode segment
start:

mov ax,0123
mov ax,ds:[0123]
push ds:[0123]

mov ax,0
jmp s
add ax,1
add ax,1
add ax,1
s: inc ax
		;return
		mov ax,4c00h
		int 21h
	scode ends
end start
