;ע��Ҫ����öε�ַ��ƫ�Ƶ�ַ
;�Ե�λ����Ҫע���λ�Ƿ�Ҫ��0��
;���С����ģ����Ȱ�si,cx(cl) ѹջ����ʵ���si,cx��;��һ����dh ��ֻ������ʵ�δ�ֵ��show_str��Ҳ���Բ�ѹջ��
assume cs:code

data segment
db 'This is a show string program',0
data ends

code segment
start:
		mov ax,data
		mov ds,ax
;����ʵ�ʲ�����ֵ		
		mov dh,8  ;row index
		mov dl,3  ;col index
		mov cl,02h  ;color value
		mov si,0  ;data adress index
		call show_str
exitp:	call retp
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
