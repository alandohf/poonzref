assume cs:code



data segment
;db 'Welcome to masm!'
db 16 dup(0)
data ends


; ��ʾ��
; 1.�з������ڼ�����������䲹����ʽ���д洢�ġ�
; 2.ע��ִ��ָ��"add ax,0010h"��Ӱ�����ر�־λ��������������£�
 
; CF       OF       SF       ZF       PF
 ; 1         0          0          1         1


code segment
start:
		mov ax,0
		push ax ;(ss:sp) 0000h
		popf ; 0 0 ei 0 0 na 0 0 ->00h ; if(ei1,di0) af(ac1,na0)
		mov ax,0fff0h ; flag:0 0 0 0 0 0 0 0 
		add ax,0010h ; ע�������־λ��λ�ã���������1-8��˳��洢���� 0 0 0 0 1 0 1 1  cf=1 pf = 1 zf =1  
		; 0 0 ! ! 0 0 0 0 - 0 1 0 0 0 1 ! 1 
		;pushf 3047h 00110000 01000111b ?
		pushf	; 0bh
		pop ax ; 0bh
		and al,11000101b ;����޹�λ;ֻ����zf��pf,cf
		and ah,00001000b ;����޹�λ;ֻ����zf��pf,cf
		

retp:
		mov ax,4c00h
		int 21h

code ends
end start
