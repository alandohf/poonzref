;ȡ��cmos ram �е�bcd���� �� ��ת���ɿ���ʾ��10������ʽ��
assume cs:code

code segment
start:
		mov al,8
		out 70h,al ;��˿�д���ַ
		
		in al ,71h ;�Ӷ˿ڻ�ȡ����
		
		mov ah,al
		mov cl,4
		shr ah,cl	;ȡ�·ݵ�10λ
		and al,00001111b ;ȡ�·ݵĸ�λ
		add al,30h
		add ah,30h

		
	
mov ax,4c00h
int 21h
			
code ends
end start
