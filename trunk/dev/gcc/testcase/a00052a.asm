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

; revert_str:	
;ת���ɿɴ�ӡ�ַ�����ջ
			; pop si
			; inc di
			; mov cx,di
	; revert_push:
			; mov dx,ds:[si]
			; add dx,30h
			; push dx
			; inc si
			; loop revert_push
			
			; mov cx,di
			; mov si,0
	; revert_pop:
			; pop dx
			; mov ds:[si],dl
			; inc si
			; loop revert_pop
	; add0:
	; mov dl,0
	; mov ds:[si],dl
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
		;mov ds:[di],dl ;��������;��ֻ�����жϣ����ñ���
		add dx,30h
		push dx
		mov dx,0
		add di,1
		jmp d2c
d2cret: 
		;mov ds:[di],dl ;��������;��ֻ�����жϣ����ñ���
		add dx,30h
		push dx
		inc di
		mov cx,di
		mov si,0
popchar:
		pop dx
		mov ds:[si],dl
		inc si
		loop popchar
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
	
		push cx
		push si
		mov al,0a0h
		dec dh
		mul dh
		mov bx,ax
		mov al,2
		mul dl
		sub ax,2
		add bx,ax
		mov ax,0b800h
		mov es,ax
		mov di,0
		mov al,cl
		mov ch,0
s:	    mov cl,ds:[si]
		jcxz ok
		mov es:[bx+di],cl
		mov es:[bx+di+1],al
		inc si
		add di,2
		jmp short s
ok : pop si
	 pop cx
	 ret  ;show_str_ret
		

retp:
		mov ax,4c00h
		int 21h

code ends
end start
