;����ֵ���ַ���ʾ
assume cs:code

stack segment
dw 32 dup(0)
stack ends


data segment
db 16 dup(0)
data ends


code segment
start:
		mov ax,stack
		mov ss,ax
		mov sp,0040h
		mov ax,12345 ;317A; 317a/0a = 4f2 ~ 6
		mov bx,data
		mov ds,bx
		mov si,0
		mov di,0
		
		push si
		
		call d2c
        ;nop

revert_str:	
;ת���ɿɴ�ӡ�ַ�����ջ
			pop si
			inc di
			mov cx,di
	revert_push:
			mov dx,ds:[si]
			add dx,30h
			push dx
			inc si
			loop revert_push
			
			mov cx,di
			mov si,0
	revert_pop:
			pop dx
			mov ds:[si],dl
			inc si
			loop revert_pop
	add0:
	mov dl,0
	mov ds:[si],dl
;;; rev_push:
;;;   mov cl,ds:[si]
;;;   mov ch,0
;;;   jcxz next
;;;   add cx,30h
;;;   push cx
;;;   inc si
;;;   jmp short rev_push
;;; 
;;; next:
;;;   mov si,0
;;; rev_pop:
;;;	   pop cx
;;;		 jcxz retp  
;;;	   mov ds:[si],cx
;;;	   inc si
;;;	   jmp short rev_pop
;;; 
 ; ����show_str		
 call_showstr:
 		mov ax,data
 		mov ds,ax
 		mov dh,7  ;row index
 		mov dl,2  ;col index
 		mov cl,0cah  ;color value
 		mov si,0  ;data adress index
 		call show_str

call retp
;########################################################################################
d2c:
;���ܣ���һ������������
;���:1.������д���ڴ�;����di,Ϊ���һ��������ƫ�Ƶ�ַ��di+1 Ϊ�����ĸ���
;
		mov cx,000ah ;���ó���
		;mov ch,0		
		call divdw;ax ��;cx����
		mov dx,cx
		mov cx,ax
		jcxz d2cret
		mov ds:[di],dl ;��������;��ֻ�����жϣ����ñ���
		mov dx,0
		add di,1
		jmp d2c
d2cret: 
		mov ds:[di],dl ;��������;��ֻ�����жϣ����ñ���
		ret ;d2c
		
divdw:
	   push ax	   ;��Ϊ�����ĸ�λ
	   mov ax,dx
	   mov dx,0
	   div cx ;get int(h/n) & rem(h/n)
	   pop bx ;�ѵ�λȡ����
	   push ax ;��;����dxֱ�����´γ����ĸ�λ
	   mov ax,bx   ;ȡ����λ,ֱ�ӷ���ax����λ
	   div cx
	   mov cx,dx;��������
	   pop dx ;�ָ������ĸ�λ��dx
	   ret ;divdw return


show_str:
;����:��ӡdata���ַ������ض����к���ɫ��
;����:dh ��;dl ��;cl ��ɫ��ds:si �����׵�ַ
		;��ʼ��
		;��������:����rowֵ������ʼ�ε�ַ
		mov al,0ah ;0a0 = 160/16
		mov ah,0
		mov bl,dh
		mul bl
		add ax,0b800h
		mov es,ax
		;mov bx,0 ;ʹ��si
		;mov di,0
		;��������:��colת����ƫ����������di��ֵ
		mov al,dl
		mov ah,0
		mov bl,2
		mul bl
		mov di,ax ;����������ʼ��di��di�����Դ�ƫ��
		;��������:��ɫ����
		mov al,cl  ;������ɫ
		mov ah,0
		;��������:�����׵�ַ
		;and si,ffffh
	writestr:
		;��ȡ�ִ�д���Դ�
		mov cl,ds:[si];��ȡ
		mov ch,0
		jcxz show_str_ret
		mov es:[di],cl ;д��
		;mov ax,0cah
		mov es:1[di],ax
		add di,2
		inc si
		jmp short writestr
	show_str_ret:
		ret;show_str_ret
		

retp:
		mov ax,4c00h
		int 21h

code ends
end start
