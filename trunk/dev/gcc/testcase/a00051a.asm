;�����������
;Divide error
assume cs:code

stack segment
dw 8 dup(0)
stack ends

code segment
start:
		mov ax,stack
		mov ss,ax
		mov sp,0010h
		mov ax,4240h
		mov cl,2h
		mov ch,0
		call div8
		call retp
div8:
	   ;push dx ;save ������ �ĸߵ�λ
	   mov bl,al  ;ȡ�õ�λ
	   mov bh,0
	   push bx	   ;�����λ
	   mov al,ah
	   mov ah,0
	   ;mov ax,bx ;��λ��������
	   div cl ;get int(h/n) & rem(h/n)
	   ;al Ϊ�� ah Ϊ���� �����̵�ջ����Ϊ���������ĸ�λ����������һ�γ����ĸ�λ
	   pop bx ;�ѵ�λȡ����
	   mov dl,al ;��������
	   mov dh,0
	   push dx
	   mov al,bl ;�ѵ�λ��ax�ĵ�λ
	   div cl
	   mov  cl,ah;dx��λ��ax��λ��cx����
	   mov ch,0
	   pop bx
	   mov ah,bl
	   mov dx,0
	   ret
retp:
		mov ax,4c00h
		int 21h

code ends
end start


