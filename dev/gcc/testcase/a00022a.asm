;error A2030: multiple index registers not allowed
;����ѭ�� ��ôд�� cx? ��ѭ���޷��˳�������
;ͨ��ջ������� push - pop!! ���߶���ļĴ��������棻�����ڴ棨ջ���ڴ�Σ�
;����ջ��ѣ�������˼Ĵ�����������⣡��
assume cs:scode

scode segment
start:
	mov ax,0e00h
	mov ds,ax
;outsize loop init 
mov dx,0
mov bx,0
mov cx,16
oloop:	
;insize loop init 	 
	push cx
	mov cx,16
	mov si,0
	iloop:
			mov [si+bx],dx	;si indice column
			inc si
	loop iloop
add bx,10h
pop cx
loop oloop

;return
mov ax,4c00h
int 21h
	scode ends
end start
