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
		
		mov ax,0abch
		mov dx,0000h
		mov cx,0ah
		call divdw
		call retp
divdw:
;����Ϊ16λ��������Ϊ32λ�ķ��������
;���룺ax ��������cl ����
;�����ax �̵�λ,dx �̸�λ;cx ���� 

;push dx ;save ������ �ĸߵ�λ
	   push ax	   ;��Ϊ�����ĸ�λ
	   mov ax,dx
	   mov dx,0
	   div cx ;get int(h/n) & rem(h/n)
	   pop bx ;�ѵ�λȡ����
	   push ax ;��;����dxֱ�����´γ����ĸ�λ
	   ;mov dx,dx ;��������λ rem(h/n)*10000h
	   mov ax,bx   ;ȡ����λ,ֱ�ӷ���ax����λ
	   div cx
	   mov cx,dx;��������
	   pop dx ;�ָ������ĸ�λ��dx
	   ret
retp:
		mov ax,4c00h
		int 21h

code ends
end start


