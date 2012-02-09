;�жϴ�������滻
;1.ע�������ʾ��Ϣ�Ĵ��
;2.ע����������Դ��ַ
;3.ע�����ƫ����������
;4.ע���ж�������ĸ���

;TF��Trap Flag�������־����TF������λ1ʱ��CPU���뵥��ģʽ����ν����ģʽ����CPU��ÿִ��һ��ָ��󶼲���һ�������жϡ���Ҫ���ڳ���ĵ��ԡ�
;8086/8088��û��ר��������λ������TF�������Ҫ�������취������
;IF��Interrupt Flag���жϱ�־������CPU�Ƿ�
;��Ӧ�ⲿ�������ж�����TFΪ1ʱ��CPU������Ӧ�ⲿ�Ŀ������ж����󡣡�

assume cs:code

code segment
start:
			
		mov ax,cs ;���뿽��
		mov ds,ax
		mov si,offset do0
		mov ax,0
		mov es,ax
		mov di,200h
		mov cx,offset do0end - offset do0
		cld
		rep movsb ; ds->es
		;set interupt table
		mov ax,0
		mov es,ax
		mov word ptr es:[0*4],200h
		mov word ptr es:2[0*4],0
		
		mov ax,4c00h
		int 21h

do0:
		jmp short do0start
		db 'A divide error occours!'
do0start:
		mov ax,cs
		mov ds,ax
		mov si,202h
		mov ax,0b800h
		mov es,ax
		mov di,12*160
		
		mov cx,23
	s:  mov al,[si]
		mov es:[di],al
		inc si
		mov al,0cah
		mov es:1[di],al
		add di,2
		loop s
		mov ax,4c00h
		int 21h
do0end:
		nop

code ends
end start
